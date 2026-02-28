#include <openai/types/moderation_create_response.h>

namespace openai
{

void from_json(const nlohmann::json& j, ModerationCreateResponse& x) {
  j.at("id").get_to(x.id);
  j.at("model").get_to(x.model);
  j.at("results").get_to(x.results);
}

}
