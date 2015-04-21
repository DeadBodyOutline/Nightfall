#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>

#include <string>

class Animation : public thor::FrameAnimation
{
public:
    Animation(const std::string &name, int frameWidth, int frameHeight);
    virtual ~Animation();

    void addFrames(int x1, int x2, int y, float duration);
    void addFramesY(int x, int y1, int y2, float duration);
    void addWholeFile(int numColumns, int numFrames, float duration);

    virtual std::string name() const;

    virtual int width() const;
    virtual int height() const;

private:
    std::string m_name;

    int m_frameWidth;
    int m_frameHeight;
};

#endif // __ANIMATION_H__
