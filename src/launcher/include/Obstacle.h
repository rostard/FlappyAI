//
// Created by rostard on 26.01.18.
//

#ifndef TRON_OBSTACLE_H
#define TRON_OBSTACLE_H

class Sprite;
class Texture;
class Shader;

class Obstacle {
public:

    Obstacle(Texture* texture, float xPos, float height);
    Obstacle(Texture* texture, float xPos);

    virtual ~Obstacle();

    void move(float amt);

    void render(Shader* shader);

    bool posLessThanX(float x);

    float getX() const;

    float getHeight() const;

    float getWidth() const;

    bool intersect(Sprite* sprite);

    bool isPassed() const;

    void setPassed(bool passed);

private:
    float height;
    const float GAP = 3.5;
    Sprite* topPipe;
    Sprite* bottomPipe;
    bool passed = false;

};


#endif //TRON_OBSTACLE_H
