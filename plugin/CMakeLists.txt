cmake_minimum_required(VERSION 3.25.0)
project(VST3RVC VERSION 0.1.0 LANGUAGES CXX)

# Path to Steinberg VST3 SDK (submodule)
set(VST3_SDK_ROOT "${CMAKE_SOURCE_DIR}/../external/vst3sdk" CACHE PATH "Path to VST3 SDK root")
# Include VST3 SDK CMake infrastructure
list(APPEND CMAKE_MODULE_PATH "${VST3_SDK_ROOT}/cmake/modules")
## Disable VSTGUI support to avoid macOS Xcode dependency if not needed
set(SMTG_ENABLE_VSTGUI_SUPPORT OFF CACHE BOOL "Disable VSTGUI support" FORCE)
# Include VST3 SDK
include(SMTG_VST3_SDK)

# Find ONNX Runtime for RVC inference (optional)
find_package(onnxruntime QUIET)
if(NOT TARGET onnxruntime::onnxruntime)
  message(WARNING "ONNX Runtime not found; RVC inference will be disabled.")
else()
  message(STATUS "ONNX Runtime found; enabling RVC inference support.")
endif()

# Find curl CLI for HTTP API control
find_program(CURL_PROGRAM curl)
if(NOT CURL_PROGRAM)
  message(WARNING "curl not found; HTTP-based API control will not be available.")
endif()

# Custom target zur Einrichtung des Python-RVC-Servers
find_program(BASH_EXEC bash)
if(BASH_EXEC)
  add_custom_target(setup_rvc_server
    COMMAND "${BASH_EXEC}" "${CMAKE_SOURCE_DIR}/../tools/setup_rvc_server.sh"
    COMMENT "Setup Python RVC API-Server environment"
  )
endif()

# Configure platform toolset and symbol visibility
smtg_setup_platform_toolset()
smtg_setup_symbol_visibility()

# Plugin settings
set(PRODUCT_NAME "VST3RVC")
set(COMPANY_NAME "Whykiki")
set(CATEGORY "Instrument|Synth")

# Source files
set(SOURCE_FILES
    source/pluginprocessor.cpp
    source/plugincontroller.cpp
    source/modelmanager.cpp
)
set(HEADER_FILES
    source/pluginprocessor.h
    source/plugincontroller.h
    source/version.h
    source/modelmanager.h
)

# Define the plugin component using SMTG macro
smtg_add_vst3plugin(${PROJECT_NAME}
    PRODUCT_NAME "${PRODUCT_NAME}"
    COMPANY_NAME "${COMPANY_NAME}"
    CATEGORY "${CATEGORY}"
    SOURCES ${SOURCE_FILES} ${HEADER_FILES}
)

# Setup plugin as VST3 example (sets install rules, C++ standard, bundle ID)
# Setup plugin as example and install rules
smtg_target_setup_as_vst3_example(${PROJECT_NAME})

# Copy RVC model assets to plugin binary for runtime access
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets/models
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/../assets/models
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets/models
)

# Link ONNX Runtime if available
if(TARGET onnxruntime::onnxruntime)
  target_link_libraries(${PROJECT_NAME} PRIVATE onnxruntime::onnxruntime)
endif()
