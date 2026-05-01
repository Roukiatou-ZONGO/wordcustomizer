cmake_minimum_required(VERSION 3.20)
project(WordCustomizer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Modules du projet
add_subdirectory(src/engine)
add_subdirectory(src/styles)
add_subdirectory(src/templates)
add_subdirectory(src/macros)
add_subdirectory(src/ui)

# Exécutable principal
add_executable(wordcustomizer
    src/main.cpp
)

target_link_libraries(wordcustomizer
    engine
    styles
    templates
    macros
    ui
)