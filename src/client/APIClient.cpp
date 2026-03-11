#include <openai/client/APIClient.h>
#include <openai/third_party/yhirose/httplib.h>
#include <openai/utils/OpenAIError.h>

namespace openai
{

httplib::Response SyncAPIClient::Get(const std::string& path) const {
  FinalRequestOptions opts;
  opts.method = "GET";
  opts.url = path;
  return request(opts);
}

httplib::Response SyncAPIClient::Get(const std::string& path, const httplib::Params& params) const {
  FinalRequestOptions opts;
  opts.method = "GET";
  opts.url = path;
  opts.params = params;
  return request(opts);
}

httplib::Response SyncAPIClient::Post(const std::string& path, const std::string& body) const {
  FinalRequestOptions opts;
  opts.method = "POST";
  opts.url = path;
  opts.json_data = body;
  return request(opts);
}

httplib::Response SyncAPIClient::PostMultipart(
  const std::string& path,
  const httplib::MultipartFormDataItems& multipart_form_data
) const {
  FinalRequestOptions opts;
  opts.method = "POST";
  opts.url = path;
  opts.multipart_form_data = multipart_form_data;
  return request(opts);
}

httplib::Response SyncAPIClient::Delete(const std::string& path) const {
  FinalRequestOptions opts;
  opts.method = "DELETE";
  opts.url = path;
  return request(opts);
}

httplib::Response SyncAPIClient::GetAPIList(const std::string& path) const {
  return Get(path);
}

httplib::Response SyncAPIClient::GetAPIList(const std::string& path, const httplib::Params& params) const {
  FinalRequestOptions opts;
  opts.method = "GET";
  opts.url = path;
  opts.params = params;
  return request(opts);
}

httplib::Response SyncAPIClient::request(const FinalRequestOptions& options) const {
  std::string last_error;
  int retries_taken = 0;
  while (retries_taken < max_retires + 1) {
    auto request = build_request(options, retries_taken);

    auto response = client->send(request);
    if (response.error() != httplib::Error::Success) {
      last_error = httplib::to_string(response.error());
      retries_taken++;
      std::cerr << "[openai-cpp] HTTP send error: " << last_error << std::endl;
      continue;
    }
    return response.value();
  }

  throw OpenAIError(
    "Request failed after " + std::to_string(max_retires + 1)
    + " attempt(s): " + (last_error.empty() ? "unknown error" : last_error)
  );
}

}
