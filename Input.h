//
// Created by rostard on 12.12.17.
//

#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H


#include <vector>
#include "Window.h"

class Input {
public:
    Input() = delete;

    static void update();
    static void setWindowCapture(Window &window);
    static bool isKeyDown(const int& key);
    static bool isKeyPress(const int& key);
    static bool isKeyUp(const int& key);

private:
    static const unsigned int numOfKeys = 300;
    static std::vector<int> lastKeys;
    static Window* window;
};


#endif //ENGINE_INPUT_H
