#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <string>
#include <memory>

class Sprite : public sf::Drawable
{
public:
    Sprite(const std::string &fileName);
    virtual ~Sprite();

    virtual void setPosition(int x, int y);
    void setPosition(sf::Vector2f point);
    virtual sf::Vector2f position() const;

    virtual void setScale(float scaleX, float scaleY);
    virtual int width() const;
    virtual int height() const;

    virtual void setRotation(float angle);
    virtual float rotation() const;

    virtual void setVisible(bool visible);
    virtual bool visible() const;

    // 0.0-1.0
    virtual void setTransparency(float value);

    virtual void update(sf::Time delta = sf::Time::Zero);

    virtual bool collideWith(Sprite *sprite);

    virtual void move(const float x, const float y);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual bool load(const std::string &fileName);

    sf::Sprite m_sprite;
    std::shared_ptr<sf::Texture> m_texture;

    int m_width;
    int m_height;

    bool m_visible;
};

#endif // __SPRITE_H__
