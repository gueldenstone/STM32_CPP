cmake_minimum_required(VERSION 3.17)
project(stmlibxx
    VERSION 1.0.0
    LANGUAGES CXX C ASM
)
add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PUBLIC
        io.cpp
        gpio.cpp
        # libraryhacks.cpp
)
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(${PROJECT_NAME} CMSIS) 