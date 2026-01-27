cmake_minimum_required(VERSION 3.16)

project(Lunaria_Server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lunaria_Server Serveur/main_server.cpp)

target_compile_definitions(Lunaria_Server PRIVATE ASIO_STANDALONE)
target_link_libraries(Lunaria_Server PRIVATE pthread)
target_link_libraries(Lunaria_Server PRIVATE pthread pq)
