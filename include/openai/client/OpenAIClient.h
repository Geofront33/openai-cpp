#pragma once
#include <openai/resources/embeddings.h>
#include <openai/resources/models.h>
#include <openai/resources/responses/responses.h>

namespace openai
{

class OpenAI;
class OpenAIWithRawResponse;

class OpenAI : public SyncAPIClient
{
public:
  OpenAI();
  struct OpenAIClientOpts;
  explicit OpenAI(const OpenAIClientOpts& opts);

  const Embeddings& embeddings();
  const Models& models();
  const Responses& responses();

  OpenAIWithRawResponse with_raw_response();

private:
  std::once_flag f_embeddings;
  std::unique_ptr<Embeddings> embeddings_;

  std::once_flag f_models;
  std::unique_ptr<Models> models_;

  std::once_flag f_responses;
  std::unique_ptr<Responses> responses_;
};

struct OpenAI::OpenAIClientOpts
{
  std::string api_key;
  std::string organization;
  std::string project;
  std::string webhook_secret;
  std::string base_url;
  std::string websocket_base_url;
};

class OpenAIWithRawResponse
{
public:
  explicit OpenAIWithRawResponse(OpenAI& client) : client{client} {}

  const EmbeddingsWithRawResponse& embeddings();
  const ModelsWithRawResponse& models();
  const ResponsesWithRawResponse& responses();

private:
  OpenAI& client;

  std::once_flag f_embeddings;
  std::unique_ptr<EmbeddingsWithRawResponse> embeddings_;

  std::once_flag f_models;
  std::unique_ptr<ModelsWithRawResponse> models_;

  std::once_flag f_responses;
  std::unique_ptr<ResponsesWithRawResponse> responses_;
};

}
