add_executable(test_embeddings test_embeddings.cpp)

target_link_libraries(test_embeddings PRIVATE openai-cpp)
