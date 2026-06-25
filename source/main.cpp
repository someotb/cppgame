#include "common.hpp"
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

int main(int argc, char *argv[]) {
  sf::RenderWindow window(sf::VideoMode(800, 600), "cppgame");
  window.setFramerateLimit(240);

  // Global Flags
  GlobalFlags gFlags;

  // Players
  StatusBar playerBar;
  Player player(10, 100, Layout(LayoutType::WASD), ObjectDirectionType::UP,
                playerBar);
  player.set_speed(700.0f);

  StatusBar enemyBar;
  Player enemy(10, 100, Layout(LayoutType::IJKL), ObjectDirectionType::DOWN,
               enemyBar);
  enemy.set_speed(700.0f);

  // sf::Clock for stable objects velocity for every machine
  sf::Clock clock;

  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();

    player.set_dt(dt);
    enemy.set_dt(dt);

    sf::Event event;
    while (window.pollEvent(event))
      if (event.type == sf::Event::Closed)
        window.close();

    window.clear(sf::Color::Black);

    player.actions_handler(window, gFlags);
    player.drow_objects(window);

    enemy.actions_handler(window, gFlags);
    enemy.drow_objects(window);

    window.display();

    if (!gFlags.player_alive)
      break;
  }

  return 0;
}
