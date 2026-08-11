if(MSVC)
    message(STATUS "Using MSVC")

    # close /showIncludes
    string(REPLACE "/showIncludes" "" CMAKE_DEPFILE_FLAGS_C "${CMAKE_DEPFILE_FLAGS_C}")
    string(REPLACE "/showIncludes" "" CMAKE_DEPFILE_FLAGS_CXX "${CMAKE_DEPFILE_FLAGS_CXX}")
endif()

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
    PRIVATE
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
            ${MODULE_FILES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)