#pragma once
#include <openai/service/APIService.h>
#include <openai/types/Image.h>

namespace openai
{

class ImagesWithRawResponse : public SyncAPIService
{
public:
  explicit ImagesWithRawResponse(SyncAPIClient& client) : SyncAPIService(client) {}

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

  std::vector<Image> generate(const ImagesGenerateOpts& opts) const;
};

}

