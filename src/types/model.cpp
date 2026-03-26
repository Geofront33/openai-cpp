#include <openai/types/model.h>
#include <openai/utils/utils.h>
#include <sstream>

namespace openai
{

std::string Model::to_string() const {
  assert(object == "model");
  std::ostringstream oss;
  oss << "Model" << "(";
  oss << "id='" << id << "'";
  if (created) {
    oss << ", created=" << *created;
  }
  oss << ", object='" << object << "'";
  oss << ", owned_by='" << owned_by << "'";
  oss << ")";
  return oss.str();
}

void from_json(const nlohmann::json& j, Model& model) {
  j["id"].get_to(model.id);
  get_opt(j, "created", model.created);
  j["object"].get_to(model.object);
  j["owned_by"].get_to(model.owned_by);
}

}
