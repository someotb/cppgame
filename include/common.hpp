#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <atomic>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

// Base class Object
class Object {
protected:
  int m_health;

public:
  int getHealth() const { return m_health; }
  void setHealth(int health) { m_health = health; }

  virtual sf::Vector2f get_pos() const = 0;
  virtual void set_pos(sf::Vector2f position) = 0;

  Object(int health) : m_health(health) {}
  virtual ~Object() = default;
};

// Global Flags
struct GlobalFlags {
  std::atomic_bool quit{false};
  std::atomic_bool player_alive{true};
};

// Player control layout
enum class LayoutType { WASD, IJKL };

struct Layout {
public:
  sf::Keyboard::Key m_forward;
  sf::Keyboard::Key m_backward;
  sf::Keyboard::Key m_rightward;
  sf::Keyboard::Key m_leftward;
  sf::Keyboard::Key m_shoot;

  Layout(const LayoutType &layout);
  ~Layout() = default;
};

// Object direction
enum class ObjectDirectionType { UP, DOWN };

// Status bar
class StatusBar : public Object {
private:
  sf::Font m_font;
  sf::Vector2f m_position;

public:
  sf::Text m_statusBar;
  void set_pos(const sf::Vector2f position) override { m_position = position; }
  sf::Vector2f get_pos() const override { return m_position; }

  StatusBar();
  ~StatusBar() = default;
};
