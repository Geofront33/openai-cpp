#include <openai/types/image.h>

namespace openai
{

void from_json(const nlohmann::json& j, Image& image) {
  image.b64_json = j.value("b64_json", "");
  image.revised_prompt = j.value("revised_prompt", "");
  image.url = j.value("url", "");
}

}
