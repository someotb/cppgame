#include "player.hpp"
#include "common.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>

Player::Player(const float radius, const std::size_t point_count,
               const Layout layout)
    : Object(100), m_layout(std::move(layout)) {
  m_player.setRadius(radius);
  m_player.setPointCount(point_count);
  m_player.setOutlineColor(sf::Color::Magenta);
  m_player.setOutlineThickness(1);
  m_player.setFillColor(sf::Color::White);
  StatusBar bar;
}

void Player::create_bullet() {
  Bullet bullet(10.0f, 100, 1000, get_pos());
  m_bullets.push_back(bullet);
  m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(),
                                 [](Bullet &b) { return b.bullet_is_out(); }),
                  m_bullets.end());
}

bool Player::is_player_alive() {
  if (getHealth() <= 0)
    return false;
  return true;
}

void Player::drow_objects(sf::RenderWindow &window) {
  // PLAYER
  window.draw(m_player);

  // STATUS BAR
  window.draw(m_bar.m_statusBar);

  // BULLET
  for (auto &b : m_bullets) {
    b.move_bullet(m_dt);
    window.draw(b.get_bullet());
  }
}

void Player::status_bar(sf::RenderWindow &window) {
  sf::Vector2u winSize = window.getSize();
  sf::Vector2u statusBar_pos(winSize.x - 150, winSize.y - 30);
  m_bar.m_statusBar.setPosition(statusBar_pos.x, statusBar_pos.y);
  m_bar.m_statusBar.setString("Healt: " + std::to_string(getHealth()));
}

void Player::actions_handler(sf::RenderWindow &window, GlobalFlags &gFlags) {
  // Status Bar
  status_bar(window);

  // Player movement
  movement_handler(window);

  // Player status
  if (!is_player_alive())
    gFlags.player_alive = false;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    setHealth(getHealth() - 1);
}

void Player::movement_handler(sf::RenderWindow &window) {
  static bool shoot_was_pressed = false;
  bool shoot_pressed_now = sf::Keyboard::isKeyPressed(m_layout.m_shoot);
  auto winSize = window.getSize();
  if (sf::Keyboard::isKeyPressed(m_layout.m_forward) and
      not player_out(winSize, m_layout.m_forward))
    m_player.move(0.0f, -m_speed * m_dt);
  if (sf::Keyboard::isKeyPressed(m_layout.m_leftward) and
      not player_out(winSize, m_layout.m_leftward))
    m_player.move(-m_speed * m_dt, 0.0f);
  if (sf::Keyboard::isKeyPressed(m_layout.m_backward) and
      not player_out(winSize, m_layout.m_backward))
    m_player.move(0.0f, m_speed * m_dt);
  if (sf::Keyboard::isKeyPressed(m_layout.m_rightward) and
      not player_out(winSize, m_layout.m_rightward))
    m_player.move(m_speed * m_dt, 0.0f);
  if (shoot_was_pressed == false and shoot_pressed_now == true)
    create_bullet();
  shoot_was_pressed = shoot_pressed_now;
}

bool Player::player_out(sf::Vector2u &win_size,
                        const sf::Keyboard::Key &direction) {
  auto player_pos = get_pos();
  if ((direction == m_layout.m_forward) and
      (player_pos.y + m_speed * m_dt < 0.0f))
    return true;
  else if ((direction == m_layout.m_leftward) and
           (player_pos.x + m_speed * m_dt < 0.0f))
    return true;
  else if ((direction == m_layout.m_backward) and
           (player_pos.y + m_speed * m_dt > win_size.y))
    return true;
  else if ((direction == m_layout.m_rightward) and
           (player_pos.x + m_speed * m_dt > win_size.x))
    return true;
  else
    return false;
}

Bullet::Bullet(const float radius, const float point_count,
               const float velocity, const sf::Vector2f current_pos)
    : Object(1) {
  m_bullet.setPosition(current_pos);
  m_bullet.setRadius(radius);
  m_bullet.setPointCount(point_count);
  m_bullet.setFillColor(sf::Color::Transparent);
  m_bullet.setOutlineColor(sf::Color::Magenta);
  m_bullet.setOutlineThickness(1);
  m_velocity = velocity;
}

void Bullet::move_bullet(const float dt) { m_bullet.move(0, -m_velocity * dt); }

bool Bullet::bullet_is_out() const {
  auto bulletPos = get_pos();
  if (bulletPos.x < 0 || bulletPos.y < 0)
    return true;
  return false;
}
