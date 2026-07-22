cmake_minimum_required(VERSION 3.15)
project(FPS_Steer_Fix CXX)

# SafetyHook ve Modern C++23 Desteği
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED PLUGIN_SDK_DIR)
    set(PLUGIN_SDK_DIR "C:/plugin-sdk")
endif()

# Plugin-SDK içindeki TÜM alt klasörleri otomatik bulan ve ekleyen dinamik tarama
file(GLOB_RECURSE ALL_SDK_HEADERS "${PLUGIN_SDK_DIR}/*.h" "${PLUGIN_SDK_DIR}/*.hpp")
set(SDK_INCLUDE_DIRS "")
foreach(HEADER_FILE ${ALL_SDK_HEADERS})
    get_filename_component(HEADER_DIR ${HEADER_FILE} DIRECTORY)
    list(APPEND SDK_INCLUDE_DIRS ${HEADER_DIR})
endforeach()
list(REMOVE_DUPLICATES SDK_INCLUDE_DIRS)

include_directories(${SDK_INCLUDE_DIRS})

link_directories(
    ${PLUGIN_SDK_DIR}/output/lib
)

add_library(FPS_Steer_Fix SHARED main.cpp)

set_target_properties(FPS_Steer_Fix PROPERTIES SUFFIX ".asi")

# Makrolar ve MSVC Derleyici Bayrakları
target_compile_definitions(FPS_Steer_Fix PRIVATE GTASA _CRT_SECURE_NO_WARNINGS)

if(MSVC)
    target_compile_options(FPS_Steer_Fix PRIVATE /std:c++latest)
endif()
