#include <openai/types/file_deleted.h>
#include <sstream>

namespace openai
{

std::string FileDeleted::to_string() const {
  std::ostringstream oss;
  oss << "FileDeleted" << "(";
  oss << "id='" << id << "'";
  oss << ", deleted=" << deleted;
  oss << ", object='" << object << "'";
  oss << ")";
  return oss.str();
}

void from_json(const nlohmann::json& j, FileDeleted& file_deleted) {
  j.at("id").get_to(file_deleted.id);
  j.at("deleted").get_to(file_deleted.deleted);
  j.at("object").get_to(file_deleted.object);
}

}
