#pragma once
#include <openai/resources/embeddings.h>
#include <openai/resources/images.h>
#include <openai/resources/models.h>
#include <openai/resources/moderations.h>

namespace openai
{

struct OpenAIClientOpts
{
  std::string api_key;
  std::string organization;
  std::string project;
  std::string webhook_secret;
  std::string base_url;
  std::string websocket_base_url;
};

class OpenAI : public SyncAPIClient
{
public:
  OpenAI();
  explicit OpenAI(const OpenAIClientOpts& opts);

  const Embeddings& embeddings();
  const Images& images();
  const Moderations& moderations();
  const Models& models();

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

}
