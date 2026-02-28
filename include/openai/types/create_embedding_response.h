#pragma once
#include <openai/types/embedding.h>

namespace openai
{

struct CreateEmbeddingResponse
{
  struct Usage
  {
    int prompt_tokens;
    int total_tokens;
  };

  std::vector<Embedding> data;
  std::string model;
  std::string object;
  Usage usage;
};

inline void from_json(const nlohmann::json& j, CreateEmbeddingResponse::Usage& x) {
  j.at("prompt_tokens").get_to(x.prompt_tokens);
  j.at("total_tokens").get_to(x.total_tokens);
}

inline void from_json(const nlohmann::json& j, CreateEmbeddingResponse& x) {
  j.at("data").get_to(x.data);
  j.at("model").get_to(x.model);
  j.at("object").get_to(x.object);
  j.at("usage").get_to(x.usage);
}

}
