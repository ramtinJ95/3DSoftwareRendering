cmake_minimum_required(VERSION 3.26)
project(main)

# Source and header directories
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_OSX_ARCHITECTURES arm64 CACHE STRING "" FORCE)

# Recursively collect all source files in src/
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${INCLUDE_DIR}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_definitions(${PROJECT_NAME} PRIVATE IMGDIR="../img/")
target_compile_options(${PROJECT_NAME} PRIVATE -mcpu=apple-m4)

# SDL2 setup
list(APPEND CMAKE_MODULE_PATH "/usr/local/lib/cmake/SDL2" "/opt/homebrew/lib/cmake/SDL2")
list(APPEND CMAKE_PREFIX_PATH "/usr/local" "/opt/homebrew")

find_package(SDL2 QUIET)

if (SDL2_FOUND)
  message("Using SDL2 from find_package")
  target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
else()
  include(FindPkgConfig)
  pkg_search_module(SDL2 REQUIRED sdl2)
  message("Using SDL2 from pkg-config")
  target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
endif()
