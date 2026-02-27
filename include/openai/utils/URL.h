#pragma once
#include <string>

namespace openai
{

class URL
{
public:
  URL& operator=(const std::string& url) {
    std::string u = url;

    // 1. Parse schema (default https if missing)
    if (const auto scheme_pos = u.find("://"); scheme_pos != std::string::npos) {
      schema = u.substr(0, scheme_pos);
      u.erase(0, scheme_pos + 3);
    } else {
      schema = "https"; // default
    }

    // 2. Split host[:port] and path
    std::string host_port;
    if (const auto path_pos = u.find('/'); path_pos != std::string::npos) {
      host_port = u.substr(0, path_pos);
      path = u.substr(path_pos);
    } else {
      host_port = u;
      path = "";
    }

    // 3. Parse host and port
    if (const auto colon_pos = host_port.find(':'); colon_pos != std::string::npos) {
      host = host_port.substr(0, colon_pos);
      port = std::stoi(host_port.substr(colon_pos + 1));
    } else {
      host = host_port;
      // Default port based on schema
      if (schema == "https") {
        port = 443;
      } else {
        port = 80;
      }
    }
    return *this;
  }

  explicit operator bool() const noexcept {
    return !path.empty();
  }

  std::string schema;
  std::string host;
  int port;
  std::string path;
};

}
