cmake_minimum_required(VERSION 3.17)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
# set(CMAKE_GENERATOR Unix)
include("${CMAKE_CURRENT_LIST_DIR}/project-meta-info.cmake")

# Define a project for the current CMakeLists.txt.
project(${project_name}
    VERSION ${project_version} 
    DESCRIPTION ${project_description} 
    HOMEPAGE_URL ${project_homepage}
    LANGUAGES C CXX ASM )
set(TARGET_NAME CMAKE_STM32 CACHE INTERNAL "the main targets name")

# Local CMake Module Path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake)

# The main Executable
add_executable(${TARGET_NAME})

# include the stm32 script
include(stm32)
# check for defined STM32 CHIP
if(NOT CHIP_NAME)
    message(FATAL_ERROR "No Chip specified!")
else()
    message(STATUS "Setting common properties!")
    stm32_set_target_common_properties(${TARGET_NAME} ${CHIP_NAME})
endif()
# add sources
add_subdirectory(src)
target_include_directories(${TARGET_NAME}
    PUBLIC
    include
)

# include CMSIS & HAL
add_subdirectory(${STM32_CUBE_DIR} ${STM32_CUBE_DIR}/build)
target_link_libraries(${TARGET_NAME} CMSIS)
if(USE_HAL_DRIVER)
    target_link_libraries(${TARGET_NAME} HAL_DRIVER)
endif()
if(USE_LL_DRIVER)
    target_link_libraries(${TARGET_NAME} LL_DRIVER)
endif()

# -------------------- Configure tasks launch and c/cpp -------------------- #
# configure_file (
#     "${CMAKE_SOURCE_DIR}/vscode_templates/c_cpp_properties.json.in"
#     "${PROJECT_SOURCE_DIR}/.vscode/c_cpp_properties.json"
# )
configure_file (
    "${CMAKE_SOURCE_DIR}/vscode_templates/launch.json.in"
    "${PROJECT_SOURCE_DIR}/.vscode/launch.json"
)
configure_file (
    "${CMAKE_SOURCE_DIR}/vscode_templates/tasks.json.in"
    "${PROJECT_SOURCE_DIR}/.vscode/tasks.json"
    @ONLY
)
# -------------------------------------------------------------------------- #

# get_target_property(STM32_FAMILY_2 ${TARGET_NAME} STM32_FAMILY)
# get_target_property(STM32_TYPE_2 ${TARGET_NAME} STM32_TYPE)
# get_target_property(STM32_SIZE_CODE_2 ${TARGET_NAME} STM32_SIZE_CODE)
# get_target_property(STM32_FLASH_SIZE_2 ${TARGET_NAME} STM32_FLASH_SIZE)
# get_target_property(STM32_RAM_SIZE_2 ${TARGET_NAME} STM32_RAM_SIZE)
# get_target_property(STM32_CCRAM_SIZE_2 ${TARGET_NAME} STM32_CCRAM_SIZE)
# get_target_property(STM32_COMP_DEF_2 ${TARGET_NAME} COMPILE_DEFINITIONS)
# get_target_property(STM32_COMP_FLAGS ${TARGET_NAME} COMPILE_OPTIONS)
# get_target_property(STM32_LINK_FLAGS ${TARGET_NAME} LINK_FLAGS)
get_target_property(STM32_INCLUDE_DIRECTORIES ${TARGET_NAME} INCLUDE_DIRECTORIES)

# message("STM32_CHIP is: " ${STM32_CHIP_2})
# message("STM32_FAMILY is: " ${STM32_FAMILY_2})
# message("STM32_TYPE is: " ${STM32_TYPE_2})
# message("STM32_SIZE_CODE is: " ${STM32_SIZE_CODE_2})
# message("STM32_FLASH_SIZE is: " ${STM32_FLASH_SIZE_2})
# message("STM32_RAM_SIZE is: " ${STM32_RAM_SIZE_2})
# message("STM32_CCRAM_SIZE is: " ${STM32_CCRAM_SIZE_2})
# message("COMPILE_DEFINTIONS is: " ${STM32_COMP_DEF_2})
# message("COMPILE_OPTIONS is: " ${STM32_COMP_FLAGS})
# message("LINK_FLAGS is: " ${STM32_LINK_FLAGS})
message("INCLUDE_DIRECTORIES is: " ${STM32_INCLUDE_DIRECTORIES})


# STM32_set_TARGET_PROPERTIES(${TARGET_NAME})
# STM32_ADD_HEX_BIN_TARGETS(${TARGET_NAME})
# STM32_PRINT_SIZE_OF_TARGETS(${TARGET_NAME})
