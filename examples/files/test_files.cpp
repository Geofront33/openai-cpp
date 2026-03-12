#include <openai.h>

int main() {
  openai::OpenAI client;

  std::cout << "[file.list]" << std::endl;
  const auto res = client.files().list();
  for (const auto& i : res) {
    std::cout << i.to_string() << std::endl;
  }

  std::cout << "[file.retrieve]" << std::endl;
  std::cout << client.files().retrieve(res[0].id).to_string() << std::endl;

  std::cout << "[file.delete]" << std::endl;
  std::cout << client.files().remove(res[0].id).to_string() << std::endl;

  std::cout << "[file.content]" << std::endl;
  std::cout << client.files().content(res[0].id).body << std::endl;

  return 0;
}
