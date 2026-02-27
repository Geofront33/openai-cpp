#pragma once
#include <vector>
#include <openai/types/Image.h>

namespace openai
{

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

struct Usage
{
  int input_tokens;
  UsageInputTokensDetails input_tokens_details;
  int output_tokens;
  int total_tokens;
  UsageOutputTokensDetails output_tokens_details;
};

struct ImagesResponse
{
  int created;
  std::string background;
  std::vector<Image> data;
  std::string output_format;
  std::string quality;
  std::string size;
  Usage usage;
};

inline void from_json(const nlohmann::json& j, ImagesResponse& ir) {
  j.at("created").get_to(ir.created);
  ir.background = j.value("background", "");
  j.at("data").get_to(ir.data);
  ir.output_format = j.value("output_format", "");
  ir.quality = j.value("quality", "");
  ir.size = j.value("size", "");
}

}
