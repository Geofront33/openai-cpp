#pragma once
#include <openai/resources/api_resource.h>
#include <openai/types/embedding_create_response.h>

namespace openai
{

class EmbeddingsWithRawResponse : public SyncAPIResource
{
public:
  explicit EmbeddingsWithRawResponse(SyncAPIClient& client) : SyncAPIResource(client) {}

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

  EmbeddingCreateResponse create(const EmbeddingsCreateOpts& opts) const;
};

}
