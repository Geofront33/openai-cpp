#pragma once
#include <openai/client/APIClient.h>

namespace openai
{

class SyncAPIResource
{
  const SyncAPIClient& client;

public:
  explicit SyncAPIResource(SyncAPIClient& client) : client(client) {}

  httplib::Response Get(const std::string& path) const {
    return client.Get(path);
  }
  httplib::Response Post(const std::string& path, const std::string& body) const {
    return client.Post(path, body);
  }
  void Patch() const {
    client.Patch();
  }
  void Put() const {
    client.Put();
  }
  void Delete() const {
    client.Delete();
  }
  httplib::Response GetAPIList(const std::string& path) const {
    return client.GetAPIList(path);
  }
};

class AsyncAPIService
{

};

}
