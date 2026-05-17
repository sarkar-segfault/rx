cmake_minimum_required(VERSION 3.12..4.3)

project(
  Rx
  LANGUAGES C
  VERSION 0.1.0
  HOMEPAGE_URL "https://codeberg.org/adhritsarkar/Rx"
  DESCRIPTION "A rendering library for simpletons and wizards alike"
)

option(Rx_FetchDependencies "Whether to fetch dependencies; disable if they are already installed" ON)

option(Rx_Testing "Whether to build tests and enable CTest integration" OFF)

add_library(
  Rx
  Sources/Engine.c
  Sources/DeviceSpec.c
  Sources/Device/Core.c
)

if(BUILD_SHARED_LIBS)
  target_compile_definitions(Rx PRIVATE Rx_Shared)
endif()

target_compile_definitions(Rx PRIVATE Rx_Build)

target_compile_definitions(
  Rx PUBLIC
  Rx_Version="${PROJECT_VERSION}"
  Rx_VersionMajor=${PROJECT_VERSION_MAJOR}
  Rx_VersionMinor=${PROJECT_VERSION_MINOR}
  Rx_VersionMicro=${PROJECT_VERSION_PATCH}
)

target_include_directories(Rx PUBLIC Headers)

target_compile_features(Rx PUBLIC c_std_99)

if(WIN32)
    set(WGPU_NATIVE_OS "windows")
elseif(APPLE)
    set(WGPU_NATIVE_OS "macos")
elseif(UNIX)
    set(WGPU_NATIVE_OS "linux")
else()
    message(FATAL_ERROR "Unsupported OS")
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64|AMD64")
    set(WGPU_NATIVE_ARCH "x86_64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64|ARM64")
    set(WGPU_NATIVE_ARCH "aarch64")
else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

set(WGPU_NATIVE_TOOLCHAIN "")

if(WIN32)
    if(MSVC)
        set(WGPU_NATIVE_TOOLCHAIN "-msvc")
    else()
        set(WGPU_NATIVE_TOOLCHAIN "-gnu")
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(WGPU_NATIVE_BUILD_TYPE "debug")
else()
    set(WGPU_NATIVE_BUILD_TYPE "release")
endif()

set(
  WGPU_NATIVE_URL
  "https://github.com/gfx-rs/wgpu-native/releases/download/v29.0.0.0/wgpu-${WGPU_NATIVE_OS}-${WGPU_NATIVE_ARCH}${WGPU_NATIVE_TOOLCHAIN}-${WGPU_NATIVE_BUILD_TYPE}.zip"
)

set(WGPU_NATIVE_ARCHIVE_PATH "${CMAKE_BINARY_DIR}/wgpu-native.zip")
set(WGPU_NATIVE_EXTRACT_PATH "${CMAKE_BINARY_DIR}/wgpu-native")

if(NOT EXISTS "${WGPU_NATIVE_EXTRACT_PATH}")
  file(
    DOWNLOAD
    ${WGPU_NATIVE_URL}
    ${WGPU_NATIVE_ARCHIVE_PATH}
    STATUS WGPU_DOWNLOAD_STATUS
    TLS_VERIFY ON
  )

  list(GET WGPU_DOWNLOAD_STATUS 0 WGPU_DOWNLOAD_STATUS_CODE)
  if(WGPU_DOWNLOAD_STATUS_CODE EQUAL 0)
    message(STATUS "${WGPU_NATIVE_URL} downloaded to ${WGPU_NATIVE_ARCHIVE_PATH}, with exit code ${WGPU_DOWNLOAD_STATUS_CODE}")
  else()
    message(FATAL_ERROR "${WGPU_NATIVE_URL} failed to download to ${WGPU_NATIVE_ARCHIVE_PATH}, with exit code ${WGPU_DOWNLOAD_STATUS_CODE}")
  endif()

  file(
    ARCHIVE_EXTRACT
    INPUT ${WGPU_NATIVE_ARCHIVE_PATH}
    DESTINATION ${WGPU_NATIVE_EXTRACT_PATH}
  )
  message(STATUS "Extracted ${WGPU_NATIVE_ARCHIVE_PATH} to ${WGPU_NATIVE_EXTRACT_PATH}")
endif()

target_include_directories(Rx PRIVATE ${WGPU_NATIVE_EXTRACT_PATH}/include)

find_library(
  WGPU_NATIVE_LIBRARY
  NAMES wgpu_native
  PATHS "${WGPU_NATIVE_EXTRACT_PATH}/lib"
  NO_DEFAULT_PATH
)

target_link_libraries(Rx PRIVATE ${WGPU_NATIVE_LIBRARY})

if(Rx_Testing)
  if (Rx_FetchDependencies)
    include(FetchContent)

    FetchContent_Declare(
      Vx
      GIT_REPOSITORY https://codeberg.org/adhritsarkar/Vx.git
      GIT_TAG main
    )

    FetchContent_MakeAvailable(Vx)
  endif()

  function(Rx_Test name)
      add_executable(${name} Tests/${name}.c)
      target_link_libraries(${name} PRIVATE Vx Rx)
      add_test(NAME ${name} COMMAND ${name})
  endfunction()

  Rx_Test(Basic)
  enable_testing()
endif()
