#pragma once
#include <openai/third_party/nlohmann/json.h>

namespace openai
{

inline std::string getenv_or_empty(const char* name) {
  if (const char* p = std::getenv(name)) {
    return {p};
  }
  return {};
}

static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

inline std::vector<unsigned char> b64decode(const std::string& encoded) {
  std::vector<unsigned char> decoded;
  std::vector<int> T(256, -1);

  for (int i = 0; i < 64; i++)
    T[base64_chars[i]] = i;

  int val = 0, valb = -8;

  for (unsigned char c : encoded) {
    if (T[c] == -1) break;
    val = (val << 6) + T[c];
    valb += 6;
    if (valb >= 0) {
      decoded.push_back(static_cast<unsigned char>((val >> valb) & 0xFF));
      valb -= 8;
    }
  }

  return decoded;
}

template <class T>
std::optional<T> get_opt(const nlohmann::json& j, const std::string_view key) {
  const auto it = j.find(std::string(key));
  if (it == j.end() || it->is_null())
    return std::nullopt;
  return it->get<T>();
}

}

