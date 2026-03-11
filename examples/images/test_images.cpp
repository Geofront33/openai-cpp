#include <fstream>
#include <iostream>
#include <openai.h>
#include <openai/utils/utils.h>

int main() {
  openai::OpenAI client;

  std::cout << "[images.generate]" << std::endl;
  const auto generated = client.images().generate({
    .prompt = "A cute baby sea otter",
    .model = "gpt-image-1.5",
    .n = 1,
    .output_compression = 100,
    .output_format = "png",
    .size = "1024x1024",
    .user = "demo-user",
  });
  const auto generated_data = openai::b64decode(generated.data[0].b64_json);

  std::ofstream out("output.png", std::ios::binary);
  out.write(reinterpret_cast<const char*>(generated_data.data()), static_cast<std::streamsize>(generated_data.size()));
  out.close();

  std::cout << "[images.edit]" << std::endl;
  const auto edited = client.images().edit({
    .image_paths = {"output.png"},
    .prompt = "Turn this into a watercolor painting",
    .model = "gpt-image-1.5",
    .output_format = "png",
  });
  const auto edited_data = openai::b64decode(edited.data[0].b64_json);
  std::ofstream edited_out("output_edit.png", std::ios::binary);
  edited_out.write(reinterpret_cast<const char*>(edited_data.data()), static_cast<std::streamsize>(edited_data.size()));
  edited_out.close();

  std::cout << "[images.variation]" << std::endl;
  const auto variation = client.images().create_variation({
    .image_path = "output.png",
    .model = "dall-e-2",
    .n = 1,
    .response_format = "b64_json",
    .size = "256x256",
  });
  const auto variation_data = openai::b64decode(variation.data[0].b64_json);
  std::ofstream variation_out("output_variation.png", std::ios::binary);
  variation_out.write(
    reinterpret_cast<const char*>(variation_data.data()),
    static_cast<std::streamsize>(variation_data.size())
  );
  variation_out.close();

  return 0;
}
