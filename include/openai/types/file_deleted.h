#pragma once
#include <openai/third_party/nlohmann/json.h>

namespace openai
{

struct FileDeleted
{
  std::string id;
  bool deleted;
  std::string object;

  std::string to_string() const;
};

void from_json(const nlohmann::json& j, FileDeleted& file_deleted);

}
