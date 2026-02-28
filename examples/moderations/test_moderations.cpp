#include <openai.h>

int main() {
  openai::OpenAI client;

  std::cout << "[moderations.create]" << std::endl;
  const auto res = client.moderations().create({
    .input = "I want to kill them."
  });
  std::cout << res.results[0].categories.to_string() << std::endl;

  return 0;
}
