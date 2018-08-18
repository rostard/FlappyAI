//
// Created by rostard on 02.08.18.
//

#ifndef FLAPPYAI_FONT_H
#define FLAPPYAI_FONT_H


#include <string>
#include <GL/glew.h>
#include <map>
#include "Vector2f.h"
#include "Shader.h"

struct Character {
    GLuint     textureID;  // ID handle of the glyph texture
    Vector2f size;       // size of glyph
    Vector2f bearing;    // Offset from baseline to left/top of glyph
    GLuint     advance;    // Offset to advance to next glyph
};


class Font {
public:
    Font(const std::string& fontPath, unsigned int fontSize = 48);

    virtual ~Font();

    void RenderText(Shader* s, std::string text, GLfloat x, GLfloat y, GLfloat scale, Vector3f color);
private:
    std::map<GLchar, Character> Characters;
    GLuint VAO, VBO;
};


#endif //FLAPPYAI_FONT_H
