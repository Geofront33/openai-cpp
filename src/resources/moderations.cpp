#include <openai/resources/moderations.h>
#include <openai/utils/OpenAIError.h>

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

  if (const auto* s = std::get_if<std::string>(&input)) {
    if (s->empty()) {
      throw OpenAIError("Expected a non-empty value for `input`");
    }
    j["input"] = *s;
  } else if (const auto* a = std::get_if<std::vector<std::string>>(&input)) {
    if (a->empty()) {
      throw OpenAIError("Expected a non-empty value for `input`");
    }
    j["input"] = *a;
  } else {
    throw OpenAIError("Expected `input` to be either string or array of strings");
  }

  if (!model.empty()) {
    j["model"] = model;
  }

  return j.dump();
}

}
