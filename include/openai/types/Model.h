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
    return "Model(id='" + id + "', created='" + std::to_string(created) + "', object='" + object + "', owned_by='"
      + owned_by + "')";
  }
};

inline void from_json(const nlohmann::json& j, Model& model) {
  j.at("id").get_to(model.id);
  j.at("created").get_to(model.created);
  j.at("object").get_to(model.object);
  j.at("owned_by").get_to(model.owned_by);
}

}
