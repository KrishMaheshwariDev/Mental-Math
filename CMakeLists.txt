cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   

project(Mental-Math-Engine)

add_executable(MentalMath)

file(GLOB ENGINE_SOURCES "src/engine/*.cpp")
file(GLOB PROFILE_SOURCES "src/profile/*.cpp")
file(GLOB QUESTION_SOURCES "src/questions/*.cpp")

target_sources(MentalMath PRIVATE
    src/main.cpp
    ${ENGINE_SOURCES}
    ${PROFILE_SOURCES}
    ${QUESTION_SOURCES}
)   

target_include_directories(MentalMath PUBLIC include)
target_include_directories(MentalMath PRIVATE libs)