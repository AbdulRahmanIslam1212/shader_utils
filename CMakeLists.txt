cmake_minimum_required(VERSION 3.16)
project(shader_utils VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# <sstream>, <fstream>, and <iostream> are part of the C++ standard library.
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# Replace with your actual source file(s)
add_library(shader_utils
    src/shader_utils.cpp
)
add_library(shader_utils::shader_utils ALIAS shader_utils)

target_include_directories(shader_utils
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(shader_utils
    PUBLIC
        glad::glad
        OpenGL::GL
)

# Install library binary and export target metadata
install(TARGETS shader_utils
    EXPORT shader_utilsTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install public headers (e.g., include/shader_utils/shader.h)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Generate and install CMake package config files for find_package(shader_utils)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/shader_utilsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/shader_utilsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/shader_utilsConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/shader_utils
)

install(EXPORT shader_utilsTargets
    FILE shader_utilsTargets.cmake
    NAMESPACE shader_utils::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/shader_utils
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/shader_utilsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/shader_utilsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/shader_utils
)
