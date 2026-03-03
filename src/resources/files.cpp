#include <openai/resources/files.h>
#include <openai/utils/OpenAIError.h>

namespace openai
{

FilesWithRawResponse Files::with_raw_response() const {
  return FilesWithRawResponse(*this);
}

std::vector<FileObject> Files::list() const {
  return nlohmann::json::parse(list_raw().body)["data"].get<std::vector<FileObject>>();
}

httplib::Response Files::list_raw() const {
  return GetAPIList("/files");
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

httplib::Response FilesWithRawResponse::list() const {
  return list_raw();
}

httplib::Response FilesWithRawResponse::retrieve(const std::string& file_id) const {
  return retrieve_raw(file_id);
}

httplib::Response FilesWithRawResponse::remove(const std::string& file_id) const {
  return remove_raw(file_id);
}

}
