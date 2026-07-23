cmake_minimum_required(VERSION 3.15)
project(FPS_Steer_Fix CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED PLUGIN_SDK_DIR)
    set(PLUGIN_SDK_DIR "C:/plugin-sdk")
endif()

# Header Dizinleri
include_directories(
    ${PLUGIN_SDK_DIR}/plugin_sa
    ${PLUGIN_SDK_DIR}/plugin_sa/game_sa
    ${PLUGIN_SDK_DIR}/plugin_sa/game_sa/rw
    ${PLUGIN_SDK_DIR}/plugin_sa/game_sa/enums
    ${PLUGIN_SDK_DIR}/plugin_common
    ${PLUGIN_SDK_DIR}/plugin_common/game
    ${PLUGIN_SDK_DIR}/shared
    ${PLUGIN_SDK_DIR}/shared/game
    ${PLUGIN_SDK_DIR}/shared/rw
    ${PLUGIN_SDK_DIR}/injector
    ${PLUGIN_SDK_DIR}/safetyhook
)

# Premake tarafından üretilen .lib dosyalarının konumu
link_directories(
    ${PLUGIN_SDK_DIR}/output/lib
    ${PLUGIN_SDK_DIR}/output/lib/Release
    ${PLUGIN_SDK_DIR}/shared/bass
)

add_library(FPS_Steer_Fix SHARED main.cpp)

set_target_properties(FPS_Steer_Fix PROPERTIES SUFFIX ".asi")

# Statik C++ Runtime (Geçersiz Win32 Uygulaması hatasını önler)
set_target_properties(FPS_Steer_Fix PROPERTIES
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

target_compile_definitions(FPS_Steer_Fix PRIVATE 
    GTASA=1 
    _CRT_SECURE_NO_WARNINGS 
    RwObjects=1 
    RW=1
)

# Kütüphane bağlama
target_link_libraries(FPS_Steer_Fix PRIVATE plugin_sa bass)

if(MSVC)
    target_compile_options(FPS_Steer_Fix PRIVATE /std:c++latest)
endif()
