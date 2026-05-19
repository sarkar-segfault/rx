cmake_minimum_required(VERSION 3.12..4.3)

project(
  rx
  LANGUAGES C
  VERSION 0.1.0
  HOMEPAGE_URL "https://codeberg.org/adhritsarkar/rx"
  DESCRIPTION "A rendering library for simpletons and wizards alike"
)

option(RX_FETCH_DEPS "Whether to fetch dependencies; disable if they are already installed" ON)

option(RX_TESTING "Whether to build tests and enable CTest integration" OFF)

add_library(
  rx
  sources/engine.c
  sources/device.c
)

if(BUILD_SHARED_LIBS)
  target_compile_definitions(rx PRIVATE RX_SHARED)
endif()

target_compile_definitions(rx PRIVATE RX_BUILD)

target_compile_definitions(
  rx PUBLIC
  RX_VERSION="${PROJECT_VERSION}"
  RX_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
  RX_VERSION_MINOR=${PROJECT_VERSION_MINOR}
  RX_VERSION_MICRO=${PROJECT_VERSION_PATCH}
)

target_include_directories(rx PUBLIC headers)

target_compile_features(rx PUBLIC c_std_99)

if(WIN32)
  set(WGPU_OS "windows")
elseif(APPLE)
  set(WGPU_OS "macos")
elseif(UNIX)
  set(WGPU_OS "linux")
else()
  message(FATAL_ERROR "Unsupported OS")
endif()

message(STATUS "WGPU_OS = ${WGPU_OS}")

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64|AMD64")
  set(WGPU_ARCH "x86_64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64|ARM64")
  set(WGPU_ARCH "aarch64")
else()
  message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

message(STATUS "WGPU_ARCH = ${WGPU_ARCH}")

set(WGPU_TOOLCHAIN "")

if(WIN32)
  if(MSVC)
    set(WGPU_TOOLCHAIN_USER "msvc")
  else()
    set(WGPU_TOOLCHAIN_USER "gnu")
  endif()
  message(STATUS "WGPU_TOOLCHAIN = ${WGPU_TOOLCHAIN_USER}")
  set(WGPU_TOOLCHAIN "-${WGPU_TOOLCHAIN_USER}")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(WGPU_BUILD_TYPE "debug")
else()
  set(WGPU_BUILD_TYPE "release")
endif()

message(STATUS "WGPU_BUILD_TYPE = ${WGPU_BUILD_TYPE}")

set(
  WGPU_URL
  "https://github.com/gfx-rs/wgpu-native/releases/download/v29.0.0.0/wgpu-${WGPU_OS}-${WGPU_ARCH}${WGPU_TOOLCHAIN}-${WGPU_BUILD_TYPE}.zip"
)

set(WGPU_ARCHIVE_PATH "${CMAKE_BINARY_DIR}/wgpu-native.zip")
set(WGPU_EXTRACT_PATH "${CMAKE_BINARY_DIR}/wgpu-native")

if(NOT EXISTS "${WGPU_EXTRACT_PATH}")
  message(STATUS "Downloading ${WGPU_URL} to ${WGPU_ARCHIVE_PATH}...")
  file(
    DOWNLOAD
    ${WGPU_URL}
    ${WGPU_ARCHIVE_PATH}
    STATUS WGPU_DOWNLOAD_STATUS
    TLS_VERIFY ON
  )

  list(GET WGPU_DOWNLOAD_STATUS 0 WGPU_DOWNLOAD_EXIT_CODE)
  if(WGPU_DOWNLOAD_EXIT_CODE EQUAL 0)
    message(STATUS "Finished!")
  else()
    message(FATAL_ERROR "Failed with exit code ${WGPU_DOWNLOAD_EXIT_CODE}!")
  endif()

  message(STATUS "Extracting ${WGPU_ARCHIVE_PATH} to ${WGPU_EXTRACT_PATH}")
  file(
    ARCHIVE_EXTRACT
    INPUT ${WGPU_ARCHIVE_PATH}
    DESTINATION ${WGPU_EXTRACT_PATH}
  )
  message(STATUS "Finished!")
endif()

message(STATUS "Copying ${WGPU_EXTRACT_PATH}/lib to ${CMAKE_BINARY_DIR}...")
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  "${WGPU_EXTRACT_PATH}/lib"
  "${CMAKE_BINARY_DIR}"
  RESULT_VARIABLE WGPU_COPY_EXIT_CODE
)

if(NOT WGPU_COPY_EXIT_CODE EQUAL 0)
  message(FATAL_ERROR "Failed with exit code ${WGPU_COPY_EXIT_CODE}!")
else()
  message(STATUS "Finished!")
endif()

if(WIN32)
  set(WGPU_LIBRARY "wgpu_native.dll.lib")
elseif(APPLE)
  set(WGPU_LIBRARY "libwgpu_native.dylib")
elseif(UNIX)
  set(WGPU_LIBRARY "libwgpu_native.so")
endif()

target_include_directories(rx PRIVATE "${WGPU_EXTRACT_PATH}/include")
target_link_libraries(rx PRIVATE "${CMAKE_BINARY_DIR}/${WGPU_LIBRARY}")

if(RX_TESTING)
  if (RX_FETCH_DEPS)
    include(FetchContent)
    set(VX_URL "https://codeberg.org/adhritsarkar/vx.git")

    FetchContent_Declare(
      vx
      GIT_REPOSITORY "${VX_URL}"
      GIT_TAG main
      GIT_SHALLOW ON
    )

    message(STATUS "Fetching ${VX_URL} (for testing)...")
    FetchContent_MakeAvailable(vx)
    message(STATUS "Finished!")
  endif()

  function(rx_test name)
    add_executable(${name} tests/${name}.c)
    target_link_libraries(${name} PRIVATE vx rx)
    add_test(NAME ${name} COMMAND ${name})
  endfunction()

  rx_test(Basic)
  enable_testing()
endif()
