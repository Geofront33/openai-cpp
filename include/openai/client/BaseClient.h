#pragma once
#include <openai/third_party/yhirose/httplib.h>
#include <openai/utils/URL.h>
#include <openai/utils/Types.h>

namespace openai
{

class BaseClient
{
public:
  std::string version;
  int max_retires = 0;
  float timeout;
  std::map<std::string, std::string> custom_headers;
  std::map<std::string, std::string> custom_query;

  std::string api_key;
  std::string organization;
  std::string project;
  std::string webhook_secret;
  URL base_url;
  std::string websocket_base_url;

  httplib::Headers build_headers(const FinalRequestOptions& options, int retries_taken) const;
  std::string prepare_url(const std::string& url) const;
  httplib::Request build_request(const FinalRequestOptions& options, int retries_taken) const;

  std::map<std::string, std::string> auth_headers() const;
  std::map<std::string, std::string> default_headers() const;
  static std::string user_agent();
};

}
