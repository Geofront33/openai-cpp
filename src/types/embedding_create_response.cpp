#include <openai/types/embedding_create_response.h>

namespace openai
{

void from_json(const nlohmann::json& j, EmbeddingCreateResponse::Usage& x) {
  j.at("prompt_tokens").get_to(x.prompt_tokens);
  j.at("total_tokens").get_to(x.total_tokens);
}

void from_json(const nlohmann::json& j, EmbeddingCreateResponse& x) {
  j.at("data").get_to(x.data);
  j.at("model").get_to(x.model);
  j.at("object").get_to(x.object);
  j.at("usage").get_to(x.usage);
}

}
