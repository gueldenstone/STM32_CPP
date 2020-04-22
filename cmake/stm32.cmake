
# Define Custom Properties of the target
define_property(TARGET PROPERTY STM32_CHIP INHERITED BRIEF_DOCS "Name of the Chip" FULL_DOCS "Name of the Chip")
define_property(TARGET PROPERTY STM32_FAMILY INHERITED BRIEF_DOCS "Name of the Chip Family" FULL_DOCS "Name of the Chip")
define_property(TARGET PROPERTY STM32_TYPE INHERITED BRIEF_DOCS "Name of the Chip Type" FULL_DOCS "Name of the Chip")
define_property(TARGET PROPERTY STM32_SIZE_CODE INHERITED BRIEF_DOCS "Name of the Chip" FULL_DOCS "Name of the Chip")
define_property(TARGET PROPERTY STM32_FLASH_SIZE INHERITED BRIEF_DOCS "Name of the Chip" FULL_DOCS "Name of the Chip")
define_property(TARGET PROPERTY STM32_RAM_SIZE INHERITED BRIEF_DOCS "Name of the Chip" FULL_DOCS "Name of the Chip")
define_property(TARGET PROPERTY STM32_CCRAM_SIZE INHERITED BRIEF_DOCS "Name of the Chip" FULL_DOCS "Name of the Chip")
define_property(TARGET PROPERTY STM32_FLASH_ORIGIN INHERITED BRIEF_DOCS "Name of the Chip" FULL_DOCS "Name of the Chip")
define_property(TARGET PROPERTY STM32_RAM_ORIGIN INHERITED BRIEF_DOCS "Name of the Chip" FULL_DOCS "Name of the Chip")
define_property(TARGET PROPERTY STM32_MIN_STACK_SIZE INHERITED BRIEF_DOCS "Name of the Chip" FULL_DOCS "Name of the Chip")
define_property(TARGET PROPERTY STM32_MIN_HEAP_SIZE INHERITED BRIEF_DOCS "Name of the Chip" FULL_DOCS "Name of the Chip")
define_property(TARGET PROPERTY STM32_CCRAM_ORIGIN INHERITED BRIEF_DOCS "Name of the Chip" FULL_DOCS "Name of the Chip")
define_property(TARGET PROPERTY STM32_ARM_CORE INHERITED BRIEF_DOCS "Name of the Chip" FULL_DOCS "Name of the Chip")

# set System-Parameters
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)


