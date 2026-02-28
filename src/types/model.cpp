#include <openai/types/model.h>
#include <sstream>

namespace openai
{

std::string Model::to_string() const {
  std::ostringstream oss;
  oss << "Model(id='" << id << "', created=" << created << ", object='" << object << "', owned_by=" << owned_by << ")";
  return oss.str();
}

void from_json(const nlohmann::json& j, Model& model) {
  j["id"].get_to(model.id);
  j["created"].get_to(model.created);
  j["object"].get_to(model.object);
  j["owned_by"].get_to(model.owned_by);
}

}
