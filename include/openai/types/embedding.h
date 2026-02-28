#pragma once
#include <openai/third_party/nlohmann/json.h>

namespace openai
{

struct Embedding
{
  std::vector<float> embedding;
  int index;
  std::string object;

  std::string to_string() const;
};

void from_json(const nlohmann::json& j, Embedding& embedding);

}
