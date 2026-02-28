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

inline void from_json(const nlohmann::json& j, Image& image) {
  image.b64_json = j.value("b64_json", "");
  image.revised_prompt = j.value("revised_prompt", "");
  image.url = j.value("url", "");
}

}
