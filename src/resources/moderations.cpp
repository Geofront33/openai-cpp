#include <openai/resources/moderations.h>

namespace openai
{

httplib::Response ModerationsWithRawResponse::create(const ModerationsCreateOpts& opts) const {
  return Post("/moderations", opts.validate_and_serialize());
}

const ModerationsWithRawResponse& Moderations::with_raw_response() const {
  return static_cast<const ModerationsWithRawResponse&>(*this);
}

ModerationCreateResponse Moderations::create(const ModerationsCreateOpts& opts) const {
  return nlohmann::json::parse(with_raw_response().create(opts).body).get<ModerationCreateResponse>();
}

std::string ModerationsWithRawResponse::ModerationsCreateOpts::validate_and_serialize() const {
  nlohmann::json j;

  assert(!input.empty());
  j["input"] = input;
  if (!model.empty()) {
    j["model"] = model;
  }

  return j.dump();
}

}
