cmake_minimum_required(VERSION 3.10)
project(socketmaster)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find required packages
find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

# Add Abseil source dir for CMake to build
add_subdirectory("include/abseil-cpp")

# Add executable
add_executable(${PROJECT_NAME}
    src/main.cc
    src/server.cc
    src/session.cc
    src/port_manager.cc
    src/configuration.cc
    src/logger.cc
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${absl_INCLUDE_DIRS}
    include
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    Threads::Threads
    ${Boost_LIBRARIES}
    absl::base
    absl::strings
    absl::synchronization
    absl::flat_hash_map
)

# Install target (optional)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Add test directory (optional)
# add_subdirectory(tests)
