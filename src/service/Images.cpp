#include <openai/service/Images.h>

namespace openai
{

ImagesResponse Images::generate(const ImagesGenerateOpts& opts) const {
  auto res = Post("/images/generations", opts.validate_and_serialize());
  return nlohmann::json::parse(res.body).get<ImagesResponse>();
}

std::string Images::ImagesGenerateOpts::validate_and_serialize() const {
  nlohmann::json j;

  j["prompt"] = prompt;
  if (!background.empty()) {
    assert(background == "transparent" || background == "opaque" || background == "auto");
    j["background"] = background;
  }
  if (!model.empty()) {
    assert(model == "gpt-image-1.5" || model == "dall-e-2" || model == "dall-e-3" || model == "gpt-image-1"
      || model == "gpt-image-1-mini");
    j["model"] = model;
  }
  if (!moderation.empty()) {
    assert(moderation == "low" || moderation == "auto");
    j["moderation"] = moderation;
  }
  if (n) {
    j["n"] = n;
  }
  if (!output_format.empty()) {
    assert(output_format == "png" || output_format == "jpeg" || output_format == "webp");
    j["output_format"] = output_format;
  }
  if (!quality.empty()) {
    assert(quality == "standard" || quality == "hd" || quality == "low" || quality == "medium" || quality == "high"
      || quality == "auto");
    j["quality"] = quality;
  }
  if (!response_format.empty()) {
    assert(response_format == "url" || response_format == "b64_json");
    j["response_format"] = response_format;
  }
  if (!size.empty()) {
    assert(size == "auto" || size == "1024x1024" || size == "1536x1024" || size == "1024x1536" || size == "256x256"
      || size == "512x512" || size == "1792x1024" || size == "1024x1792");
    j["size"] = size;
  }

  return j.dump();
}

}
