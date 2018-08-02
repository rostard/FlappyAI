//
// Created by rostard on 17.12.17.
//

#include <GL/glew.h>
#include "Texture.h"

Texture::Texture(int id, int width, int height) : id(id), width(width), height(height) {}

void Texture::bind(unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
}

Texture::Texture():id(0), width(0), height(0) {}


