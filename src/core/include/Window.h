//
// Created by rostard on 11.12.17.
//

#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H


#include "core_export.h"
#include <string>


class GLFWwindow;

class CORE_EXPORT Window {
public:
    Window() = delete;

    static void initGLFW();

    static void createWindow(const unsigned int screen_width, const unsigned int screen_height,
                      const std::string& title);

    static bool isShouldClose();

    static void render();

    static bool getKey(int key);


    static bool getMouseButton(int button);

    static void dispose();

	static void pollEvents();
private:
    static GLFWwindow* window;
    static bool initialized;
};


#endif //ENGINE_WINDOW_H
