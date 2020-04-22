function(stm32_target_set_family_properties TARGET)

    target_compile_options(${TARGET}
        PUBLIC
        $<$<COMPILE_LANGUAGE:C>:-mthumb -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Wall -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs -fno-unroll-loops -ffast-math -ftree-vectorize>
        $<$<COMPILE_LANGUAGE:CXX>:-mthumb -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Wall -std=c++11 -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs -fno-unroll-loops -ffast-math -ftree-vectorize>
        $<$<COMPILE_LANGUAGE:ASM>:-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -g -Wa,--no-warn -x assembler-with-cpp>
    )

    target_link_options(${TARGET}
        PUBLIC
        -Wl,--gc-sections -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard
    )

    get_target_property(TYPE ${TARGET} STM32_TYPE)
    get_target_property(SIZE_CODE ${TARGET} STM32_SIZE_CODE)
    if(NOT TYPE)
        message(FATAL_ERROR "No Type specified!")
    endif()
    if(NOT SIZE_CODE)
        message(FATAL_ERROR "No Size Code given!")
    else()
        # RAM & CCRAM
        if(${TYPE} STREQUAL "301xx")
        set(RAM_SIZE_IN_K "16")
        # 302xx Series
        elseif(${TYPE} STREQUAL "302xx")
            if(${SIZE_CODE} STREQUAL "6")
                set(RAM_SIZE_IN_K "16")
            elseif(${SIZE_CODE} STREQUAL "8")
                set(RAM_SIZE_IN_K "16")
            elseif(${SIZE_CODE} STREQUAL "B")
                set(RAM_SIZE_IN_K "32")
            elseif(${SIZE_CODE} STREQUAL "C")
                set(RAM_SIZE_IN_K "40")
            elseif(${SIZE_CODE} STREQUAL "D")
                set(RAM_SIZE_IN_K "64")
            elseif(${SIZE_CODE} STREQUAL "E")
                set(RAM_SIZE_IN_K "64")
            endif()
        # 303xx Series
        elseif(${TYPE} STREQUAL "303xx")
            if(${SIZE_CODE} STREQUAL "6")
                set(RAM_SIZE_IN_K "16")
                set(CCRAM_SIZE_IN_K "4")
            elseif(${SIZE_CODE} STREQUAL "8")
                set(RAM_SIZE_IN_K "16")
                set(CCRAM_SIZE_IN_K "4")
            elseif(${SIZE_CODE} STREQUAL "B")
                set(RAM_SIZE_IN_K "40")
                set(CCRAM_SIZE_IN_K "8")
            elseif(${SIZE_CODE} STREQUAL "C")
                set(RAM_SIZE_IN_K "48")
                set(CCRAM_SIZE_IN_K "8")
            elseif(${SIZE_CODE} STREQUAL "D")
                set(RAM_SIZE_IN_K "80")
                set(CCRAM_SIZE_IN_K "16")
            elseif(${SIZE_CODE} STREQUAL "E")
                set(RAM_SIZE_IN_K "80")
                set(CCRAM_SIZE_IN_K "16")
            endif()
        # 334xx Series
        elseif(${TYPE} STREQUAL "334xx")
        set(RAM_SIZE_IN_K "16")
        set(CCRAM_SIZE_IN_K "4")
        # 373xx Series
        elseif(${TYPE} STREQUAL "373xx")
            if(${SIZE_CODE} STREQUAL "8")
                set(RAM_SIZE_IN_K "16")
            elseif(${SIZE_CODE} STREQUAL "B")
                set(RAM_SIZE_IN_K "24")
            elseif(${SIZE_CODE} STREQUAL "C")
                set(RAM_SIZE_IN_K "32")
            endif()
        # 3x8 Series
        # 318 Series
        elseif(${TYPE} STREQUAL "318xx")
        set(RAM_SIZE_IN_K "16")
        # 328 Series
        elseif(${TYPE} STREQUAL "328xx")
        set(RAM_SIZE_IN_K "16")
        set(CCRAM_SIZE_IN_K "4")
        # 358 Series
        elseif(${TYPE} STREQUAL "358xx")
        set(RAM_SIZE_IN_K "48")
        set(CCRAM_SIZE_IN_K "8")
        # 378 Series
        elseif(${TYPE} STREQUAL "378xx")
        set(RAM_SIZE_IN_K "32")
        # 398 Series
        elseif(${TYPE} STREQUAL "398xx")
        set(RAM_SIZE_IN_K "80")
        set(CCRAM_SIZE_IN_K "16")
        endif()


        # RAM size = total RAM - CCRAM
        math(EXPR RAM_SIZE_IN_K "${RAM_SIZE_IN_K}-${CCRAM_SIZE_IN_K}")
        
        # Append the 'K' literal to the numbers
        set(RAM_SIZE "${RAM_SIZE_IN_K}K")
        set(CCRAM_SIZE "${CCRAM_SIZE_IN_K}K")
        if(NOT RAM_SIZE)
            message(FATAL_ERROR "Could not determine the RAM Size ${CHIP}")
        else()
            message(STATUS "The RAM Size is ${RAM_SIZE}")
            # write the values to the target
            set_target_properties(${TARGET} PROPERTIES
            STM32_RAM_SIZE ${RAM_SIZE}
            )
        endif()
        if(NOT CCRAM_SIZE)
            message(FATAL_ERROR "Could not determine the CCRAM Size ${CHIP}")
        else()
            message(STATUS "The CCRAM Size is ${CCRAM_SIZE}")
            # write the values to the target
            set_target_properties(${TARGET} PROPERTIES
            STM32_CCRAM_SIZE ${CCRAM_SIZE}
            )
        endif()
    endif()


    # set origins, stack- and heap-sizes
    if(NOT STM32_FLASH_ORIGIN)
    set(STM32_FLASH_ORIGIN "0x08000000")
        # set the properties to the target
        set_target_properties(${TARGET} PROPERTIES
        STM32_FLASH_ORIGIN ${STM32_FLASH_ORIGIN}
    )
    endif()

    if(NOT STM32_RAM_ORIGIN)
    set(STM32_RAM_ORIGIN "0x20000000")
        # set the properties to the target
        set_target_properties(${TARGET} PROPERTIES
        STM32_RAM_ORIGIN ${STM32_RAM_ORIGIN}
    )
    endif()
    

    if(NOT STM32_MIN_STACK_SIZE)
    set(STM32_MIN_STACK_SIZE "0x200")
        # set the properties to the target
        set_target_properties(${TARGET} PROPERTIES
        STM32_MIN_STACK_SIZE ${STM32_MIN_STACK_SIZE}
    )
    endif()

    if(NOT STM32_MIN_HEAP_SIZE)
    set(STM32_MIN_HEAP_SIZE "0")
        # set the properties to the target
        set_target_properties(${TARGET} PROPERTIES
        STM32_MIN_HEAP_SIZE ${STM32_MIN_HEAP_SIZE}
    )
    endif()

    if(NOT STM32_CCRAM_ORIGIN)
    set(STM32_CCRAM_ORIGIN "0x10000000")
        # set the properties to the target
        set_target_properties(${TARGET} PROPERTIES
        STM32_CCRAM_ORIGIN ${STM32_CCRAM_ORIGIN}
    )
    endif()


    # set the properties to the target
    set_target_properties(${TARGET} PROPERTIES
        STM32_RAM_SIZE ${RAM_SIZE}
        STM32_CCRAM_SIZE ${CCRAM_SIZE}
        COMPILE_DEFINITIONS ${COMP_DEF}
    )

endfunction()