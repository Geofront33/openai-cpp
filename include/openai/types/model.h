#pragma once
#include <openai/third_party/nlohmann/json.h>

namespace openai
{

struct Model
{
  std::string id;
  int created;
  std::string object;
  std::string owned_by;

  std::string to_string() const;
};

void from_json(const nlohmann::json& j, Model& model);

}
