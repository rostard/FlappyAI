//
// Created by rostard on 26.01.18.
//

#ifndef TRON_BIRD_H
#define TRON_BIRD_H

#include <list>

class Texture;
class Sprite;
class Obstacle;
class Shader;

class Bird {
public:
    Bird(Texture* texture);

    bool shouldDie(std::list<Obstacle *>);

    void move();

    void jump();

    void render(Shader* shader);

    void reset();

    float getX() const;

    float getY() const;

    float getWidth() const;

    void setDistance(float xD, float yD);

    float getXDistance() const;

    float getYDistance() const;

    bool dead;

    float getVelocity() const;

private:
    Sprite* sprite;
    float xDistance;
    float yDistance;
    float velocity = 0;
};


#endif //TRON_BIRD_H
