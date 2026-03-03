#pragma once
#include <openai/resources/api_resource.h>
#include <openai/types/embedding_create_response.h>

namespace openai
{

class Embeddings;
class EmbeddingsWithRawResponse;

class Embeddings : SyncAPIResource
{
public:
  explicit Embeddings(const SyncAPIClient& client) : SyncAPIResource(client) {}

  EmbeddingsWithRawResponse with_raw_response() const;

  struct EmbeddingsCreateOpts;
  EmbeddingCreateResponse create(const EmbeddingsCreateOpts& opts) const;
  httplib::Response create_raw(const EmbeddingsCreateOpts& opts) const;
};

class EmbeddingsWithRawResponse : Embeddings
{
public:
  explicit EmbeddingsWithRawResponse(const Embeddings& client) : Embeddings(client) {}

  httplib::Response create(const EmbeddingsCreateOpts& opts) const;
};

struct Embeddings::EmbeddingsCreateOpts
{
  std::string input;
  std::string model;
  int dimensions;
  std::string encoding_format;

  std::string validate_and_serialize() const;
};

}
