#include <openai/types/embedding.h>
#include <openai/utils/utils.h>

namespace openai
{

std::string Embedding::to_string() const {
  std::ostringstream oss;
  oss << "Embedding(embedding=";
  oss << vec2str(embedding) << ", index=" << index << ", object='" << object << "')";
  return oss.str();
}

void from_json(const nlohmann::json& j, Embedding& embedding) {
  j["index"].get_to(embedding.index);
  j["object"].get_to(embedding.object);
  if (const auto& e = j["embedding"]; e.is_array()) {
    e.get_to(embedding.embedding);
  } else {
    const auto b = b64decode(e.get<std::string>());
    embedding.embedding.resize(b.size() / 4);
    std::memcpy(embedding.embedding.data(), b.data(), b.size());
  }
}

}
