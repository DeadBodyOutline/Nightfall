#include "animatedsprite.h"

#include <iostream>

AnimatedSprite::AnimatedSprite(const std::string &fileName, int width, int height)
    : Sprite(fileName)
{
    m_width = width;
    m_height = height;

    // XXX
    //m_sprite.setOrigin(m_width / 2, m_height / 2);
    m_sprite.setOrigin(0, 0);
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::addAnimation(const Animation &animation, sf::Time duration)
{
    m_animator.addAnimation(animation.name(), animation, duration);
}

void AnimatedSprite::play(const std::string &animation, bool loop)
{
    m_animator.playAnimation(animation, loop);
}

// TODO use states?
bool AnimatedSprite::isPlaying() const
{
    return m_animator.isPlayingAnimation();
}

void AnimatedSprite::stop()
{
    m_animator.stopAnimation();
}

std::string AnimatedSprite::current() const
{
    return m_animator.getPlayingAnimation();
}


void AnimatedSprite::setPosition(int x, int y)
{
    sf::Vector2f v(x, y);
    this->setPosition(v);
}

void AnimatedSprite::setPosition(sf::Vector2f point)
{
    if (point == Sprite::position())
        return;

    Sprite::setPosition(point.x, point.y);
}

sf::Vector2f AnimatedSprite::position() const
{
    return Sprite::position();
}

void AnimatedSprite::update(sf::Time delta)
{
    m_animator.update(delta);
    m_animator.animate(m_sprite);
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Sprite::draw(target, states);
}
