cmake_minimum_required(VERSION 3.5)
project(plyr)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PLYR_SRCS src/plyr.c src/ui.c  src/audio.c src/queue.c src/song.c)
# Linux -pthread shenanigans
if (CMAKE_SYSTEM_NAME STREQUAL Linux)
  set(THREADS_PREFER_PTHREAD_FLAG ON)
  find_package(Threads REQUIRED)
endif()

#=== LIBRARY: cimgui + Dear ImGui
add_library(cimgui STATIC
    libs/cimgui/cimgui.cpp
    libs/cimgui/cimgui.h
    libs/cimgui/imgui/imgui.cpp
    libs/cimgui/imgui/imgui.h
    libs/cimgui/imgui/imgui_widgets.cpp
    libs/cimgui/imgui/imgui_draw.cpp
    libs/cimgui/imgui/imgui_tables.cpp
    libs/cimgui/imgui/imgui_demo.cpp)
target_include_directories(cimgui INTERFACE libs/cimgui)


#=== LIBRARY: sokol
# add headers to the the file list because they are useful to have in IDEs
set(SOKOL_HEADERS
    libs/sokol/sokol_gfx.h
    libs/sokol/sokol_app.h
    libs/sokol/sokol_imgui.h
    libs/sokol/sokol_glue.h)
if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
  add_library(sokol STATIC libs/sokol/sokol.c ${SOKOL_HEADERS})
  target_compile_options(sokol PRIVATE -x objective-c)
  target_link_libraries(sokol PUBLIC
        "-framework QuartzCore"
        "-framework Cocoa"
        "-framework MetalKit"
        "-framework Metal")
else()
  add_library(sokol STATIC libs/sokol/sokol.c ${SOKOL_HEADERS})
  if (CMAKE_SYSTEM_NAME STREQUAL Linux)
    target_link_libraries(sokol INTERFACE X11 Xi Xcursor GL dl m)
    target_link_libraries(sokol PUBLIC Threads::Threads)
  endif()
endif()
target_link_libraries(sokol PUBLIC cimgui)
target_include_directories(sokol INTERFACE libs/sokol)

include(FetchContent)

# Fetch TagLib
FetchContent_Declare(
  Taglib
  GIT_REPOSITORY https://github.com/taglib/taglib.git
)

FetchContent_MakeAvailable(Taglib)
set_target_properties(tag PROPERTIES ENABLE_BINDINGS ON)

#=== EXECUTABLE: plyr
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
  add_executable(plyr WIN32  ${PLYR_SRCS})
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT plyr)
else()
  add_executable(plyr ${PLYR_SRCS})
endif()

add_subdirectory(libs/nativefiledialog-cmake)
target_include_directories(plyr PRIVATE libs/nativefiledialog-cmake/src/include)
target_include_directories(plyr PRIVATE ${taglib_SOURCE_DIR} ${taglib_BINARY_DIR})
target_link_libraries(plyr sokol tag_c  "-framework AppKit" nativefiledialog )

# Emscripten-specific linker options
if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  # use our own minimal shell.html
  target_link_options(plyr PRIVATE --shell-file ../sokol/shell.html)
  # link with WebGL2
  target_link_options(plyr PRIVATE -sUSE_WEBGL2=1)
  # WASM+JS size optimizations
  target_link_options(plyr PRIVATE -sNO_FILESYSTEM=1 -sASSERTIONS=0 -sMALLOC=emmalloc --closure=1)
endif()

# explicitly strip dead code
if (CMAKE_C_COMPILER_ID MATCHES "Clang" AND NOT CMAKE_SYSTEM_NAME STREQUAL Emscripten)
  target_link_options(plyr PRIVATE LINKER:-dead_strip)
endif()

target_compile_options(plyr PRIVATE -fsanitize=address)
target_link_options(plyr PRIVATE -fsanitize=address)

# this hack removes the xxx-CMakeForceLinker.cxx dummy file
set_target_properties(plyr PROPERTIES LINKER_LANGUAGE C)
