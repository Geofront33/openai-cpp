#include <openai/resources/responses/responses.h>
#include <openai/third_party/nlohmann/json.h>

namespace openai
{

ResponsesWithRawResponse Responses::with_raw_response() const {
  return ResponsesWithRawResponse(*this);
}

httplib::Response Responses::create_raw(const ResponsesCreateOpts& opts) const {
  return Post("/responses", opts.validate_and_serialize());
}

httplib::Response ResponsesWithRawResponse::create(const ResponsesCreateOpts& opts) const {
  return create_raw(opts);
}

std::string Responses::ResponsesCreateOpts::validate_and_serialize() const {
  nlohmann::json j;

 if (auto* s = std::get_if<std::string>(&input)) {
   j["input"] = *s;
 }
  if (!model.empty()) {
    j["model"] = model;
  }

  return j.dump();
}

}

