#pragma once
#include <openai/third_party/nlohmann/json.h>
#include <openai/utils/utils.h>

namespace openai
{

struct Embedding
{
  std::vector<float> embedding;
  int index;
  std::string object;

  std::string to_string() const {
    std::ostringstream oss;
    oss << "Embedding(embedding=[";
    auto sep = "";
    for (const auto& e : embedding) {
      oss << sep << e;
      sep = ", ";
    }
    oss << "], index=" << index << ", object='" << object << "')";
    return oss.str();
  }
};

inline void from_json(const nlohmann::json& j, Embedding& embedding) {
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
