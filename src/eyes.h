#ifndef __EYES_H__
#define __EYES_H__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <string>

#include "animatedsprite.h"

class Eyes : public AnimatedSprite
{
public:
    Eyes(const std::string &fileName, int x = 0, int y = 0);
    ~Eyes();

    void die();

private:
    int m_tileWidth;
    int m_tileHeight;
};

#endif // __EYES_H__
