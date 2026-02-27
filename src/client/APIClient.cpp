#include <openai/client/APIClient.h>
#include <openai/third_party/yhirose/httplib.h>

namespace openai
{

httplib::Response SyncAPIClient::Get(const std::string& path) const {
  FinalRequestOptions opts;
  opts.method = "GET";
  opts.url = path;
  return request(opts);
}

httplib::Response SyncAPIClient::Post(const std::string& path, const std::string& body) const {
  FinalRequestOptions opts;
  opts.method = "POST";
  opts.url = path;
  opts.json_data = body;
  return request(opts);
}

httplib::Response SyncAPIClient::GetAPIList(const std::string& path) const {
  FinalRequestOptions opts;
  opts.method = "GET";
  opts.url = path;
  return request(opts);
}

httplib::Response SyncAPIClient::request(const FinalRequestOptions& options) const {
  int retries_taken = 0;
  while (retries_taken < max_retires + 1) {
    int remaining_retries = max_retires - retries_taken;
    auto request = build_request(options, retries_taken);

    auto response = client->send(request);
    if (response.error() != httplib::Error::Success) {
      retries_taken++;
      std::cerr << "[openai-cpp] HTTP send error: " << httplib::to_string(response.error()) << std::endl;
      continue;
    }
    return response.value();
  }
  return {};
}

}
