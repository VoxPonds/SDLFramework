message(STATUS "The CMAKE_VERSION is ${CMAKE_VERSION}.")
cmake_minimum_required(VERSION 4.2.0)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD f35a9ac6-8463-4d38-8eec-5d6008153e7d)
set(CMAKE_CXX_STANDARD 23)

# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# ---- output ----
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# ---- SDL3 Configuration ----
# Key Point 1: Choose shared or static library before add_subdirectory
set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)

# Key Point 2: Set options before add_subdirectory
# This prevents the compilation of SDL3's dozens of test programs, greatly speeding up the build process
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL_TESTS OFF CACHE BOOL "" FORCE)

project (SDLFramework LANGUAGES C CXX VERSION 0.0.1)

# Create your game executable target as usual
add_executable(${PROJECT_NAME} 
    src/main.cpp
)

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

#SDL_image (used for loading various image formats)
set(SDLIMAGE_VENDORED ON)
set(SDLIMAGE_AVIF OFF)	# disable formats we don't use to make the build faster and smaller.
set(SDLIMAGE_BMP OFF)
set(SDLIMAGE_JPEG OFF)
set(SDLIMAGE_WEBP OFF)

#This assumes the SDL_image source is available in vendored/SDL_image
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)


# SDL_ttf
# set(SDLTTF_VENDORED ON CACHE BOOL "" FORCE)
# This assumes the SDL_ttf source is available in vendored/SDL_ttf
# add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)


# SDL_mixer (used for playing audio)
# set(SDLMIXER_MIDI_NATIVE OFF)     # disable formats we don't use to make the build faster and smaller. Also some of these don't work on all platforms so you'll need to do some experimentation.
# set(SDLMIXER_GME OFF)
# set(SDLMIXER_WAVPACK OFF)     
# set(SDLMIXER_MOD OFF)
# set(SDLMIXER_MOD_XMP OFF)
# set(SDLMIXER_OPUS OFF)
# set(SDLMIXER_MP3_MPG123 OFF)
# set(SDLMIXER_VORBIS_VORBISFILE OFF)
# set(SDLMIXER_FLAC_LIBFLAC OFF)
# set(SDLMIXER_VENDORED ON)   # tell SDL_mixer to build its own dependencies
# add_subdirectory(vendored/SDL_mixer EXCLUDE_FROM_ALL)

set(GLM_BUILD_LIBRARY OFF CACHE BOOL "" FORCE)
set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(vendored/glm EXCLUDE_FROM_ALL)
add_subdirectory(vendored/nlohmann_json)
add_subdirectory(vendored/spdlog)
add_subdirectory(src)

if(MSVC)
    message(STATUS "Using MSVC")

    # close /showIncludes
    string(REPLACE "/showIncludes" "" CMAKE_DEPFILE_FLAGS_C "${CMAKE_DEPFILE_FLAGS_C}")
    string(REPLACE "/showIncludes" "" CMAKE_DEPFILE_FLAGS_CXX "${CMAKE_DEPFILE_FLAGS_CXX}")
endif()


target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_23

)
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    CXX_MODULE_STD ON
    CXX_STANDARD_REQUIRED ON
)
# Link to the actual SDL3 library.
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        glm::glm
        nlohmann_json::nlohmann_json
        spdlog::spdlog
)

