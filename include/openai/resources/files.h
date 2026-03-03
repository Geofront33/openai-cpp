#pragma once
#include <openai/resources/api_resource.h>
#include <openai/types/file_deleted.h>
#include <openai/types/file_object.h>

#include "files.h"

namespace openai
{

class Files;
class FilesWithRawResponse;

class Files : SyncAPIResource
{
public:
  explicit Files(const SyncAPIClient& client) : SyncAPIResource(client) {}

  FilesWithRawResponse with_raw_response() const;

  std::vector<FileObject> list() const;
  httplib::Response list_raw() const;

  FileObject retrieve(const std::string& file_id) const;
  httplib::Response retrieve_raw(const std::string& file_id) const;

  FileDeleted remove(const std::string& file_id) const;
  httplib::Response remove_raw(const std::string& file_id) const;
};

class FilesWithRawResponse : Files
{
public:
  explicit FilesWithRawResponse(const Files& files) : Files(files) {}

  httplib::Response list() const;
  httplib::Response retrieve(const std::string& file_id) const;
  httplib::Response remove(const std::string& file_id) const;
};

}
