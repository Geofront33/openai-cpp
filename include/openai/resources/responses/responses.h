#pragma once
#include <openai/resources/api_resource.h>

namespace openai
{

class Responses;
class ResponsesWithRawResponse;

class Responses : SyncAPIResource
{
public:
  explicit Responses(const SyncAPIClient& client) : SyncAPIResource(client) {}

  ResponsesWithRawResponse with_raw_response() const;

  struct ResponsesCreateOpts;
  httplib::Response create_raw(const ResponsesCreateOpts& opts) const;
};

class ResponsesWithRawResponse : Responses
{
public:
  explicit ResponsesWithRawResponse(const Responses& client) : Responses(client) {}

  httplib::Response create(const ResponsesCreateOpts& opts) const;
};

struct Responses::ResponsesCreateOpts
{
  std::variant<std::string, std::vector<std::string>> input;
  std::string instructions;
  std::string model;

  std::string validate_and_serialize() const;
};

}
