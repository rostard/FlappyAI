//
// Created by rostard on 26.01.18.
//

#ifndef TRON_VECTOR2F_H
#define TRON_VECTOR2F_H


class Vector2f {
public:
    Vector2f(float x, float y);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

private:
    float x;
    float y;
};


#endif //TRON_VECTOR2F_H
