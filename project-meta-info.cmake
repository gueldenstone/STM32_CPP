# project-meta-info.in

# The Project Name
    get_filename_component(project_name ${CMAKE_CURRENT_LIST_DIR} NAME)
    string(REPLACE " " "_" project_name ${project_name})

# The version number of this project.
    set(project_version 0.0.1 ) 

# The description of this project.
    set(project_description "Description of root-project" ) 

# The homepage of this project.
    set(project_homepage "https://www.example.com" )

# The used STM32 Chip in the Format STM32Fxxxxx (example: STM32F303CC)
    set(CHIP_NAME "STM32F303RE")

# The Build Type
    set(CMAKE_BUILD_TYPE DEBUG)

# The Drivers to use (coment/uncomment)
    # set(USE_HAL_DRIVER TRUE)
    # set(USE_LL_DRIVER TRUE)
    # set(UPDATE_HAL TRUE)

    set(USE_CMSIS TRUE)
    # set(UPDATE_CMSIS TRUE)

# some STM32 specific stuff with CMake
    set(HAVE_FLAG_SEARCH_PATHS_FIRST 0) # otherwise CMake will automatically set linker flags
    # set(CMAKE_C_LINK_FLAGS "")
    # set(CMAKE_CXX_LINK_FLAGS "")

# Debug Config
    set(DEBUG_DIR "${CMAKE_CURRENT_LIST_DIR}/Debug")
    set(DEBUG_SERVER "openocd")
    set(DEBUG_ADAPTER "stlink")
    set(STM32_SVD_FILE "STM32F303.svd")