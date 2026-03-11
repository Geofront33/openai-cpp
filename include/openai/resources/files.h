#pragma once
#include <openai/resources/api_resource.h>
#include <openai/types/file_deleted.h>
#include <openai/types/file_object.h>

namespace openai
{

class Files;
class FilesWithRawResponse;

class Files : SyncAPIResource
{
public:
  explicit Files(const SyncAPIClient& client) : SyncAPIResource(client) {}

  FilesWithRawResponse with_raw_response() const;

  struct FilesListOpts;
  std::vector<FileObject> list() const;
  std::vector<FileObject> list(const FilesListOpts& opts) const;
  httplib::Response list_raw() const;
  httplib::Response list_raw(const FilesListOpts& opts) const;

  struct FilesCreateOpts;
  FileObject create(const FilesCreateOpts& opts) const;
  httplib::Response create_raw(const FilesCreateOpts& opts) const;

  FileObject retrieve(const std::string& file_id) const;
  httplib::Response retrieve_raw(const std::string& file_id) const;

  FileDeleted remove(const std::string& file_id) const;
  httplib::Response remove_raw(const std::string& file_id) const;

  httplib::Response content(const std::string& file_id) const;
  httplib::Response content_raw(const std::string& file_id) const;
};

class FilesWithRawResponse : Files
{
public:
  explicit FilesWithRawResponse(const Files& files) : Files(files) {}

  httplib::Response list() const;
  httplib::Response list(const FilesListOpts& opts) const;
  httplib::Response create(const FilesCreateOpts& opts) const;
  httplib::Response retrieve(const std::string& file_id) const;
  httplib::Response remove(const std::string& file_id) const;
  httplib::Response content(const std::string& file_id) const;
};

struct Files::FilesListOpts
{
  std::string purpose;
  std::optional<int> limit;
  std::string order;
  std::string after;

  httplib::Params to_query_params() const;
};

struct Files::FilesCreateOpts
{
  std::string file_path;
  std::string purpose;
  std::string expires_after_anchor;
  std::optional<int> expires_after_seconds;

  httplib::MultipartFormDataItems validate_and_serialize() const;
};

}
