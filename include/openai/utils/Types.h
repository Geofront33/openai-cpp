#pragma once
#include <openai/third_party/yhirose/httplib.h>

namespace openai
{

struct FinalRequestOptions
{
  std::string method;
  std::string url;
  httplib::Params params;
  httplib::Headers headers;
  int max_retries;
  float timeout;
  std::string json_data;
};

}

