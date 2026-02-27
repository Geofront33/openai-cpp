#include <openai/service/Models.h>
#include <openai/utils/OpenAIError.h>

namespace openai
{

Model Models::retrieve(const std::string& model) const {
  if (model.empty()) {
    throw OpenAIError("Expected a non-empty value for `model`");
  }
  auto res = Get("/models/" + model);
  return nlohmann::json::parse(res.body).get<Model>();
}

std::vector<Model> Models::list() const {
  auto res = GetAPIList("/models");
  return nlohmann::json::parse(res.body)["data"].get<std::vector<Model>>();
}

}
