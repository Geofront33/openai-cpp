#pragma once
#include <openai/resources/api_resource.h>
#include <openai/types/images_response.h>

namespace openai
{

class Images;
class ImagesWithRawResponse;

class Images : SyncAPIResource
{
public:
  explicit Images(const SyncAPIClient& client) : SyncAPIResource(client) {}

  ImagesWithRawResponse with_raw_response() const;

  struct ImagesGenerateOpts;
  ImagesResponse generate(const ImagesGenerateOpts& opts) const;
  httplib::Response generate_raw(const ImagesGenerateOpts& opts) const;

  struct ImagesEditOpts;
  ImagesResponse edit(const ImagesEditOpts& opts) const;
  httplib::Response edit_raw(const ImagesEditOpts& opts) const;

  struct ImagesVariationOpts;
  ImagesResponse create_variation(const ImagesVariationOpts& opts) const;
  httplib::Response create_variation_raw(const ImagesVariationOpts& opts) const;
};

class ImagesWithRawResponse : Images
{
public:
  explicit ImagesWithRawResponse(const Images& images) : Images(images) {}

  httplib::Response generate(const ImagesGenerateOpts& opts) const;
  httplib::Response edit(const ImagesEditOpts& opts) const;
  httplib::Response create_variation(const ImagesVariationOpts& opts) const;
};

struct Images::ImagesGenerateOpts
{
  std::string prompt;
  std::string background;
  std::string model;
  std::string moderation;
  std::optional<int> n;
  std::optional<int> output_compression;
  std::string output_format;
  std::string quality;
  std::string response_format;
  std::string size;
  std::string style;
  std::string user;

  std::string validate_and_serialize() const;
};

struct Images::ImagesEditOpts
{
  std::vector<std::string> image_paths;
  std::string mask_path;
  std::string prompt;
  std::string background;
  std::string model;
  std::string moderation;
  int n;
  int output_compression;
  std::string output_format;
  std::string quality;
  std::string size;
  std::string style;
  std::string user;

  httplib::MultipartFormDataItems validate_and_serialize() const;
};

struct Images::ImagesVariationOpts
{
  std::string image_path;
  std::string model;
  int n;
  std::string response_format;
  std::string size;
  std::string user;

  httplib::MultipartFormDataItems validate_and_serialize() const;
};

}
