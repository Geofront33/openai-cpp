#pragma once
#include <openai/service/APIService.h>
#include <openai/types/Model.h>

namespace openai
{

class Models : public SyncAPIService
{
public:
  explicit Models(SyncAPIClient& client) : SyncAPIService(client) {}

  Model retrieve(const std::string& model) const;
  std::vector<Model> list() const;
};

}
