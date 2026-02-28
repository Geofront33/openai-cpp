#pragma once
#include <openai/types/embedding.h>

namespace openai
{

struct EmbeddingCreateResponse
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

void from_json(const nlohmann::json& j, EmbeddingCreateResponse::Usage& x);
void from_json(const nlohmann::json& j, EmbeddingCreateResponse& x);

}
