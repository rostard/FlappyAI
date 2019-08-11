//
// Created by rostard on 02.08.18.
//

#ifndef FLAPPYAI_FONT_H
#define FLAPPYAI_FONT_H


#include <string>
#include <map>
#include "Vector2f.h"
#include "Shader.h"
#include "core_export.h"

struct Character {
    uint32_t textureID;  // ID handle of the glyph texture
    Vector2f size;       // size of glyph
    Vector2f bearing;    // Offset from baseline to left/top of glyph
    uint32_t advance;    // Offset to advance to next glyph
};


class CORE_EXPORT Font {
public:
    Font(const std::string& fontPath, unsigned int fontSize = 48);

    virtual ~Font();

    void RenderText(Shader* s, std::string text, float x, float y, float scale, Vector3f color);
private:
    std::map<char, Character> Characters;
    uint32_t VAO, VBO;
};


#endif //FLAPPYAI_FONT_H
