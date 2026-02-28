#pragma once
#include <openai/resources/api_resource.h>
#include <openai/types/moderation_create_response.h>

namespace openai
{

class ModerationsWithRawResponse : public SyncAPIResource
{
public:
  explicit ModerationsWithRawResponse(SyncAPIClient& client) : SyncAPIResource(client) {}

  struct ModerationsCreateOpts;
  httplib::Response create(const ModerationsCreateOpts& opts) const;

  struct ModerationsCreateOpts
  {
    std::string input;
    std::string model;

    std::string validate_and_serialize() const;
  };
};

class Moderations : ModerationsWithRawResponse
{
public:
  explicit Moderations(SyncAPIClient& client) : ModerationsWithRawResponse(client) {}

  const ModerationsWithRawResponse& with_raw_response() const;

  ModerationCreateResponse create(const ModerationsCreateOpts& opts) const;
};

}
