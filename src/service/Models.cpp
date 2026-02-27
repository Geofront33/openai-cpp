#include <openai/service/Models.h>
#include <openai/utils/OpenAIError.h>

namespace openai
{

httplib::Response ModelsWithRawResponse::retrieve(const std::string& model) const {
  if (model.empty()) {
    throw OpenAIError("Expected a non-empty value for `model`");
  }
  return Get("/models/" + model);
}

httplib::Response ModelsWithRawResponse::list() const {
  return GetAPIList("/models");
}

const ModelsWithRawResponse& Models::with_raw_response() const {
  return static_cast<const ModelsWithRawResponse&>(*this);
}

Model Models::retrieve(const std::string& model) const {
  return nlohmann::json::parse(with_raw_response().retrieve(model).body).get<Model>();
}

std::vector<Model> Models::list() const {
  return nlohmann::json::parse(with_raw_response().list().body)["data"].get<std::vector<Model>>();
}

}
