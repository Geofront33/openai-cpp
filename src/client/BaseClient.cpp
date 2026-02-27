#include <openai/client/BaseClient.h>

namespace openai
{

httplib::Headers BaseClient::build_headers(const FinalRequestOptions& options, int retries_taken) const {
  auto res = default_headers();
  return {res.begin(), res.end()};
}

std::string BaseClient::prepare_url(const std::string& url) const {
  if (url[0] == '/') {
    return base_url.path + url;
  }
  return url;
}

httplib::Request BaseClient::build_request(const FinalRequestOptions& options, const int retries_taken) const {
  auto headers = build_headers(options, retries_taken);
  if (options.method != "GET") {
    // todo
  } else {
    headers.erase("Content-Type");
  }
  return {
    .method = options.method,
    .path = prepare_url(options.url),
    .headers = std::move(headers),
    .body = options.json_data,
  };
}

std::map<std::string, std::string> BaseClient::auth_headers() const {
  if (api_key.empty()) {
    return {};
  }
  return {{"Authorization", "Bearer " + api_key}};
}

std::map<std::string, std::string> BaseClient::default_headers() const {
  std::map<std::string, std::string> res = {
    {"Accept", "application/json"},
    {"Content-Type", "application/json"},
    {"User-Agent", user_agent()},
  };
  res.merge(auth_headers());
  res.insert(custom_headers.begin(), custom_headers.end());
  if (!organization.empty()) {
    res.emplace("OpenAI-Organization", organization);
  }
  if (!project.empty()) {
    res.emplace("OpenAI-Project", project);
  }
  return res;
}

std::string BaseClient::user_agent() {
  return "openai-cpp/0.1.0";
}

}
