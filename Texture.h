//
// Created by rostard on 17.12.17.
//

#ifndef DORMENGINE_TEXTURE_H
#define DORMENGINE_TEXTURE_H


class Texture {
public:
    Texture(int id, int width, int height);
    Texture();

    void bind(unsigned int slot);

    inline int getId() const { return id; }

    inline int getWidht() const { return width; }

    inline int getHeight() const { return height; }
private:
    int id;
    int width;
    int height;
};


#endif //DORMENGINE_TEXTURE_H
