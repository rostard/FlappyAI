#ifndef TRON_SPRITE_H
#define TRON_SPRITE_H


#include "Vector2f.h"

class Texture;
class Shader;

class Sprite {
public:
    Sprite(Texture* image, Vector2f position, Vector2f size);
    static void initBuffers();

    void render(Shader* shader);

    const Vector2f &getSize() const;

    void setSize(const Vector2f &size);

    const Vector2f &getPosition() const;

    void setPosition(const Vector2f &position);

    bool intersect(Sprite* r);
private:
    static unsigned int vbo;
    static unsigned int vao;

    Texture* image;
    Vector2f size;
    Vector2f position;
};


#endif //TRON_SPRITE_H
