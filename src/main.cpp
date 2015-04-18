#include <iostream>
#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

using namespace std;

int main(int argc, char **argv)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "ld32");
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // XXX move it to a common file

    sf::Vector2u windowSize = window.getSize();

    sf::View view(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
    window.setView(view);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        window.clear(sf::Color(0, 0, 0));

        // update...
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
        }

        window.display();
    }
}
