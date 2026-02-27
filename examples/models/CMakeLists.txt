add_executable(test_models test_models.cpp)

target_link_libraries(test_models PRIVATE openai-cpp)
