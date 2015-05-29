#include "game.h"
#include "world.h"

// XXX game should contain Scenes handling, update and input.
// All game related things should live at some scene
Game::Game(int width, int height, const std::string &title)
{
    m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height),
            title);

    m_windowSize = m_window->getSize();

    m_window->setKeyRepeatEnabled(false);
    m_window->setVerticalSyncEnabled(true);

    // game world, really it's just a scene
    World *world = new World();
    m_scenes.push_back(world);
}

Game::~Game()
{
    m_scenes.clear();
}

int Game::excelsior()
{
    // view setup
    sf::View view = sf::View(sf::FloatRect(0, 0, m_windowSize.x, m_windowSize.y));
    //sf::View view = sf::View(sf::FloatRect(0, mapSize.y - m_windowSize.y,
                //m_windowSize.x, m_windowSize.y));
    m_window->setView(view);
    //

    // timing
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // XXX move it to a common file
    sf::Clock clock;

    // LOOP
    while (m_window->isOpen()) {
        // update...
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            //scene.update(TimePerFrame);
            pollEvent();
            update(dt);
        }

        //m_window->draw(ml);
        //m_window->draw(scene);

        //m_window->display();
        draw();
    }

    return 0;
}

void Game::pollEvent()
{
    sf::Event event;
    while (m_window->pollEvent(event)) {
        m_scenes[0]->handleEvent(event); // XXX

        if (event.type == sf::Event::Closed)
            m_window->close();

        if (event.key.code == sf::Keyboard::Escape)
            m_window->close();
    }
}

void Game::update(sf::Time delta)
{
    m_scenes[0]->update(delta); // XXX
}

void Game::draw()
{
    m_window->clear(sf::Color(0, 0, 0));

    m_window->setView(m_window->getDefaultView());
    m_window->draw(*m_scenes[0]); // XXX

    m_window->display();
}
