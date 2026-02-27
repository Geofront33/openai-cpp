#include <openai/service/Embeddings.h>
#include <openai/third_party/nlohmann/json.h>

namespace openai
{

httplib::Response EmbeddingsWithRawResponse::create(const EmbeddingsCreateOpts& opts) const {
  return Post("/embeddings", opts.validate_and_serialize());
}

const EmbeddingsWithRawResponse& Embeddings::with_raw_response() const {
  return static_cast<const EmbeddingsWithRawResponse&>(*this);
}

std::vector<Embedding> Embeddings::create(const EmbeddingsCreateOpts& opts) const {
  return nlohmann::json::parse(with_raw_response().create(opts).body)["data"].get<std::vector<Embedding>>();
}

std::string EmbeddingsWithRawResponse::EmbeddingsCreateOpts::validate_and_serialize() const {
  nlohmann::json j;

  assert(!input.empty());
  j["input"] = input;
  assert(!model.empty());
  j["model"] = model;
  if (dimensions) {
    j["dimensions"] = dimensions;
  }
  if (!encoding_format.empty()) {
    assert(encoding_format == "float" || encoding_format == "base64");
    j["encoding_format"] = encoding_format;
  }

  return j.dump();
}

}
