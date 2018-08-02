#include <iostream>
#include "Obstacle.h"
#include "Sprite.h"
#include "Texture.h"
#include "ResourceManager.h"

Obstacle::Obstacle(Texture* texture, float xPos, float height) : height(height){
    topPipe = new Sprite(texture, Vector2f(xPos, height + GAP + 15), Vector2f(1.5f, 15));
    bottomPipe = new Sprite(texture, Vector2f(xPos, height - GAP - 15), Vector2f(1.5f, -15));
}


Obstacle::Obstacle(Texture* texture, float xPos) : Obstacle(texture, xPos, std::rand() % 15 + 7) {

}

void Obstacle::move(float amt) {
    Vector2f topPos = topPipe->getPosition();
    Vector2f botPos = bottomPipe->getPosition();

    topPos.setX(topPos.getX() - amt);
    botPos.setX(botPos.getX() - amt);

    topPipe->setPosition(topPos);
    bottomPipe->setPosition(botPos);

}

void Obstacle::render(Shader* shader) {
    topPipe->render(shader);
    bottomPipe->render(shader);
}

bool Obstacle::posLessThanX(float x) {
    return bottomPipe->getPosition().getX() < x;
}

float Obstacle::getX() const{
    return topPipe->getPosition().getX();
}

bool Obstacle::intersect(Sprite *sprite) {
    return bottomPipe->intersect(sprite) || topPipe->intersect(sprite);
}

float Obstacle::getHeight() const {
    return height;
}

bool Obstacle::isPassed() const {
    return passed;
}

void Obstacle::setPassed(bool passed) {
    Obstacle::passed = passed;
}

float Obstacle::getWidth() const {
    return topPipe->getSize().getX();
}
