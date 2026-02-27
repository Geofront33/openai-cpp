#include <openai.h>

int main() {
  openai::OpenAI client;

  std::cout << "[models.retrieve]" << std::endl;
  std::cout << client.models().retrieve("gpt-4").to_string() << std::endl;

  std::cout << "[models.list]" << std::endl;
  const auto res = client.models().list();
  for (const auto& i : res) {
    std::cout << i.to_string() << std::endl;
  }

  return 0;
}
