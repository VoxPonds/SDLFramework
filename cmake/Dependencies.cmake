# ---- SDL3 Configuration ----
# Choose shared or static library before add_subdirectory
set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)

# Set options before add_subdirectory
# This prevents the compilation of SDL3's dozens of test programs, greatly speeding up the build process
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL_TESTS OFF CACHE BOOL "" FORCE)

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendored/SDL SYSTEM EXCLUDE_FROM_ALL)


#SDL_image (used for loading various image formats)
set(SDLIMAGE_VENDORED ON CACHE BOOL "" FORCE)
set(SDLIMAGE_AVIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_BMP OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_JPEG OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_WEBP OFF CACHE BOOL "" FORCE)

#This assumes the SDL_image source is available in vendored/SDL_image
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendored/SDL_image SYSTEM EXCLUDE_FROM_ALL)


set(GLM_BUILD_LIBRARY OFF CACHE BOOL "" FORCE)
set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendored/glm SYSTEM EXCLUDE_FROM_ALL)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendored/nlohmann_json SYSTEM EXCLUDE_FROM_ALL)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendored/spdlog SYSTEM EXCLUDE_FROM_ALL)


set(SDLSHADERCROSS_VENDORED ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendored/SDL_shadercross SYSTEM EXCLUDE_FROM_ALL)
if(TARGET SDL3_shadercross)
    add_custom_command(
            TARGET SDL3_shadercross
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/vendored/SDL_shadercross/external/DirectXShaderCompiler/bin/dxcompiler.dll"
            "$<TARGET_FILE_DIR:shadercross>"
    )
endif()