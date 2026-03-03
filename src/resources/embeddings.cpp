#include <openai/resources/embeddings.h>
#include <openai/third_party/nlohmann/json.h>

namespace openai
{

EmbeddingsWithRawResponse Embeddings::with_raw_response() const {
  return EmbeddingsWithRawResponse(*this);
}

EmbeddingCreateResponse Embeddings::create(const EmbeddingsCreateOpts& opts) const {
  return nlohmann::json::parse(create_raw(opts).body).get<EmbeddingCreateResponse>();
}

httplib::Response Embeddings::create_raw(const EmbeddingsCreateOpts& opts) const {
  return Post("/embeddings", opts.validate_and_serialize());
}

httplib::Response EmbeddingsWithRawResponse::create(const EmbeddingsCreateOpts& opts) const {
  return create_raw(opts);
}

std::string Embeddings::EmbeddingsCreateOpts::validate_and_serialize() const {
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
