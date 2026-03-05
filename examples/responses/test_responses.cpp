#include <openai.h>

int main() {
  openai::OpenAI client;

  std::cout << "[responses.create]" << std::endl;
  const auto res = client.responses().create_raw({
    .input = "Tell me a three sentence bedtime story about a unicorn.",
    .model = "gpt-4.1",
  });
  std::cout << res.body << std::endl;

  return 0;
}
