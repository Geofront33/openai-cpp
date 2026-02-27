#pragma once
#include <exception>
#include <utility>

namespace openai
{

class OpenAIError : public std::exception
{
  std::string message;

public:
  explicit OpenAIError(std::string message) : message(std::move(message)) {}

  [[nodiscard]] const char* what() const noexcept override {
    return message.c_str();
  }
};

}
