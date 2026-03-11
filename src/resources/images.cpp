#include <openai/resources/images.h>
#include <filesystem>
#include <fstream>
#include <openai/utils/OpenAIError.h>

namespace openai
{

std::string read_file_binary(const std::string& file_path) {
  std::ifstream file(file_path, std::ios::binary);
  if (!file) {
    throw OpenAIError("Failed to open file: " + file_path);
  }
  return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

std::string detect_mime_type(const std::string& file_path) {
  const auto ext = std::filesystem::path(file_path).extension().string();
  if (ext == ".png") {
    return "image/png";
  }
  if (ext == ".jpg" || ext == ".jpeg") {
    return "image/jpeg";
  }
  if (ext == ".webp") {
    return "image/webp";
  }
  return "application/octet-stream";
}

ImagesWithRawResponse Images::with_raw_response() const {
  return ImagesWithRawResponse(*this);
}

ImagesResponse Images::generate(const ImagesGenerateOpts& opts) const {
  return nlohmann::json::parse(generate_raw(opts).body).get<ImagesResponse>();
}

httplib::Response Images::generate_raw(const ImagesGenerateOpts& opts) const {
  return Post("/images/generations", opts.validate_and_serialize());
}

ImagesResponse Images::edit(const ImagesEditOpts& opts) const {
  return nlohmann::json::parse(edit_raw(opts).body).get<ImagesResponse>();
}

httplib::Response Images::edit_raw(const ImagesEditOpts& opts) const {
  return PostMultipart("/images/edits", opts.validate_and_serialize());
}

ImagesResponse Images::create_variation(const ImagesVariationOpts& opts) const {
  return nlohmann::json::parse(create_variation_raw(opts).body).get<ImagesResponse>();
}

httplib::Response Images::create_variation_raw(const ImagesVariationOpts& opts) const {
  return PostMultipart("/images/variations", opts.validate_and_serialize());
}

httplib::Response ImagesWithRawResponse::generate(const ImagesGenerateOpts& opts) const {
  return generate_raw(opts);
}

httplib::Response ImagesWithRawResponse::edit(const ImagesEditOpts& opts) const {
  return edit_raw(opts);
}

httplib::Response ImagesWithRawResponse::create_variation(const ImagesVariationOpts& opts) const {
  return create_variation_raw(opts);
}

std::string Images::ImagesGenerateOpts::validate_and_serialize() const {
  nlohmann::json j;

  if (prompt.empty()) {
    throw OpenAIError("Expected a non-empty value for `prompt`");
  }
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
    j["n"] = *n;
  }
  if (output_compression) {
    assert(*output_compression >= 0 && *output_compression <= 100);
    j["output_compression"] = *output_compression;
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
  if (!style.empty()) {
    assert(style == "vivid" || style == "natural");
    j["style"] = style;
  }
  if (!user.empty()) {
    j["user"] = user;
  }

  return j.dump();
}

httplib::MultipartFormDataItems Images::ImagesEditOpts::validate_and_serialize() const {
  if (image_paths.empty()) {
    throw OpenAIError("Expected a non-empty value for `image_paths`");
  }
  if (prompt.empty()) {
    throw OpenAIError("Expected a non-empty value for `prompt`");
  }

  httplib::MultipartFormDataItems items;
  for (const auto& image_path : image_paths) {
    if (image_path.empty()) {
      throw OpenAIError("Expected non-empty entries in `image_paths`");
    }
    const auto content = read_file_binary(image_path);
    items.push_back({
      .name = "image[]",
      .content = content,
      .filename = std::filesystem::path(image_path).filename().string(),
      .content_type = detect_mime_type(image_path),
    });
  }

  if (!mask_path.empty()) {
    const auto content = read_file_binary(mask_path);
    items.push_back({
      .name = "mask",
      .content = content,
      .filename = std::filesystem::path(mask_path).filename().string(),
      .content_type = detect_mime_type(mask_path),
    });
  }

  items.push_back({
    .name = "prompt",
    .content = prompt,
  });

  if (!background.empty()) {
    assert(background == "transparent" || background == "opaque" || background == "auto");
    items.push_back({
      .name = "background",
      .content = background,
    });
  }
  if (!model.empty()) {
    assert(model == "gpt-image-1.5" || model == "dall-e-2" || model == "dall-e-3" || model == "gpt-image-1"
      || model == "gpt-image-1-mini" || model == "chatgpt-image-latest");
    items.push_back({
      .name = "model",
      .content = model,
    });
  }
  if (!moderation.empty()) {
    assert(moderation == "low" || moderation == "auto");
    items.push_back({
      .name = "moderation",
      .content = moderation,
    });
  }
  if (n) {
    items.push_back({
      .name = "n",
      .content = std::to_string(n),
    });
  }
  if (output_compression) {
    assert(output_compression >= 0 && output_compression <= 100);
    items.push_back({
      .name = "output_compression",
      .content = std::to_string(output_compression),
    });
  }
  if (!output_format.empty()) {
    assert(output_format == "png" || output_format == "jpeg" || output_format == "webp");
    items.push_back({
      .name = "output_format",
      .content = output_format,
    });
  }
  if (!quality.empty()) {
    assert(quality == "standard" || quality == "hd" || quality == "low" || quality == "medium" || quality == "high"
      || quality == "auto");
    items.push_back({
      .name = "quality",
      .content = quality,
    });
  }
  if (!size.empty()) {
    assert(size == "auto" || size == "1024x1024" || size == "1536x1024" || size == "1024x1536" || size == "256x256"
      || size == "512x512" || size == "1792x1024" || size == "1024x1792");
    items.push_back({
      .name = "size",
      .content = size,
    });
  }
  if (!style.empty()) {
    assert(style == "vivid" || style == "natural");
    items.push_back({
      .name = "style",
      .content = style,
    });
  }
  if (!user.empty()) {
    items.push_back({
      .name = "user",
      .content = user,
    });
  }

  return items;
}

httplib::MultipartFormDataItems Images::ImagesVariationOpts::validate_and_serialize() const {
  if (image_path.empty()) {
    throw OpenAIError("Expected a non-empty value for `image_path`");
  }

  httplib::MultipartFormDataItems items;
  const auto image_content = read_file_binary(image_path);
  items.push_back({
    .name = "image",
    .content = image_content,
    .filename = std::filesystem::path(image_path).filename().string(),
    .content_type = detect_mime_type(image_path),
  });

  if (!model.empty()) {
    assert(model == "dall-e-2");
    items.push_back({
      .name = "model",
      .content = model,
    });
  }
  if (n) {
    items.push_back({
      .name = "n",
      .content = std::to_string(n),
    });
  }
  if (!response_format.empty()) {
    assert(response_format == "url" || response_format == "b64_json");
    items.push_back({
      .name = "response_format",
      .content = response_format,
    });
  }
  if (!size.empty()) {
    assert(size == "256x256" || size == "512x512" || size == "1024x1024");
    items.push_back({
      .name = "size",
      .content = size,
    });
  }
  if (!user.empty()) {
    items.push_back({
      .name = "user",
      .content = user,
    });
  }

  return items;
}

}
