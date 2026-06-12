#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

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
