cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 11)

# Define the project
project (core-client)

add_subdirectory (google-tests)
add_subdirectory (tests)
add_subdirectory (ThirdParty/googletest)
