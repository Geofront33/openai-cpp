#pragma once
#include <openai/resources/api_resource.h>
#include <openai/types/model.h>

namespace openai
{

class ModelsWithRawResponse : public SyncAPIResource
{
public:
  explicit ModelsWithRawResponse(SyncAPIClient& client) : SyncAPIResource(client) {}

  httplib::Response retrieve(const std::string& model) const;
  httplib::Response list() const;
};

class Models : public ModelsWithRawResponse
{
public:
  explicit Models(SyncAPIClient& client) : ModelsWithRawResponse(client) {}

  const ModelsWithRawResponse& with_raw_response() const;

  Model retrieve(const std::string& model) const;
  std::vector<Model> list() const;
};

}
