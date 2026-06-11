#pragma once

#include <SFML/System/Vector2.hpp>

class Object {
protected:
  int m_health;

public:
  int getHealth() const { return m_health; }
  void setHealth(int health) {
    m_health = health;
  }

  virtual sf::Vector2f get_pos() const = 0;
  virtual void set_pos(sf::Vector2f position) = 0;

  Object(int health) : m_health(health) {}
  virtual ~Object() = default;
};
