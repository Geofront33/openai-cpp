#include <openai/resources/moderations.h>

namespace openai
{

ModerationsWithRawResponse Moderations::with_raw_response() const {
  return ModerationsWithRawResponse(*this);
}

ModerationCreateResponse Moderations::create(const ModerationsCreateOpts& opts) const {
  return nlohmann::json::parse(create_raw(opts).body).get<ModerationCreateResponse>();
}

httplib::Response Moderations::create_raw(const ModerationsCreateOpts& opts) const {
  return Post("/moderations", opts.validate_and_serialize());
}

httplib::Response ModerationsWithRawResponse::create(const ModerationsCreateOpts& opts) const {
  return create_raw(opts);
}

std::string Moderations::ModerationsCreateOpts::validate_and_serialize() const {
  nlohmann::json j;

  assert(!input.empty());
  j["input"] = input;
  if (!model.empty()) {
    j["model"] = model;
  }

  return j.dump();
}

}
