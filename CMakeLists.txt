cmake_minimum_required(VERSION 3.10)

project(JSONParserLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch nlohmann/json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.10.2  # Specify the desired version/tag
)

# Fetch the content only if it's not already available
if(NOT nlohmann_json_POPULATED)
    FetchContent_Populate(nlohmann_json)
endif()

# Add the source files
set(SOURCES
    json_parser.cpp
)

# Create the shared library
add_library(JSONParserLib SHARED ${SOURCES})

# Include directories
target_include_directories(JSONParserLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${nlohmann_json_SOURCE_DIR}/include)

# Set the installation destination for the library
install(TARGETS JSONParserLib
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

# Install the header files
install(FILES json_parser.h DESTINATION include)
