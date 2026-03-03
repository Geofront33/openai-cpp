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
};

class ImagesWithRawResponse : Images
{
public:
  explicit ImagesWithRawResponse(const Images& images) : Images(images) {}

  httplib::Response generate(const ImagesGenerateOpts& opts) const;
};

struct Images::ImagesGenerateOpts
{
  std::string prompt;
  std::string background;
  std::string model;
  std::string moderation;
  int n;
  std::string output_format;
  std::string quality;
  std::string response_format;
  std::string size;
  std::string style;

  std::string validate_and_serialize() const;
};

}

