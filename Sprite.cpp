//
// Created by rostard on 26.01.18.
//

#include "Sprite.h"
#include <GL/glew.h>
#include "Texture.h"
#include "Shader.h"
#include <cmath>

unsigned int Sprite::vbo = 0;
unsigned int Sprite::vao = 0;


Sprite::Sprite(Texture *image, Vector2f position, Vector2f size) : image(image), position(position), size(size) {}

void Sprite::initBuffers() {
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    Vector2f vertices[] = {Vector2f(-1, -1), Vector2f(0, 0),
                           Vector2f(-1, 1), Vector2f(0, 1),
                           Vector2f(1, 1), Vector2f(1, 1),
                           Vector2f(-1, -1), Vector2f(0, 0),
                           Vector2f(1, 1), Vector2f(1, 1),
                           Vector2f(1, -1), Vector2f(1, 0)};

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2f) * 2, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2f) * 2, (void*)(sizeof(Vector2f)));
}

void Sprite::render(Shader* shader) {
    image->bind(0);
    shader->bind();
    shader->setInt("image", 0);
    shader->setVec2("size", size);
    shader->setVec2("position", position);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

const Vector2f &Sprite::getSize() const {
    return size;
}

void Sprite::setSize(const Vector2f &size) {
    Sprite::size = size;
}

const Vector2f &Sprite::getPosition() const {
    return position;
}

void Sprite::setPosition(const Vector2f &position) {
    Sprite::position = position;
}

bool Sprite::intersect(Sprite *r) {
    bool xIntersection = std::abs(r->getPosition().getX() - getPosition().getX()) < (std::abs(r->getSize().getX()) + std::abs(getSize().getX()));
    bool yIntersection = std::abs(r->getPosition().getY() - getPosition().getY()) < (std::abs(r->getSize().getY()) + std::abs(getSize().getY()));
    return xIntersection && yIntersection;
}

