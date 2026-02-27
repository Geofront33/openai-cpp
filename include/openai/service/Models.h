#pragma once
#include <openai/service/APIService.h>
#include <openai/types/Model.h>

namespace openai
{

class ModelsWithRawResponse : public SyncAPIService
{
public:
  explicit ModelsWithRawResponse(SyncAPIClient& client) : SyncAPIService(client) {}

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
