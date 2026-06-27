#include "player.hpp"
#include "common.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <stdexcept>

Player::Player(const float radius, const std::size_t point_count,
               const Layout layout, const ObjectDirectionType objDirection,
               const StatusBar bar)
    : Object(100), m_layout(std::move(layout)),
      m_obj_direction(std::move(objDirection)), m_bar(std::move(bar)) {
  m_player.setRadius(radius);
  m_player.setPointCount(point_count);
  m_player.setOutlineColor(sf::Color::Magenta);
  m_player.setOutlineThickness(1);
  m_player.setFillColor(sf::Color::White);

  // Top Border
  m_topBorder.setSize(sf::Vector2f(WIDTH, 1.f));
  m_topBorder.setPosition(0.f, 30.f);
  m_topBorder.setFillColor(sf::Color::White);

  // Bottom order
  m_bottomBorder.setSize(sf::Vector2f(WIDTH, 1.f));
  m_bottomBorder.setPosition(0.f, HEIGHT - 1.f - 30.f);
  m_bottomBorder.setFillColor(sf::Color::White);

  // Left Border
  m_leftBorder.setSize(sf::Vector2f(1.f, HEIGHT - 60.f));
  m_leftBorder.setPosition(0.f, 30.f);
  m_leftBorder.setFillColor(sf::Color::White);

  // Right order
  m_rightBorder.setSize(sf::Vector2f(1.f, HEIGHT - 60.f));
  m_rightBorder.setPosition(WIDTH - 1.f, 30.f);
  m_rightBorder.setFillColor(sf::Color::White);
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
  window.draw(m_topBorder);
  window.draw(m_bottomBorder);
  window.draw(m_leftBorder);
  window.draw(m_rightBorder);

  // BULLET
  for (auto &b : m_bullets) {
    b.move_bullet(m_dt, m_obj_direction);
    window.draw(b.get_bullet());
  }
}

void Player::status_bar(sf::RenderWindow &window) {
  sf::Vector2u winSize = window.getSize();
  switch (m_obj_direction) {
  case ObjectDirectionType::UP: {
    sf::Vector2u statusBar_pos(winSize.x - 255, winSize.y - 30);
    m_bar.m_statusBar.setPosition(statusBar_pos.x, statusBar_pos.y);
    m_bar.m_statusBar.setString("Player Healt: " + std::to_string(getHealth()));
    break;
  }
  case ObjectDirectionType::DOWN: {
    sf::Vector2u statusBar_pos(winSize.x - 255, 0);
    m_bar.m_statusBar.setPosition(statusBar_pos.x, statusBar_pos.y);
    m_bar.m_statusBar.setString("Enemy Healt: " + std::to_string(getHealth()));
    break;
  }
  default:
    throw std::invalid_argument("Use supported ObjectDirectionType(UP, DOWN)");
  }
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
  if (sf::Keyboard::isKeyPressed(m_layout.m_shoot))
    create_bullet();
}

bool Player::player_out(sf::Vector2u &win_size,
                        const sf::Keyboard::Key &direction) {
  auto player_pos = get_pos();
  if ((direction == m_layout.m_forward) and
      (player_pos.y + m_speed * m_dt < 40.f))
    return true;
  else if ((direction == m_layout.m_leftward) and
           (player_pos.x + m_speed * m_dt < 10.f))
    return true;
  else if ((direction == m_layout.m_backward) and
           (player_pos.y + m_speed * m_dt > win_size.y - 55.f))
    return true;
  else if ((direction == m_layout.m_rightward) and
           (player_pos.x + m_speed * m_dt > win_size.x - 25.f))
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

void Bullet::move_bullet(const float dt, const ObjectDirectionType type) {
  switch (type) {
  case ObjectDirectionType::UP:
    m_bullet.move(0, -m_velocity * dt);
    break;
  case ObjectDirectionType::DOWN:
    m_bullet.move(0, m_velocity * dt);
    break;
  default:
    throw std::invalid_argument("Use supported ObjectDirectionType(UP, DOWN)");
  }
}

bool Bullet::bullet_is_out() const {
  auto bulletPos = get_pos();
  if (bulletPos.x < 0 || bulletPos.y < 0)
    return true;
  return false;
}
