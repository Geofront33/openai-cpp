#pragma once
#include <openai/types/moderation.h>

namespace openai
{

struct ModerationCreateResponse
{
  std::string id;
  std::string model;
  std::vector<Moderation> results;
};

void from_json(const nlohmann::json& j, ModerationCreateResponse& x);

}
