#pragma once
#include <openai/types/image.h>

namespace openai
{

struct ImagesResponse
{
  struct Usage {
    struct UsageInputTokensDetails
    {
      int image_tokens;
      int text_tokens;
    };

    struct UsageOutputTokensDetails
    {
      int image_tokens;
      int text_tokens;
    };

    int input_tokens{};
    UsageInputTokensDetails input_tokens_details{};
    int output_tokens{};
    int total_tokens{};
    std::optional<UsageOutputTokensDetails> output_tokens_details;
  };

  int created;
  std::optional<std::string> background;
  std::vector<Image> data;
  std::optional<std::string> output_format;
  std::optional<std::string> quality;
  std::optional<std::string> size;
  std::optional<Usage> usage;
};

void from_json(const nlohmann::json& j, ImagesResponse::Usage::UsageInputTokensDetails& x);
void from_json(const nlohmann::json& j, ImagesResponse::Usage::UsageOutputTokensDetails& x);
void from_json(const nlohmann::json& j, ImagesResponse::Usage& x);
void from_json(const nlohmann::json& j, ImagesResponse& x);

}
