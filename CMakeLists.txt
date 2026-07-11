cmake_minimum_required(VERSION 3.20)

project(
    SW_USIM_Emulator
    VERSION 0.1
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)

include_directories(
    include
    include/common
    include/boot
)

add_executable(
    sw_usim

    main.c

    src/common/logger.c

    src/boot/bootloader.c
)