#ifndef __GAME_H__
#define __GAME_H__

#include <SFML/Graphics.hpp>

#include <memory>

#include "scene.h"
#include "stuffmath.h"

typedef std::vector<Scene *> SceneContainer;
//typedef std::stack<Scene *> SceneContainer;

class Game
{
public:
    Game(int width, int height, const std::string &title = "");
    ~Game();

    int excelsior(); // because reasons

private:
    void pollEvent();
    void update(sf::Time delta = sf::Time::Zero);

    void render();

    std::shared_ptr<sf::RenderWindow> m_window;
    sf::Vector2u m_windowSize;

    SceneContainer m_scenes;
};

#endif // __GAME_H__
