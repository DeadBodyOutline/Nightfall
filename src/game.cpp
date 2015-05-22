#include "game.h"

Game::Game(int width, int height)
{
}

Game::~Game()
{
    m_scenes.clear();
}

void Game::excelsior()
{
}

//void Game::addLayer(Layer &layer)
//{
    //m_layers.push_back(&layer);
//}

//LayerContainer &Game::layers()
//{
    //return m_layers;
//}

//void Game::update(sf::Time delta)
//{
    //for (auto layer : m_layers)
        //layer->update(delta);
//}

//void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
    //for (auto layer : m_layers)
        //target.draw(*layer);
//}
