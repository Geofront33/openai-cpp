#pragma once
#include <mutex>
#include <optional>
#include <openai/service/Images.h>
#include <openai/service/Models.h>

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

  Images& images();
  Models& models();

private:
  std::once_flag f_images;
  std::optional<Images> v_images;
  std::once_flag f_models;
  std::optional<Models> v_models;
};

}
