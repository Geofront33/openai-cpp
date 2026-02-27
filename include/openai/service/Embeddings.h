#pragma once
#include <openai/service/APIService.h>
#include <openai/types/Embedding.h>

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

  std::vector<Embedding> create(const EmbeddingsCreateOpts& opts) const;
};

}
