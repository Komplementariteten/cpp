# Minimal zulässige Version von CMake: 
cmake_minimum_required(VERSION 3.15)
# Inkludieren des Pico-SDK: 
include(pico_sdk_import.cmake)

# enable usb output
# pico_enable_stdio_usb(${OUTPUT_NAME} 1)

# pico_add_extra_outputs(${OUTPUT_NAME})
# Name und Version des Projekts: 
project(MeinPicoProjekt VERSION 1.0.0) 

# set(OUTPUT_NAME tufty2040_drawing)
add_executable(MeinPicoProjekt show_pics.cpp)

target_link_libraries(MeinPicoProjekt
        hardware_i2c
        pico_stdlib
        tufty2040
        hardware_spi
        pico_graphics
        st7789
        button
)

# Das Projekt mit einer Quelldatei verknüpfen, das das Hauptprogramm enthält:  
# add_executable(MeinPicoProjekt show_pics.c) 
# Angabe der benötigten Bibliothek(en): 
# target_link_libraries(MeinPicoProjekt hardware_i2c pico_stdlib) 
# Initialisieren des SDK: 
pico_sdk_init()
# Zugriff auf USB und UART ermöglichen (1 = enable, 0 = disable): 
pico_enable_stdio_usb(MeinPicoProjekt 1) 
pico_enable_stdio_uart(MeinPicoProjekt 1)
# Definition notwendiger Extra-Zieldateien. Hieraus generiert das Tooling
# die für die Übertragung auf den Pico benötigte UF2-Datei: 
pico_add_extra_outputs(MeinPicoProjekt)