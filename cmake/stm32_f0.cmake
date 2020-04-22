target_compile_options(${TARGET_NAME}
    PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-mthumb -fno-builtin -mcpu=cortex-m0 -Wall -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs -fno-unroll-loops -ffast-math -ftree-vectorize>
    $<$<COMPILE_LANGUAGE:CXX>:-mthumb -mthumb -fno-builtin -mcpu=cortex-m0 -Wall -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs -fno-unroll-loops -ffast-math -ftree-vectorize
    $<$<COMPILE_LANGUAGE:ASM>:-mthumb -mcpu=cortex-m0 -x assembler-with-cpp>
)

target_link_options(${TARGET_NAME}
    PRIVATE
    -Wl,--gc-sections -mthumb -mcpu=cortex-m0 -mabi=aapcs
)

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

set_target_properties(${TARGET_NAME} PROPERTIES
    STM32_ARM_CORE  "core_cm4"
)
