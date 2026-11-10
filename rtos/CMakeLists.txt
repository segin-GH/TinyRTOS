cmake_minimum_required(VERSION 3.16)
project(TinyRTOS LANGUAGES C ASM)

add_executable(kernel.elf
    src/startup.S
    src/main.c
    src/lk.c
    src/tsk.c
    src/sem.c
    src/hal/uart/uart.c
)

target_include_directories(kernel.elf PRIVATE src)

target_compile_options(kernel.elf PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -g
    $<$<COMPILE_LANGUAGE:C>:-O0>
    $<$<COMPILE_LANGUAGE:C>:-ffreestanding>
)

target_link_options(kernel.elf PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -nostdlib
    -T "${CMAKE_CURRENT_SOURCE_DIR}/linker.ld"
)
