#pragma once
#include <openai/third_party/nlohmann/json.h>

namespace openai
{

struct FileObject
{
  std::string id;
  int bytes;
  int created_at;
  std::string filename;
  std::string object;
  std::string purpose;
  std::optional<int> expires_at;

  std::string to_string() const;
};

void from_json(const nlohmann::json& j, FileObject& file_object);

}
