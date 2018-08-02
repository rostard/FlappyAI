//
// Created by rostard on 12.12.17.
//

#include <algorithm>
#include <iostream>
#include "Input.h"

std::vector<int> Input::lastKeys = std::vector<int>();
Window* Input::window = nullptr;

void Input::update() {
    //TODO: fix jamming keys after pressing few seconds

    lastKeys.clear();
    for(unsigned int i = 0; i < numOfKeys; i++){
        if(window->getKey(i)){
            lastKeys.push_back(i);
        }
    }
}

bool Input::isKeyDown(const int &key) {
    return window->getKey(key) && (std::find(lastKeys.begin(), lastKeys.end(), key) == lastKeys.end());
}

bool Input::isKeyPress(const int &key) {
    return std::find(lastKeys.begin(), lastKeys.end(), key) != lastKeys.end();
}

bool Input::isKeyUp(const int &key) {
    return !window->getKey(key) && (std::find(lastKeys.begin(), lastKeys.end(), key) != lastKeys.end());
}

void Input::setWindowCapture(Window &window) {
    Input::window = &window;
}
