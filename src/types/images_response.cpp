#include <openai/types/images_response.h>
#include <openai/utils/utils.h>

namespace openai
{

void from_json(const nlohmann::json& j, ImagesResponse::Usage::UsageInputTokensDetails& x) {
  j.at("image_tokens").get_to(x.image_tokens);
  j.at("text_tokens").get_to(x.text_tokens);
}

void from_json(const nlohmann::json& j, ImagesResponse::Usage::UsageOutputTokensDetails& x) {
  j.at("image_tokens").get_to(x.image_tokens);
  j.at("text_tokens").get_to(x.text_tokens);
}

void from_json(const nlohmann::json& j, ImagesResponse::Usage& x) {
  j.at("input_tokens").get_to(x.input_tokens);
  j.at("input_tokens_details").get_to(x.input_tokens_details);
  j.at("output_tokens").get_to(x.output_tokens);
  j.at("total_tokens").get_to(x.total_tokens);
  get_opt(j, "output_tokens_details", x.output_tokens_details);
}

void from_json(const nlohmann::json& j, ImagesResponse& x) {
  j.at("created").get_to(x.created);
  get_opt(j, "background", x.background);
  x.data = j.value("data", std::vector<Image>{});
  get_opt(j, "output_format", x.output_format);
  get_opt(j, "quality", x.quality);
  get_opt(j, "size", x.size);
  get_opt(j, "usage", x.usage);
}

}

