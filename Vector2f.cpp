//
// Created by rostard on 26.01.18.
//

#include "Vector2f.h"

Vector2f::Vector2f(float x, float y) : x(x), y(y) {}

float Vector2f::getX() const {
    return x;
}

void Vector2f::setX(float x) {
    Vector2f::x = x;
}

float Vector2f::getY() const {
    return y;
}

void Vector2f::setY(float y) {
    Vector2f::y = y;
}
