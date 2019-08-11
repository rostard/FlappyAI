include(GenerateExportHeader)

find_package(OpenGL REQUIRED)
list(APPEND CMAKE_PREFIX_PATH "C:/Users/kosbo/source/repos/rostard/FlappyAI/src/launcher/src/dependencies")
find_package(GLFW3 REQUIRED)
find_package(freetype REQUIRED)


file(GLOB_RECURSE lib_includes "include/*.h")
file(GLOB_RECURSE lib_sources "src/*.cpp")

message(${lib_sources})


add_library(core SHARED ${lib_sources})

generate_export_header(core EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/exports/core_export.h")

target_include_directories(core PUBLIC "include" "src" "${CMAKE_BINARY_DIR}/exports" ${FREETYPE_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${GLFW3_INCLUDE_DIR})
target_link_libraries(core glad ${OPENGL_LIBRARIES} ${GLFW3_LIBRARY} ${FREETYPE_LIBRARIES} )
