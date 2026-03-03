#pragma once
#include <openai/resources/embeddings.h>
#include <openai/resources/images.h>
#include <openai/resources/models.h>
#include <openai/resources/moderations.h>

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
  const Images& images();
  const Moderations& moderations();
  const Models& models();

  OpenAIWithRawResponse with_raw_response();

private:
  std::once_flag f_embeddings;
  std::unique_ptr<Embeddings> embeddings_;
  std::once_flag f_images;
  std::unique_ptr<Images> images_;
  std::once_flag f_moderations;
  std::unique_ptr<Moderations> moderations_;
  std::once_flag f_models;
  std::unique_ptr<Models> models_;
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
  const ImagesWithRawResponse& images();
  const ModerationsWithRawResponse& moderations();
  const ModelsWithRawResponse& models();

private:
  OpenAI& client;

  std::once_flag f_embeddings;
  std::unique_ptr<EmbeddingsWithRawResponse> embeddings_;
  std::once_flag f_images;
  std::unique_ptr<ImagesWithRawResponse> images_;
  std::once_flag f_moderations;
  std::unique_ptr<ModerationsWithRawResponse> moderations_;
  std::once_flag f_models;
  std::unique_ptr<ModelsWithRawResponse> models_;
};

}
