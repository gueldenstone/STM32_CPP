cmake_minimum_required(VERSION 3.13)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR})
# set(CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "Use Makefiles")
include(GNUInstallDirs)
project("CMSIS" 
    VERSION 1.0
    LANGUAGES C ASM )

if(NOT TARGET_NAME)
    message(STATUS "No Target defined in Parent Project, switching to default STM32F303CC")
    set(STM32_CHIP "STMF303CC")
    set(STM32_FAMILY "F3")
    set(STM32_TYPE "303xx")
    set(STM32_SIZE_CODE "C")
    set(STM32_ARM_CORE "core_cm4")
    set(USE_CMSIS TRUE)
    # set(UPDATE_CMSIS TRUE)
    set(USE_HAL_DRIVER TRUE)
    # set(UPDATE_HAL TRUE)

else()
    get_target_property(STM32_CHIP ${TARGET_NAME} STM32_CHIP)
    get_target_property(STM32_FAMILY ${TARGET_NAME} STM32_FAMILY)
    get_target_property(STM32_TYPE ${TARGET_NAME} STM32_TYPE)
    get_target_property(STM32_SIZE_CODE ${TARGET_NAME} STM32_SIZE_CODE)
    get_target_property(STM32_ARM_CORE ${TARGET_NAME} STM32_ARM_CORE)
    get_target_property(STM32_ARM_MPU ${TARGET_NAME} STM32_ARM_MPU)
    get_target_property(STM32_COMPILE_DEFINITIONS ${TARGET_NAME} COMPILE_DEFINITIONS)
    get_target_property(STM32_STARTUP ${TARGET_NAME} STM32_STARTUP)
endif()

# process name properties
string(REGEX REPLACE "^[sS][tT][mM]32[fFhHlL]([0-9][0-9][0-9]).+$" "\\1" TYPE ${STM32_CHIP})

string(TOLOWER ${STM32_FAMILY} STM32_FAMILY_LOW)
string(TOLOWER ${STM32_TYPE} STM32_TYPE_LOW)
string(TOLOWER ${STM32_SIZE_CODE} STM32_SIZE_CODE_LOW)

include(FetchContent)
# get HAL Drivers from GitHub
if(USE_HAL_DRIVER OR USE_LL_DRIVER)
    FetchContent_Declare(hal
        GIT_REPOSITORY https://github.com/STMicroelectronics/stm32${STM32_FAMILY_LOW}xx_hal_driver.git
        GIT_TAG master
        GIT_PROGRESS FALSE
        BUILD_COMMAND ""
        CONFIGURE_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/STM32${STM32_FAMILY}xx_HAL_Driver")
    
    if(NOT UPDATE_HAL)
        set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
    else()
        set(FETCHCONTENT_UPDATES_DISCONNECTED FALSE)
    endif()
    message(STATUS "Downloading HAL Drivers")
    FetchContent_GetProperties(hal)
    FetchContent_Populate(hal)
    message(STATUS "The HAL Drivers have been written to: " ${hal_SOURCE_DIR})
endif()
# get CMSIS Drivers from GitHub
if(USE_CMSIS)
    FetchContent_Declare(cmsis_core
        GIT_REPOSITORY https://github.com/STMicroelectronics/cmsis_core.git
        GIT_TAG master
        GIT_PROGRESS FALSE
        BUILD_COMMAND ""
        CONFIGURE_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/CMSIS")
    
    FetchContent_Declare(cmsis_device
        GIT_REPOSITORY https://github.com/STMicroelectronics/cmsis_device_${STM32_FAMILY_LOW}.git
        GIT_TAG master
        GIT_PROGRESS FALSE
        BUILD_COMMAND ""
        CONFIGURE_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
        SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/CMSIS/Device/ST/STM32${STM32_FAMILY}xx")
    
    if(NOT UPDATE_CMSIS)
        set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
    else()
        set(FETCHCONTENT_UPDATES_DISCONNECTED FALSE)
    endif()
    message(STATUS "Downloading CMSIS Core Drivers")
    FetchContent_GetProperties(cmsis_core)
    FetchContent_Populate(cmsis_core)
    message(STATUS "The CMSIS Core Drivers have been written to: " ${cmsis_core_SOURCE_DIR})
    message(STATUS "Downloading CMSIS Device Drivers")
    FetchContent_GetProperties(cmsis_device)
    FetchContent_Populate(cmsis_device)
    message(STATUS "The CMSIS Device Drivers have been written to: " ${cmsis_device_SOURCE_DIR})
endif()

# Set Common Headers
set(CMSIS_COMMON_HEADERS
    cmsis_gcc.h
    cmsis_version.h
    cmsis_compiler.h
    core_${STM32_ARM_CORE}.h
    mpu_${STM32_ARM_MPU}.h
)

set(CMSIS_DEVICE_HEADERS
    system_stm32${STM32_FAMILY_LOW}xx.h
    stm32${STM32_FAMILY_LOW}xx.h
    stm32f${TYPE}x${STM32_SIZE_CODE_LOW}.h
)

list(TRANSFORM CMSIS_COMMON_HEADERS PREPEND "${cmsis_core_SOURCE_DIR}/Core/Include/" OUTPUT_VARIABLE CMSIS_COMMON_HEADERS_P)
list(TRANSFORM CMSIS_DEVICE_HEADERS PREPEND "${cmsis_device_SOURCE_DIR}/Include/" OUTPUT_VARIABLE CMSIS_DEVICE_HEADERS_P)
if(CMSIS_OVERRIDE_COPY)
file(COPY 
        # Sources
        ${cmsis_device_SOURCE_DIR}/Source/Templates/system_stm32${STM32_FAMILY_LOW}xx.c
        ${cmsis_device_SOURCE_DIR}/Source/Templates/gcc/startup_${STM32_STARTUP}.s
    DESTINATION
        ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/src
)

file(COPY
        # Header
        ${CMSIS_COMMON_HEADERS_P}
        ${CMSIS_DEVICE_HEADERS_P}
    DESTINATION
        ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/include 
)
set(CMSIS_OVERRIDE_COPY false)
endif()
configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/CMakeLists.txt.in ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/CMakeLists.txt @ONLY)