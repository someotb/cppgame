#pragma once

#include "common.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <cstddef>
#include <ctime>
#include <string>
#include <vector>

class Bullet : public Object {
private:
  sf::CircleShape m_bullet;
  float m_velocity;

public:
  void move_bullet(const float dt);

  bool bullet_is_out() const;

  void set_pos(const sf::Vector2f position) override {
    m_bullet.setPosition(position.x, position.y);
  }
  sf::Vector2f get_pos() const override { return m_bullet.getPosition(); }

  sf::CircleShape get_bullet() { return m_bullet; }

  Bullet(const float radius, const float point_count, const float velocity,
         const sf::Vector2f current_pos);
  ~Bullet() = default;
};

class Player : public Object {
private:
  sf::CircleShape m_player;
  float m_speed;
  float m_dt;
  std::vector<Bullet> m_bullets;
  StatusBar m_bar;
  Layout m_layout;

public:
  void actions_handler(sf::RenderWindow &window, GlobalFlags &gFlags);

  void movement_handler(sf::RenderWindow &window);

  bool player_out(sf::Vector2u &win_size, const sf::Keyboard::Key &direction);

  void create_bullet();

  bool is_player_alive();

  void drow_objects(sf::RenderWindow &window);

  void status_bar(sf::RenderWindow &window);

  void set_size(const float radius, const std::size_t point_count) {
    m_player.setRadius(radius);
    m_player.setPointCount(point_count);
  }
  float get_radius() { return m_player.getRadius(); }
  std::size_t get_point_count() { return m_player.getPointCount(); }

  void set_pos(const sf::Vector2f position) override {
    m_player.setPosition(position.x, position.y);
  }
  sf::Vector2f get_pos() const override { return m_player.getPosition(); }

  void set_dt(const float dt) { m_dt = dt; }
  float get_dt() { return m_dt; }

  void set_speed(const float speed) { m_speed = speed; }
  float get_speed() { return m_speed; }

  sf::CircleShape get_player() { return m_player; }

  Player(const float radius, const std::size_t point_count,
         const Layout layout);
  ~Player() = default;
};
