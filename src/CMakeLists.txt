add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE TP2.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE vendor)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/SDL/include)