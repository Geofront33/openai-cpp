#include <openai.h>

int main() {
  openai::OpenAI client;

  std::cout << "[embeddings.create]" << std::endl;
  const auto res = client.embeddings().create({
    .input = "The food was delicious and the waiter...",
    .model = "text-embedding-ada-002",
    .encoding_format = "float",
  });
  std::cout << res.data[0].to_string() << std::endl;

  return 0;
}
