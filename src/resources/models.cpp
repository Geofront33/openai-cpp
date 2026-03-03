#include <openai/resources/models.h>
#include <openai/utils/OpenAIError.h>

namespace openai
{

ModelsWithRawResponse Models::with_raw_response() const {
  return ModelsWithRawResponse(*this);
}

Model Models::retrieve(const std::string& model) const {
  return nlohmann::json::parse(retrieve_raw(model).body).get<Model>();
}

httplib::Response Models::retrieve_raw(const std::string& model) const {
  if (model.empty()) {
    throw OpenAIError("Expected a non-empty value for `model`");
  }
  return Get("/models/" + model);
}

std::vector<Model> Models::list() const {
  return nlohmann::json::parse(list_raw().body)["data"].get<std::vector<Model>>();
}

httplib::Response Models::list_raw() const {
  return GetAPIList("/models");
}

httplib::Response ModelsWithRawResponse::retrieve(const std::string& model) const {
  return retrieve_raw(model);
}

httplib::Response ModelsWithRawResponse::list() const {
  return list_raw();
}

}
