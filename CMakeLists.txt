cmake_minimum_required(VERSION 3.10)

project(Doodler)

add_executable(Doodler ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc )

target_include_directories(Doodler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc )

add_library(Doodler_libs
  ${CMAKE_CURRENT_SOURCE_DIR}/src/spriteclass.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/platform.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/doodler.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/background.cc )

target_include_directories(Doodler_libs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc )

find_package(OpenGL REQUIRED)

target_link_libraries(Doodler Doodler_libs glfw GLEW OpenGL::GL SOIL )
