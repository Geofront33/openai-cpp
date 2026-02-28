#pragma once
#include <openai/resources/APIService.h>
#include <openai/types/create_embedding_response.h>

namespace openai
{

class EmbeddingsWithRawResponse : public SyncAPIService
{
public:
  explicit EmbeddingsWithRawResponse(SyncAPIClient& client) : SyncAPIService(client) {}

  struct EmbeddingsCreateOpts;
  httplib::Response create(const EmbeddingsCreateOpts& opts) const;

  struct EmbeddingsCreateOpts
  {
    std::string input;
    std::string model;
    int dimensions;
    std::string encoding_format;

    std::string validate_and_serialize() const;
  };
};

class Embeddings : public EmbeddingsWithRawResponse
{
public:
  explicit Embeddings(SyncAPIClient& client) : EmbeddingsWithRawResponse(client) {}

  const EmbeddingsWithRawResponse& with_raw_response() const;

  CreateEmbeddingResponse create(const EmbeddingsCreateOpts& opts) const;
};

}
