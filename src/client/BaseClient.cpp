#include <openai/client/BaseClient.h>
#include <chrono>

namespace openai
{

httplib::Headers BaseClient::build_headers(const FinalRequestOptions& options, int retries_taken) const {
  auto res = default_headers();
  for (const auto& [k, v] : options.headers) {
    res[k] = v;
  }
  return {res.begin(), res.end()};
}

std::string BaseClient::prepare_url(const std::string& url) const {
  if (url.empty() || url[0] == '/') {
    return base_url.path + url;
  }
  return url;
}

httplib::Request BaseClient::build_request(const FinalRequestOptions& options, const int retries_taken) const {
  auto headers = build_headers(options, retries_taken);
  if (options.method == "GET" || options.method == "DELETE") {
    headers.erase("Content-Type");
  }

  httplib::Request request;
  request.method = options.method;
  request.path = prepare_url(options.url);
  request.headers = std::move(headers);

  for (const auto& [k, v] : custom_query) {
    request.params.emplace(k, v);
  }
  for (const auto& [k, v] : options.params) {
    request.params.emplace(k, v);
  }

  if (!options.multipart_form_data.empty()) {
    const auto boundary = "openai_cpp_boundary_"
      + std::to_string(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    request.body = httplib::detail::serialize_multipart_formdata(options.multipart_form_data, boundary);
    request.headers.erase("Content-Type");
    request.headers.emplace("Content-Type", httplib::detail::serialize_multipart_formdata_get_content_type(boundary));
  } else if (options.method != "GET" && options.method != "DELETE") {
    request.body = options.json_data;
  }

  return request;
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
