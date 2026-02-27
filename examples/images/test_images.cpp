#include <fstream>
#include <iostream>
#include <openai.h>
#include <openai/utils/utils.h>

int main() {
  openai::OpenAI client;

  std::cout << "[images.generate]" << std::endl;
  const auto res = client.images().generate({
    .prompt = "A cute baby sea otter",
    .model = "dall-e-2",
    .n = 1,
    .response_format = "b64_json",
    .size = "256x256",
  });
  const auto image_data = openai::b64decode(res[0].b64_json);

  std::ofstream out("output.png", std::ios::binary);
  out.write(reinterpret_cast<const char*>(image_data.data()), static_cast<std::streamsize>(image_data.size()));
  out.close();

  return 0;
}
