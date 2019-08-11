

link_directories("src/dependencies")

find_package(OpenGL REQUIRED)

message(STATUS "OPENGL_INCLUDE_DIR:= ${OPENGL_INCLUDE_DIR}")
message(STATUS "OPENGL_LIBRARY:= ${OPENGL_LIBRARY}")
message(STATUS "OPENGL_LIBRARIES:= ${OPENGL_LIBRARIES}")


list(APPEND CMAKE_PREFIX_PATH "C:/Users/kosbo/source/repos/rostard/FlappyAI/src/launcher/src/dependencies")
#find_package(glew REQUIRED PATH dependencies)

file(GLOB_RECURSE lib_includes "include/*.h")
file(GLOB_RECURSE lib_sources "src/*.cpp")


add_library(glad STATIC "src/dependencies/glad.c")
target_include_directories(glad PUBLIC ${GLFW3_INCLUDE_DIR})

add_executable(launcher  ${lib_sources})

target_include_directories(launcher PUBLIC "include" "src" "${CMAKE_BINARY_DIR}/exports"  ${GLFW3_INCLUDE_DIR})
target_link_libraries(launcher glad core  ${OPENGL_LIBRARIES})


get_property(a TARGET launcher PROPERTY INCLUDE_DIRECTORIES)
message("!!!!!!!!!!! ${a}")

