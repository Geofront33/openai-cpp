#pragma once
#include <openai/resources/api_resource.h>
#include <openai/types/moderation_create_response.h>

namespace openai
{

class Moderations;
class ModerationsWithRawResponse;

class Moderations : SyncAPIResource
{
public:
  explicit Moderations(const SyncAPIClient& client) : SyncAPIResource(client) {}

  ModerationsWithRawResponse with_raw_response() const;

  struct ModerationsCreateOpts;
  ModerationCreateResponse create(const ModerationsCreateOpts& opts) const;
  httplib::Response create_raw(const ModerationsCreateOpts& opts) const;
};

class ModerationsWithRawResponse : Moderations
{
public:
  explicit ModerationsWithRawResponse(const Moderations& moderations) : Moderations(moderations) {}

  httplib::Response create(const ModerationsCreateOpts& opts) const;
};

struct Moderations::ModerationsCreateOpts
{
  std::string input;
  std::string model;

  std::string validate_and_serialize() const;
};

}
