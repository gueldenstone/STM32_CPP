# TODO: Add support for external RAM
get_target_property(STM32_FLASH_ORIGIN ${TARGET_NAME} STM32_FLASH_ORIGIN)
get_target_property(STM32_FLASH_SIZE ${TARGET_NAME} STM32_FLASH_SIZE)
get_target_property(STM32_RAM_ORIGIN ${TARGET_NAME} STM32_RAM_ORIGIN)
get_target_property(STM32_RAM_SIZE ${TARGET_NAME} STM32_RAM_SIZE)
get_target_property(STM32_MIN_STACK_SIZE ${TARGET_NAME} STM32_MIN_STACK_SIZE)
get_target_property(STM32_MIN_HEAP_SIZE ${TARGET_NAME} STM32_MIN_HEAP_SIZE)
get_target_property(STM32_CCRAM_ORIGIN ${TARGET_NAME} STM32_CCRAM_ORIGIN)
get_target_property(STM32_CCRAM_SIZE ${TARGET_NAME} STM32_CCRAM_SIZE)

IF((NOT STM32_CCRAM_SIZE) OR (STM32_CCRAM_SIZE STREQUAL "0K"))
  SET(STM32_CCRAM_DEF "")
  SET(STM32_CCRAM_SECTION "")
ELSE()
  SET(STM32_CCRAM_DEF "  CCMRAM (rw) : ORIGIN = ${STM32_CCRAM_ORIGIN}, LENGTH = ${STM32_CCRAM_SIZE}\n")
  SET(STM32_CCRAM_SECTION 
  "  _siccmram = LOADADDR(.ccmram)\;\n"
  "  .ccmram :\n"
  "  {"
  "    . = ALIGN(4)\;\n"
  "    _sccmram = .\;\n"
  "    *(.ccmram)\n"
  "    *(.ccmram*)\n"
  "    . = ALIGN(4)\;\n"
  "    _eccmram = .\;\n"
  "  } >CCMRAM AT> FLASH\n"
  )
ENDIF()

SET(STM32_LINKER_SCRIPT_TEXT
  "ENTRY(Reset_Handler)\n"
  "_estack = ${STM32_RAM_ORIGIN} + ${STM32_RAM_SIZE} - 1\;\n"
  "_Min_Heap_Size = ${STM32_MIN_HEAP_SIZE}\;\n"
  "_Min_Stack_Size = ${STM32_MIN_STACK_SIZE}\;\n"
  "MEMORY\n"
  "{\n"
  "  FLASH (rx)      : ORIGIN = ${STM32_FLASH_ORIGIN}, LENGTH = ${STM32_FLASH_SIZE}\n"
  "  RAM (xrw)      : ORIGIN = ${STM32_RAM_ORIGIN}, LENGTH = ${STM32_RAM_SIZE}\n"
  "${STM32_CCRAM_DEF}"
  "}\n"
  "SECTIONS\n"
  "{\n"
  "  .isr_vector :\n"
  "  {\n"
  "    . = ALIGN(4)\;\n"
  "    KEEP(*(.isr_vector))\n"
  "    . = ALIGN(4)\;\n"
  "  } >FLASH\n"
  "  .text :\n"
  "  {\n"
  "    . = ALIGN(4)\;\n"
  "    *(.text)\n"
  "    *(.text*)\n"
  "    *(.glue_7)\n"
  "    *(.glue_7t)\n"
  "    *(.eh_frame)\n"
  "    KEEP (*(.init))\n"
  "    KEEP (*(.fini))\n"
  "    . = ALIGN(4)\;\n"
  "    _etext = .\;\n"
  "  } >FLASH\n"
  "  .rodata :\n"
  "  {\n"
  "    . = ALIGN(4)\;\n"
  "    *(.rodata)\n"
  "    *(.rodata*)\n"
  "    . = ALIGN(4)\;\n"
  "  } >FLASH\n"
  "  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH\n"
  "  .ARM : {\n"
  "    __exidx_start = .\;\n"
  "    *(.ARM.exidx*)\n"
  "    __exidx_end = .\;\n"
  "  } >FLASH\n"
  "  .preinit_array     :\n"
  "  {\n"
  "    PROVIDE_HIDDEN (__preinit_array_start = .)\;\n"
  "    KEEP (*(.preinit_array*))\n"
  "    PROVIDE_HIDDEN (__preinit_array_end = .)\;\n"
  "  } >FLASH\n"
  "  .init_array :\n"
  "  {\n"
  "    PROVIDE_HIDDEN (__init_array_start = .)\;\n"
  "    KEEP (*(SORT(.init_array.*)))\n"
  "    KEEP (*(.init_array*))\n"
  "    PROVIDE_HIDDEN (__init_array_end = .)\;\n"
  "  } >FLASH\n"
  "  .fini_array :\n"
  "  {\n"
  "    PROVIDE_HIDDEN (__fini_array_start = .)\;\n"
  "    KEEP (*(SORT(.fini_array.*)))\n"
  "    KEEP (*(.fini_array*))\n"
  "    PROVIDE_HIDDEN (__fini_array_end = .)\;\n"
  "  } >FLASH\n"
  "  _sidata = LOADADDR(.data)\;\n"
  "  .data : \n"
  "  {\n"
  "    . = ALIGN(4)\;\n"
  "    _sdata = .\;\n"
  "    *(.data)\n"
  "    *(.data*)\n"
  "    . = ALIGN(4)\;\n"
  "    _edata = .\;\n"
  "  } >RAM AT> FLASH\n"
  "${STM32_CCRAM_SECTION}"
  "  . = ALIGN(4)\;\n"
  "  .bss :\n"
  "  {\n"
  "    _sbss = .\;\n"
  "    __bss_start__ = _sbss\;\n"
  "    *(.bss)\n"
  "    *(.bss*)\n"
  "    *(COMMON)\n"
  "    . = ALIGN(4)\;\n"
  "    _ebss = .\;\n"
  "    __bss_end__ = _ebss\;\n"
  "  } >RAM\n"
  "  ._user_heap_stack :\n"
  "  {\n"
  "    . = ALIGN(4)\;\n"
  "    PROVIDE ( end = . )\;\n"
  "    PROVIDE ( _end = . )\;\n"
  "    . = . + _Min_Heap_Size\;\n"
  "    . = . + _Min_Stack_Size\;\n"
  "    . = ALIGN(4)\;\n"
  "  } >RAM\n"
  "  /DISCARD/ :\n"
  "  {\n"
  "    libc.a ( * )\n"
  "    libm.a ( * )\n"
  "    libgcc.a ( * )\n"
  "  }\n"
  "  .ARM.attributes 0 : { *(.ARM.attributes) }\n"
  "}\n"
)


function(stm32_set_linker_script TARGET)
  # set the linker-script
  if(NOT STM32_LINKER_SCRIPT)
  message(STATUS "No linker script specified, generating default")
      file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}_flash.ld ${STM32_LINKER_SCRIPT_TEXT})
      target_link_options(${TARGET} PRIVATE -T${CMAKE_CURRENT_BINARY_DIR}/${TARGET}_flash.ld)
  else()
      configure_file(${STM32_LINKER_SCRIPT} ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}_flash.ld)
  endif()
endfunction()