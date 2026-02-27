#pragma once
#include <openai/service/APIService.h>
#include <openai/types/ImagesResponse.h>

namespace openai
{

class Images : public SyncAPIService
{
public:
  explicit Images(SyncAPIClient& client) : SyncAPIService(client) {}

  struct ImagesGenerateOpts;
  ImagesResponse generate(const ImagesGenerateOpts& opts) const;

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

}

