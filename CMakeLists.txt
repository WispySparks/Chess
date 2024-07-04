cmake_minimum_required(VERSION 3.28)
project("Chess")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
FILE(GLOB SOURCE_FILES "src/*.cpp")
add_executable(main ${SOURCE_FILES})
target_compile_options(main PRIVATE /W4)
# Copy binary to working directory
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:main> ${PROJECT_SOURCE_DIR}/main.exe 
)