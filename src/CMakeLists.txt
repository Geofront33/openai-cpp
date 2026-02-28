include(GNUInstallDirs)

add_library(openai-cpp STATIC
    service/Embeddings.cpp
    service/Images.cpp
    service/Models.cpp
    client/APIClient.cpp
    client/BaseClient.cpp
    client/OpenAIClient.cpp
)

set_target_properties(openai-cpp PROPERTIES OUTPUT_NAME openai)

if (WIN32)
  target_link_libraries(openai-cpp PUBLIC ws2_32 crypt32)
endif()

find_package(OpenSSL REQUIRED)
# Enable HTTPS support in yhirose/cpp-httplib (must be defined before including httplib.h)
target_compile_definitions(openai-cpp PUBLIC CPPHTTPLIB_OPENSSL_SUPPORT)
# Link OpenSSL for SSLClient / TLS
target_link_libraries(openai-cpp PUBLIC OpenSSL::SSL OpenSSL::Crypto)

target_include_directories(openai-cpp PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS openai-cpp ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
