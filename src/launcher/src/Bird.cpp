//
// Created by rostard on 26.01.18.
//

#include "Bird.h"
#include "Vector2f.h"
#include "Sprite.h"
#include "Window.h"
#include "Obstacle.h"

#define GRAVITY 0.09
#define LIFT  0.8

Bird::Bird(Texture *texture){
    sprite = new Sprite(texture, Vector2f(10, 15), Vector2f(1, 1));
}

bool Bird::shouldDie(std::list<Obstacle *> obstacles) {
    if(sprite->getPosition().getY() <= 0 || sprite->getPosition().getY() > 30) return true;
    for(auto i : obstacles){
        if(i->intersect(sprite))return true;
    }
    return false;
}

void Bird::move() {
    Vector2f pos = sprite->getPosition();
    velocity -= GRAVITY;
    pos.setY(pos.getY() + velocity);

    sprite->setPosition(pos);
}

void Bird::render(Shader* shader) {
    sprite->render(shader);
}

void Bird::jump() {
    if(velocity<0)velocity = LIFT;
}

void Bird::reset() {
    sprite->setPosition(Vector2f(10, 15));
    dead = false;
}

float Bird::getY() const {
    return sprite->getPosition().getY();
}

float Bird::getX() const{
    return sprite->getPosition().getX();
}

void Bird::setDistance(float xD, float yD) {
    xDistance = xD;
    yDistance = yD;
}

float Bird::getXDistance() const {
    return xDistance;
}

float Bird::getYDistance() const {
    return yDistance;
}

float Bird::getVelocity() const {
    return velocity;
}

float Bird::getWidth() const {
    return sprite->getSize().getX();
}

Bird::~Bird() {
    delete sprite;
}
