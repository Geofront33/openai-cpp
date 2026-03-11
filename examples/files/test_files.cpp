#include <openai.h>

int main() {
  openai::OpenAI client;

  std::cout << "[file.create]" << std::endl;
  const auto created = client.files().create({
    .file_path = "/Users/wrx/Workspace/clion/openai-cpp/examples/files/test_files.cpp",
    .purpose = "assistants",
  });
  std::cout << created.to_string() << std::endl;

  std::cout << "[file.list]" << std::endl;
  const auto listed = client.files().list({
    .purpose = "assistants",
    .limit = 10,
    .order = "desc",
  });
  for (const auto& i : listed) {
    std::cout << i.to_string() << std::endl;
  }

  std::cout << "[file.retrieve]" << std::endl;
  std::cout << client.files().retrieve(created.id).to_string() << std::endl;

  std::cout << "[file.content]" << std::endl;
  std::cout << client.files().content(created.id).body << std::endl;

  std::cout << "[file.delete]" << std::endl;
  std::cout << client.files().remove(created.id).to_string() << std::endl;

  return 0;
}
