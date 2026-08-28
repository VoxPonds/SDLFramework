add_library(${PROJECT_NAME} STATIC)

file(GLOB_RECURSE MODULE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.ixx"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cppm"
)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${SRC_FILES}
    PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
            ${MODULE_FILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_features(${PROJECT_NAME}
    PUBLIC
        cxx_std_23

)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    CXX_MODULE_STD ON
    CXX_STANDARD_REQUIRED ON
)

# Link to the actual SDL3 library.
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        SDL3::SDL3
        SDL3_image::SDL3_image
        glm::glm
        nlohmann_json::nlohmann_json
        spdlog::spdlog
)