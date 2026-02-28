#pragma once
#include <openai/resources/api_resource.h>
#include <openai/types/images_response.h>

namespace openai
{

class ImagesWithRawResponse : public SyncAPIResource
{
public:
  explicit ImagesWithRawResponse(SyncAPIClient& client) : SyncAPIResource(client) {}

  struct ImagesGenerateOpts;
  httplib::Response generate(const ImagesGenerateOpts& opts) const;

  struct ImagesGenerateOpts
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
};

class Images : public ImagesWithRawResponse
{
public:
  explicit Images(SyncAPIClient& client) : ImagesWithRawResponse(client) {}

  const ImagesWithRawResponse& with_raw_response() const;

  ImagesResponse generate(const ImagesGenerateOpts& opts) const;
};

}

