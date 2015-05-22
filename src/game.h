#ifndef __GAME_H__
#define __GAME_H__

#include <SFML/Graphics.hpp>
#include <stack>

#include "scene.h"

typedef std::vector<Scene *> SceneContainer;
//typedef std::stack<Scene *> SceneContainer;

// XXX will contain game loop, render and control (what layers to show on screen)
class Game
//class Game : public sf::Drawable
{
public:
    Game(int width, int height);
    ~Game();

    void excelsior(); // because reasons

private:
    //void addLayer(Layer &layer);

    //void update(sf::Time delta = sf::Time::Zero);
    //void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    SceneContainer m_scenes;
};

#endif // __GAME_H__
