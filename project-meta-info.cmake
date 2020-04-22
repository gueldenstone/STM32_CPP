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
    # Directory of the Drivers
    set(STM32_CUBE_DIR "/Users/lukas/Library/Mobile Documents/com~apple~CloudDocs/05_DEV/VSARM/Drivers")

    # set(USE_HAL_DRIVER TRUE)
    # set(USE_LL_DRIVER TRUE)
    # set(UPDATE_HAL TRUE)

    set(USE_CMSIS TRUE)
    # set(UPDATE_CMSIS TRUE)

# some STM32 specific stuff with CMake
    set(HAVE_FLAG_SEARCH_PATHS_FIRST 0) # otherwise CMake will automatically set linker flags
    # set(CMAKE_C_LINK_FLAGS "")
    # set(CMAKE_CXX_LINK_FLAGS "")