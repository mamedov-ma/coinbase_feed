cmake_minimum_required(VERSION 3.14)
project(HFT_Ticker_EMA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -Wall")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# nlohmann/json
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)
include(FetchContent)

find_package(Threads REQUIRED)
find_package(BZip2 REQUIRED)
find_package(ixwebsocket REQUIRED)

set(SOURCES
    src/main.cpp
    src/ticker_data.cpp
    src/ema_calculator.cpp
    src/csv_logger.cpp
)

set(HEADERS
    src/ticker_data.hpp
    src/ema_calculator.hpp
    src/csv_logger.hpp
)

add_executable(coinbase_ws_ix ${SOURCES} ${HEADERS})
target_link_libraries(coinbase_ws_ix
    PRIVATE
        ixwebsocket::ixwebsocket
        pthread
        ssl
        crypto
        BZip2::BZip2
        nlohmann_json::nlohmann_json
)

enable_testing()

add_executable(test_ema test/test_ema.cpp src/ema_calculator.cpp src/ema_calculator.hpp)
target_link_libraries(test_ema PRIVATE gtest_main)
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(test_parser test/test_parser.cpp src/ticker_data.cpp src/ticker_data.hpp)
target_link_libraries(test_parser PRIVATE gtest_main nlohmann_json::nlohmann_json)
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include(GoogleTest)
gtest_discover_tests(test_ema)
gtest_discover_tests(test_parser)