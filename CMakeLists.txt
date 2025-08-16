cmake_minimum_required(VERSION 3.26)
project(main)

# Export compile commands for clangd / LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Source and header directories
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Recursively collect all source files in src/
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${INCLUDE_DIR}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_definitions(${PROJECT_NAME} PRIVATE IMGDIR="../img/")

# Platform-specific compiler options
if(APPLE)
  set(CMAKE_OSX_ARCHITECTURES arm64 CACHE STRING "" FORCE)
  target_compile_options(${PROJECT_NAME} PRIVATE -mcpu=apple-m4)

  # SDL2 paths for macOS (Homebrew, /usr/local)
  list(APPEND CMAKE_MODULE_PATH "/usr/local/lib/cmake/SDL2" "/opt/homebrew/lib/cmake/SDL2")
  list(APPEND CMAKE_PREFIX_PATH "/usr/local" "/opt/homebrew")

elseif(UNIX AND NOT APPLE)
  target_compile_options(${PROJECT_NAME} PRIVATE -march=native)
endif()

# Find SDL2 and SDL2_image
find_package(SDL2 QUIET)
find_package(SDL2_image QUIET)

if (SDL2_FOUND AND SDL2_IMAGE_FOUND)
  message(STATUS "Using SDL2 and SDL2_image from find_package")
  target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

  # Only adjust RPATH if libraries are outside standard system paths
  if(UNIX AND NOT APPLE)
    foreach(lib_dir ${SDL2_LIBRARY_DIRS} ${SDL2_IMAGE_LIBRARY_DIRS})
      if(NOT lib_dir MATCHES "^/usr(/|$)")
        set_target_properties(${PROJECT_NAME} PROPERTIES
                    BUILD_RPATH "$ORIGIN/../lib"
                    INSTALL_RPATH "$ORIGIN/../lib"
                    INSTALL_RPATH_USE_LINK_PATH TRUE
                )
      endif()
    endforeach()
  endif()

else()
  # fallback to pkg-config
  find_package(PkgConfig REQUIRED)
  pkg_search_module(SDL2 REQUIRED sdl2)
  pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
  message(STATUS "Using SDL2 and SDL2_image from pkg-config")
  target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
endif()