function(stm32_set_target_common_properties TARGET CHIP)
    set_target_properties(${TARGET} PROPERTIES
         STM32_CHIP ${CHIP_NAME}
         OUTPUT_NAME "${CMAKE_PROJECT_NAME}.elf"
    )
    # set common flags
    target_compile_options(${TARGET}
        PUBLIC
        $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:Debug>>:-Og -g>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Debug>>:-Og -g>
        $<$<AND:$<COMPILE_LANGUAGE:ASM>,$<CONFIG:Debug>>:-g>
        $<$<AND:$<COMPILE_LANGUAGE:C>,$<CONFIG:Release>>:-Os -flto>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Release>>:-Os -flto>
        $<$<AND:$<COMPILE_LANGUAGE:ASM>,$<CONFIG:Release>>: >
    )
    target_link_options(${TARGET}
        PUBLIC
        $<$<CONFIG:Debug>:-specs=nano.specs -Xlinker -Map=output.map>
        $<$<CONFIG:Release>:-specs=nano.specs -Xlinker -Map=output.map -s -flto>
    )
    
    if(USE_HAL_DRIVER)
    target_compile_definitions(${TARGET} PUBLIC USE_HAL_DRIVER)
    endif()

    if(USE_LL_DRIVER)
    target_compile_definitions(${TARGET} PUBLIC USE_LL_DRIVER)
    endif()
    # decode the chip-name
    string(REGEX REPLACE "^[sS][tT][mM]32([fFhHlL][0-9]).+$" "\\1" FAMILY ${CHIP})
    string(REGEX REPLACE "^[sS][tT][mM]32[fFhHlL][0-9]([0-9][0-9]).+$" "\\1" SUB_FAMILY ${CHIP})
    string(REGEX REPLACE "^[sS][tT][mM]32[fFhHlL]([0-9][0-9][0-9]).+$" "\\1xx" TYPE ${CHIP})
    string(REGEX REPLACE "^[sS][tT][mM]32[fFhHlL][0-9][0-9][0-9]([A-Z]).+$" "\\1" PIN_CODE ${CHIP})
    string(REGEX REPLACE "^[sS][tT][mM]32[fFhHlL][0-9][0-9][0-9][A-Z]([468BZCDEFGHI])$" "\\1" SIZE_CODE ${CHIP})
    string(REGEX REPLACE "^([sS][tT][mM]32[fFhHlL][0-9][0-9][0-9])[A-Z]([468BZCDEFGHI])$" "\\1x\\2" COMP_DEF ${CHIP})
    string(TOLOWER ${FAMILY} FAMILY_LOW)
    string(TOLOWER ${SUB_FAMILY} SUB_FAMILY_LOW)
    string(TOLOWER ${TYPE} TYPE_LOW)
    string(TOLOWER ${PIN_CODE} PIN_CODE_LOW)
    string(TOLOWER ${SIZE_CODE} SIZE_CODE_LOW)

    # write the values to the target
    set_target_properties(${TARGET} PROPERTIES
        STM32_FAMILY ${FAMILY}
        STM32_TYPE ${TYPE}
        STM32_SIZE_CODE ${SIZE_CODE}
    )

    # -------------------- select Family and set parameters -------------------- #
    if(FAMILY STREQUAL "F0")
        set(STM32_CORE "M0")
        set(ARM_CORE "core_cm0")
    elseif(FAMILY STREQUAL "F1")
        set(STM32_CORE "M3")
        set(ARM_CORE "core_cm3")

    elseif(FAMILY STREQUAL "F2")
        set(STM32_CORE "M3")
        set(ARM_CORE "core_cm3")

    elseif(FAMILY STREQUAL "F3")
        set(STM32_CORE "M4")
        set(ARM_CORE "core_cm4")

    elseif(FAMILY STREQUAL "F4")
        set(STM32_CORE "M4")
        set(ARM_CORE "core_cm4")

    elseif(FAMILY STREQUAL "F7")
        set(STM32_CORE "M7")
        set(ARM_CORE "core_cm7")

    elseif(FAMILY STREQUAL "G0")
        set(STM32_CORE "M0+")
        set(ARM_CORE "core_cm0plus")

    elseif(FAMILY STREQUAL "G4")
        set(STM32_CORE "M4")
        set(ARM_CORE "core_cm4")

    elseif(FAMILY STREQUAL "H7")
        set(STM32_CORE "M7")
        set(ARM_CORE "core_cm7")

    elseif(FAMILY STREQUAL "L0")
        set(STM32_CORE "M0+")
        set(ARM_CORE "core_cm0plus")

    elseif(FAMILY STREQUAL "L1")
        set(STM32_CORE "M3")
        set(ARM_CORE "core_cm3")

    elseif(FAMILY STREQUAL "L4")
        set(STM32_CORE "M4")
        set(ARM_CORE "core_cm4")

    elseif(FAMILY STREQUAL "L5")
        set(STM32_CORE "M33")
        set(ARM_CORE "core_cm33")
    endif()
    if(NOT ARM_CORE)
        message(FATAL_ERROR "Could not determine the ARM Core for ${CHIP}")
    else()
        message(STATUS "The ARM Core is ${ARM_CORE}")
        # write the values to the target
        set_target_properties(${TARGET} PROPERTIES
            STM32_ARM_CORE ${ARM_CORE}
        )
    endif()

    # set Flash Size
    if(SIZE_CODE STREQUAL "4")
        set(FLASH_SIZE "16K")
    elseif(SIZE_CODE STREQUAL "6")
        set(FLASH_SIZE "32K")
    elseif(SIZE_CODE STREQUAL "8")
        set(FLASH_SIZE "64K")
    elseif(SIZE_CODE STREQUAL "B")
        set(FLASH_SIZE "128K")
    elseif(SIZE_CODE STREQUAL "C")
        set(FLASH_SIZE "256K")
    elseif(SIZE_CODE STREQUAL "D")
        set(FLASH_SIZE "384K")
    elseif(SIZE_CODE STREQUAL "E")
        set(FLASH_SIZE "512K")
    elseif(SIZE_CODE STREQUAL "F")
        set(FLASH_SIZE "768K")
    elseif(SIZE_CODE STREQUAL "G")
        set(FLASH_SIZE "1000K")
    endif()
    if(NOT FLASH_SIZE)
        message(FATAL_ERROR "Could not determine the Flash Size for ${CHIP}")
    else()
        message(STATUS "The Flash Size ist ${FLASH_SIZE}")
         # write the values to the target
        set_target_properties(${TARGET} PROPERTIES
            STM32_FLASH_SIZE ${FLASH_SIZE}
        )
    endif()

    # determine more target properties
    include(stm32_${FAMILY_LOW})
    stm32_target_set_family_properties(${TARGET})

    # set the linker stuff
    include(stm32_linker)
    stm32_set_linker_script(${TARGET})
endfunction()





