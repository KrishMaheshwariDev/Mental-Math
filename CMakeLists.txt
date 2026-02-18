cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   

project(Mental-Math-Engine)
add_executable(MentalMath 
    "src/main.cpp"
    "src/engine/States.cpp"
    "src/profile/profile.cpp"
)

target_include_directories(MentalMath PUBLIC include)