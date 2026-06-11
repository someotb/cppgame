cmake_minimum_required(VERSION 3.19)

project(cppgame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/source)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)

set(SRC_BIN
  ${SRC_DIR}/enemy.cpp
  ${SRC_DIR}/common.cpp
  ${SRC_DIR}/player.cpp
  ${SRC_DIR}/main.cpp
)

add_executable(${PROJECT_NAME}
  ${SRC_BIN}
)

find_package(SFML 2 REQUIRED COMPONENTS graphics window system)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR})
