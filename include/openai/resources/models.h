#pragma once
#include <openai/resources/api_resource.h>
#include <openai/types/model.h>

namespace openai
{

class Models;
class ModelsWithRawResponse;

class Models : SyncAPIResource
{
public:
  explicit Models(const SyncAPIClient& client) : SyncAPIResource(client) {}

  ModelsWithRawResponse with_raw_response() const;

  Model retrieve(const std::string& model) const;
  httplib::Response retrieve_raw(const std::string& model) const;

  std::vector<Model> list() const;
  httplib::Response list_raw() const;
};

class ModelsWithRawResponse : Models
{
public:
  explicit ModelsWithRawResponse(const Models& models) : Models(models) {}

  httplib::Response retrieve(const std::string& model) const;

  httplib::Response list() const;
};

}
