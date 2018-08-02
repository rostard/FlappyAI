cmake_minimum_required(VERSION 3.9)
project(FlappyAI)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Window.h Window.cpp utility/Log.cpp utility/Log.h Vector2f.cpp Vector2f.h ResourceManager.cpp ResourceManager.h Shader.cpp Shader.h ShaderLoader.h ShaderLoader.cpp Texture.h Texture.cpp TextureLoader.h TextureLoader.cpp utility/SID.h dependencies/stb_image.h dependencies/stb_image.cpp Sprite.cpp Sprite.h Obstacle.cpp Obstacle.h Bird.cpp Bird.h Input.h Input.cpp NeuralNetwork.cpp NeuralNetwork.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} -L/usr/local/lib -I/usr/include/libpng16 -I/usr/include/freetype2 -lGLEW -lGL -lfreetype -lz  -lm  -lglfw -lrt -ldl -lXrandr -lXinerama -lXxf86vm -lXext -lXcursor -lXrender -lXfixes -lX11 -lpthread -lxcb -lXau -lassimp -lstdc++ )