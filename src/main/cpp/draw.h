#ifndef DRAW_H
#define DRAW_H
#include <vector>
#include "assetManager.h"
#include "errorChecker.h"

class Draw {
public:
    Draw();


    //old
    float displayW=  1080.0f;
    float displayH= 2220.0f;
    float m_posX,m_posY;
    //make virtual?
    Draw(AssetManager* ass);

    bool first = true;
    //
    void transform();
    void feedBack();
};

#endif //DRAW_H
