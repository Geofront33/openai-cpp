add_executable(test_images test_images.cpp)

target_link_libraries(test_images PRIVATE openai-cpp)
