#include <iostream>

#include "animation.h"

Animation::Animation(const std::string &name, int frameWidth, int frameHeight)
    : thor::FrameAnimation()
    , m_name(name)
    , m_frameWidth(frameWidth)
    , m_frameHeight(frameHeight)
{
}

Animation::~Animation()
{
}

// animation over texture atlas
void Animation::addFrames(int x1, int x2, int y, float duration)
{
    const int step = (x1 < x2) ? +1 : -1;
    x2 += step;

    int x;
    for (x = x1; x != x2; x += step)
        thor::FrameAnimation::addFrame(duration, sf::IntRect(m_frameWidth * x,
                    m_frameHeight * y, m_frameWidth, m_frameHeight));
}

void Animation::addFramesY(int x, int y1, int y2, float duration)
{
    const int step = (y1 < y2) ? +1 : -1;
    y2 += step;

    int y;
    for (y = y1; y != y2; y += step)
        thor::FrameAnimation::addFrame(duration, sf::IntRect(m_frameWidth * x,
                    m_frameHeight * y, m_frameWidth, m_frameHeight));
}

void Animation::addWholeFile(int numColumns, int numFrames, float duration)
{
    int x, y, i;

    for (i = 0, x = 0, y = 0; i < numFrames; i++) {
        thor::FrameAnimation::addFrame(duration, sf::IntRect(m_frameWidth * x,
                    m_frameHeight * y, m_frameWidth, m_frameHeight));

        x = (x + 1) % numColumns;
        y = (x == 0) ? y + 1 : y;
    }
}

std::string Animation::name() const
{
    return m_name;
}

int Animation::width() const
{
    return m_frameWidth;
}

int Animation::height() const
{
    return m_frameHeight;
}
