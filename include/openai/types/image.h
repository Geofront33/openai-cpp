#pragma once
#include <openai/third_party/nlohmann/json.h>

namespace openai
{

struct Image
{
  std::string b64_json;
  std::string revised_prompt;
  std::string url;
};

void from_json(const nlohmann::json& j, Image& image);

}
