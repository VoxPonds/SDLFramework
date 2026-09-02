set(TARGET_NAME Example2D)

file(GLOB_RECURSE MODULE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.ixx"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cppm"
)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME}
    PRIVATE
        ${SRC_FILES}
    PRIVATE
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
            ${MODULE_FILES}
)

target_include_directories(${TARGET_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${TARGET_NAME}
    PRIVATE ${PROJECT_NAME}
)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:Example2D>/assets"
)