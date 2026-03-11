#include <openai/resources/files.h>
#include <filesystem>
#include <fstream>
#include <openai/utils/OpenAIError.h>

namespace openai
{

namespace
{

std::string read_file_binary(const std::string& file_path) {
  std::ifstream file(file_path, std::ios::binary);
  if (!file) {
    throw OpenAIError("Failed to open file: " + file_path);
  }
  return {(std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()};
}

std::string detect_mime_type(const std::string& file_path) {
  const auto ext = std::filesystem::path(file_path).extension().string();
  if (ext == ".jsonl" || ext == ".json") {
    return "application/json";
  }
  if (ext == ".txt" || ext == ".md" || ext == ".csv") {
    return "text/plain";
  }
  if (ext == ".pdf") {
    return "application/pdf";
  }
  return "application/octet-stream";
}

}

FilesWithRawResponse Files::with_raw_response() const {
  return FilesWithRawResponse(*this);
}

std::vector<FileObject> Files::list() const {
  return nlohmann::json::parse(list_raw().body)["data"].get<std::vector<FileObject>>();
}

std::vector<FileObject> Files::list(const FilesListOpts& opts) const {
  return nlohmann::json::parse(list_raw(opts).body)["data"].get<std::vector<FileObject>>();
}

httplib::Response Files::list_raw() const {
  return GetAPIList("/files");
}

httplib::Response Files::list_raw(const FilesListOpts& opts) const {
  return GetAPIList("/files", opts.to_query_params());
}

FileObject Files::create(const FilesCreateOpts& opts) const {
  return nlohmann::json::parse(create_raw(opts).body).get<FileObject>();
}

httplib::Response Files::create_raw(const FilesCreateOpts& opts) const {
  return PostMultipart("/files", opts.validate_and_serialize());
}

FileObject Files::retrieve(const std::string& file_id) const {
  return nlohmann::json::parse(retrieve_raw(file_id).body).get<FileObject>();
}

httplib::Response Files::retrieve_raw(const std::string& file_id) const {
  if (file_id.empty()) {
    throw OpenAIError("Expected a non-empty value for `file_id`");
  }
  return Get("/files/" + file_id);
}

FileDeleted Files::remove(const std::string& file_id) const {
  return nlohmann::json::parse(remove_raw(file_id).body).get<FileDeleted>();
}

httplib::Response Files::remove_raw(const std::string& file_id) const {
  if (file_id.empty()) {
    throw OpenAIError("Expected a non-empty value for `file_id`");
  }
  return Delete("/files/" + file_id);
}

httplib::Response Files::content(const std::string& file_id) const {
  return content_raw(file_id);
}

httplib::Response Files::content_raw(const std::string& file_id) const {
  if (file_id.empty()) {
    throw OpenAIError("Expected a non-empty value for `file_id`");
  }
  return Get("/files/" + file_id + "/content");
}

httplib::Response FilesWithRawResponse::list() const {
  return list_raw();
}

httplib::Response FilesWithRawResponse::list(const FilesListOpts& opts) const {
  return list_raw(opts);
}

httplib::Response FilesWithRawResponse::create(const FilesCreateOpts& opts) const {
  return create_raw(opts);
}

httplib::Response FilesWithRawResponse::retrieve(const std::string& file_id) const {
  return retrieve_raw(file_id);
}

httplib::Response FilesWithRawResponse::remove(const std::string& file_id) const {
  return remove_raw(file_id);
}

httplib::Response FilesWithRawResponse::content(const std::string& file_id) const {
  return content_raw(file_id);
}

httplib::Params Files::FilesListOpts::to_query_params() const {
  httplib::Params params;
  if (!purpose.empty()) {
    params.emplace("purpose", purpose);
  }
  if (limit) {
    assert(*limit > 0);
    params.emplace("limit", std::to_string(*limit));
  }
  if (!order.empty()) {
    assert(order == "asc" || order == "desc");
    params.emplace("order", order);
  }
  if (!after.empty()) {
    params.emplace("after", after);
  }
  return params;
}

httplib::MultipartFormDataItems Files::FilesCreateOpts::validate_and_serialize() const {
  if (file_path.empty()) {
    throw OpenAIError("Expected a non-empty value for `file_path`");
  }
  if (purpose.empty()) {
    throw OpenAIError("Expected a non-empty value for `purpose`");
  }

  httplib::MultipartFormDataItems items;
  items.push_back({
    .name = "purpose",
    .content = purpose,
  });

  const auto content = read_file_binary(file_path);
  items.push_back({
    .name = "file",
    .content = content,
    .filename = std::filesystem::path(file_path).filename().string(),
    .content_type = detect_mime_type(file_path),
  });

  if (!expires_after_anchor.empty()) {
    assert(expires_after_anchor == "created_at");
    items.push_back({
      .name = "expires_after[anchor]",
      .content = expires_after_anchor,
    });
  }

  if (expires_after_seconds) {
    assert(*expires_after_seconds > 0);
    items.push_back({
      .name = "expires_after[seconds]",
      .content = std::to_string(*expires_after_seconds),
    });
  }

  return items;
}

}
