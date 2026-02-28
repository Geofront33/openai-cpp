#include <openai/client/OpenAIClient.h>
#include <openai/utils/OpenAIError.h>
#include <openai/utils/utils.h>

namespace openai
{

OpenAI::OpenAI() : OpenAI(OpenAIClientOpts{}) {}

OpenAI::OpenAI(const OpenAIClientOpts& opts) {
  if(opts.api_key.empty()) {
    api_key = getenv_or_empty("OPENAI_API_KEY");
    if(api_key.empty()) {
      throw OpenAIError(
        "The api_key client option must be set either by passing api_key to the client or by setting the OPENAI_API_KEY environment variable"
      );
    }
  } else {
    api_key = opts.api_key;
  }

  if(opts.organization.empty()) {
    organization = getenv_or_empty("OPENAI_ORG_ID");
  } else {
    organization = opts.organization;
  }

  if(opts.project.empty()) {
    project = getenv_or_empty("OPENAI_PROJECT_ID");
  } else {
    project = opts.project;
  }

  if(opts.webhook_secret.empty()) {
    webhook_secret = getenv_or_empty("OPENAI_WEBHOOK_SECRET");
  } else {
    webhook_secret = opts.webhook_secret;
  }

  websocket_base_url = opts.websocket_base_url;

  if(opts.base_url.empty()) {
    base_url = getenv_or_empty("OPENAI_BASE_URL");
    if(!base_url) {
      base_url = "https://api.openai.com/v1";
    }
  } else {
    base_url = opts.base_url;
  }

  client = std::make_unique<httplib::SSLClient>(base_url.host, base_url.port);
}

const Embeddings& OpenAI::embeddings() {
  std::call_once(f_images, [this] {
    embeddings_ = std::make_unique<Embeddings>(*this);
  });
  return *embeddings_;
}

const Images& OpenAI::images() {
  std::call_once(f_images, [this] {
    images_ = std::make_unique<Images>(*this);
  });
  return *images_;
}

const Moderations& OpenAI::moderations() {
  std::call_once(f_moderations, [this] {
    moderations_ = std::make_unique<Moderations>(*this);
  });
  return *moderations_;
}

const Models& OpenAI::models() {
  std::call_once(f_models, [this] {
    models_ = std::make_unique<Models>(*this);
  });
  return *models_;
}

}
