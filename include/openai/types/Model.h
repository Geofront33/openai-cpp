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

  std::string to_string() const {
    std::ostringstream oss;
    oss << "Model(id='" << id << "', created=" << created << ", object='" << object << "', owned_by=" << owned_by << ")";
    return oss.str();
  }
};

inline void from_json(const nlohmann::json& j, Model& model) {
  j["id"].get_to(model.id);
  j["created"].get_to(model.created);
  j["object"].get_to(model.object);
  j["owned_by"].get_to(model.owned_by);
}

}
