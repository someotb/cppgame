#include "player.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "cppgame");
    window.setFramerateLimit(240);

    Player player(10, 100);
    player.set_speed(1000.0f);
    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        player.set_dt(dt);
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear(sf::Color::Black);
        player.actions_handler(window);
        player.update_actions(window);
        window.display();
    }

    return 0;
}
