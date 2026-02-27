#include <fstream>
#include <iostream>
#include <openai.h>
#include <openai/utils/utils.h>

int main() {
  openai::OpenAI client;

  std::cout << "[embeddings.create]" << std::endl;
  const auto res = client.embeddings().create({
    .input = "The food was delicious and the waiter...",
    .model = "text-embedding-ada-002",
    .encoding_format = "float",
  });
  for (const auto& i : res) {
    std::cout << i.to_string() << std::endl;
  }

  return 0;
}
