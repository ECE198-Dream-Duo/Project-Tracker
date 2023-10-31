cmake_minimum_required(VERSION 3.10)
project(LineTrackingRobot)

# Specify the version of the CMake STM32 toolchain file
set(CMAKE_TOOLCHAIN_FILE /path/to/stm32_toolchain.cmake)

# Set the STM32 target device (e.g., STM32F4xx)
set(STM32_TARGET_DEVICE STM32F4xx)

# Set the STM32 HAL library directory (modify as needed)
set(STM32_HAL_LIBRARY_PATH /workspace/stm32_hal_library)

# Set the STM32CubeMX-generated source files directory (modify as needed)
set(STM32_CUBE_SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Set the STM32CubeMX-generated include files directory (modify as needed)
set(STM32_CUBE_INC_DIR ${CMAKE_SOURCE_DIR}/inc)

# Add your source files
set(SOURCE_FILES
    src/main.cpp
    # Add other source files here
)

# Add STM32CubeMX-generated source and include directories
include_directories(${STM32_CUBE_INC_DIR})
include_directories(${STM32_CUBE_SRC_DIR})

# Add STM32 HAL library (modify as needed)
link_directories(${STM32_HAL_LIBRARY_PATH})

# Create the STM32 executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${STM32_CUBE_SRC_DIR}/stm32f4xx_hal.c)

# Link the STM32 HAL library (modify as needed)
target_link_libraries(${PROJECT_NAME} stm32f4xx_hal)

# Specify the linker script file for the STM32 device (modify as needed)
target_link_options(${PROJECT_NAME} PRIVATE -T/workspace/STM32F4xx_FLASH.ld)

# Set compiler and linker flags (modify as needed)
target_compile_options(${PROJECT_NAME} PRIVATE -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard)
target_link_options(${PROJECT_NAME} PRIVATE -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard)

# Specify the output format and file extension (modify as needed)
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".elf")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")

# Create binary (.bin) and hex (.hex) output files
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex
)

# Print size information for the binary
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} --format=berkeley $<TARGET_FILE:${PROJECT_NAME}>
)

# From ChatGpt