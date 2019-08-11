//
// Created by rostard on 26.01.18.
//

#pragma once
#include "core_export.h"

struct CORE_EXPORT Vector3f{
    Vector3f(float x, float y, float z);

    float x;
    float y;
    float z;

    float getX() const;

    float getY() const;

    float getZ() const;
};

class CORE_EXPORT Vector2f {
public:
    Vector2f();
    Vector2f(float x, float y);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

private:
    float x;
    float y;
};
