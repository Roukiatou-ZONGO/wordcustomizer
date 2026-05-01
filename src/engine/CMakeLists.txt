find_package(libzip CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)

add_library(engine DocxEngine.cpp)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(engine
    PUBLIC libzip::zip
    PUBLIC pugixml::pugixml
)