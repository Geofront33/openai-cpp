#pragma once
#include <openai/types/image.h>
#include <openai/utils/utils.h>

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

inline void from_json(const nlohmann::json& j, ImagesResponse::Usage::UsageInputTokensDetails& x) {
  j.at("image_tokens").get_to(x.image_tokens);
  j.at("text_tokens").get_to(x.text_tokens);
}

inline void from_json(const nlohmann::json& j, ImagesResponse::Usage::UsageOutputTokensDetails& x) {
  j.at("image_tokens").get_to(x.image_tokens);
  j.at("text_tokens").get_to(x.text_tokens);
}

inline void from_json(const nlohmann::json& j, ImagesResponse::Usage& x) {
  j.at("input_tokens").get_to(x.input_tokens);
  j.at("input_tokens_details").get_to(x.input_tokens_details);
  j.at("output_tokens").get_to(x.output_tokens);
  j.at("total_tokens").get_to(x.total_tokens);
  x.output_tokens_details = get_opt<ImagesResponse::Usage::UsageOutputTokensDetails>(j, "output_tokens_details");
}

inline void from_json(const nlohmann::json& j, ImagesResponse& x) {
  j.at("created").get_to(x.created);
  x.background = get_opt<std::string>(j, "background");
  x.data = j.value("data", std::vector<Image>{});
  x.output_format = get_opt<std::string>(j, "output_format");
  x.quality = get_opt<std::string>(j, "quality");
  x.size = get_opt<std::string>(j, "size");
  x.usage = get_opt<ImagesResponse::Usage>(j, "usage");
}

}
