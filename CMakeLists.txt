cmake_minimum_required(VERSION 3.16)
project(shader_utils VERSION 1.0.0 LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

find_package(OpenGL REQUIRED)

add_library(shader_utils
    src/shader_utils.cpp
    third_party/glad/src/gl.c
)
add_library(shader_utils::shader_utils ALIAS shader_utils)

target_include_directories(shader_utils
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(shader_utils
    PUBLIC
        OpenGL::GL
        ${CMAKE_DL_LIBS}
)

install(TARGETS shader_utils
    EXPORT shader_utilsTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/include/shader_utils
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include/gl
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include/KHR
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/shader_utilsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/shader_utilsConfig.cmake" [=[
@PACKAGE_INIT@
include(CMakeFindDependencyMacro)
find_dependency(OpenGL)
include("${CMAKE_CURRENT_LIST_DIR}/shader_utilsTargets.cmake")
check_required_components(shader_utils)
]=])

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
