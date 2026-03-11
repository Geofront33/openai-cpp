#pragma once
#include <openai/client/BaseClient.h>
#include <openai/third_party/yhirose/httplib.h>

namespace openai
{

class SyncAPIClient : public BaseClient
{
public:
  httplib::Response Get(const std::string& path) const;
  httplib::Response Get(const std::string& path, const httplib::Params& params) const;
  httplib::Response Post(const std::string& path, const std::string& body) const;
  httplib::Response PostMultipart(
    const std::string& path,
    const httplib::MultipartFormDataItems& multipart_form_data
  ) const;
  void Patch() const {}
  void Put() const {}
  httplib::Response Delete(const std::string& path) const;
  httplib::Response GetAPIList(const std::string& path) const;
  httplib::Response GetAPIList(const std::string& path, const httplib::Params& params) const;

  std::unique_ptr<httplib::SSLClient> client;

private:
  httplib::Response request(const FinalRequestOptions& options) const;
};

}
