cmake_minimum_required(VERSION 3.26)
project(Lab02)
set(CMAKE_C_STANDARD 11)

# Aggiunge automaticamente tutte le sottocartelle (esercizi) dentro lab02
file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
foreach(child ${children})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child})
        add_subdirectory(${child})
    endif()
endforeach()