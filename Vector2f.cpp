//
// Created by rostard on 26.01.18.
//

#include "Vector2f.h"

Vector2f::Vector2f(float x, float y) : x(x), y(y) {}
Vector2f::Vector2f() : x(0), y(0){}
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



float Vector3f::getX() const {
    return x;
}

float Vector3f::getY() const {
    return y;
}

float Vector3f::getZ() const {
    return z;
}

Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}
