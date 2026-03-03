#include <openai/types/file_object.h>
#include <openai/utils/utils.h>

namespace openai
{

std::string FileObject::to_string() const {
  std::ostringstream oss;
  oss << "FileObject" << "(";
  oss << "id='" << id << "'";
  oss << ", bytes=" << bytes;
  oss << ", created_at=" << created_at;
  oss << ", filename='" << filename << "'";
  oss << ", object='" << object << "'";
  oss << ", purpose='" << purpose << "'";
  if (expires_at) {
    oss << ", expires_at=" << *expires_at;
  }
  oss << ")";
  return oss.str();
}

void from_json(const nlohmann::json& j, FileObject& file_object) {
  j.at("id").get_to(file_object.id);
  j.at("bytes").get_to(file_object.bytes);
  j.at("created_at").get_to(file_object.created_at);
  j.at("filename").get_to(file_object.filename);
  j.at("object").get_to(file_object.object);
  j.at("purpose").get_to(file_object.purpose);
  get_opt(j, "expires_at", file_object.expires_at);
}

}
