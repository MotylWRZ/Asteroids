# Set a minimum CMake vversion
cmake_minimum_required(VERSION 3.0.2)

# Define our project name
project(Asteroids)

# Look for the SFML components we're interested in
find_package(SFML 2.4 COMPONENTS audio graphics window system REQUIRED)


# Define a list of our source files
include_directories(
		${PROJECT_SOURCE_DIR}/Include
		${PROJECT_SOURCE_DIR}/Source
)

# Find all source files
file(GLOB_RECURSE _source_list ${PROJECT_SOURCE_DIR} *.cpp* *.h* *.hpp*)

# Exclude the Build folder from the list of source files
list(FILTER _source_list EXCLUDE REGEX "${PROJECT_SOURCE_DIR}/Build/.*")

# Structure the source groups
foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

# Define our target executable based on the source files above
add_executable("${PROJECT_NAME}" "${_source_list}")

# Link our executable to SFML and its dependencies
target_link_libraries("${PROJECT_NAME}" sfml-audio sfml-graphics sfml-window sfml-system)

# Set our source directory as the startup directory for debugging
set_target_properties("${PROJECT_NAME}" PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
