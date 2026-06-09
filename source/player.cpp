#include "player.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>

Player::Player(const float radius, const std::size_t point_count)
{
    m_player.setRadius(radius);
    m_player.setPointCount(point_count);
    m_player.setOutlineColor(sf::Color::Magenta);
    m_player.setOutlineThickness(1);
    m_player.setFillColor(sf::Color::White);
}

void Player::create_bullet()
{
    Bullet bullet(3.0f, 50, 1, get_pos());
    bullets.push_back(bullet);
}

void Player::update_actions(sf::RenderWindow &window)
{
    // PLAYER
    window.draw(m_player);

    // BULLET
    for (auto &b : bullets)
    {
        b.move_bullet();
        window.draw(b.get_bullet());
    }
}

void Player::actions_handler()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        m_player.move(0, -m_speed * m_dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_player.move(-m_speed * m_dt, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_player.move(0, m_speed * m_dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_player.move(m_speed * m_dt, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        create_bullet();
}

Bullet::Bullet(const float radius, const float point_count, const float velocity, const sf::Vector2f current_pos)
{
    m_bullet.setPosition(current_pos);
    m_bullet.setRadius(radius);
    m_bullet.setPointCount(point_count);
    m_bullet.setFillColor(sf::Color::White);
    m_bullet.setOutlineColor(sf::Color::Magenta);
    m_bullet.setOutlineThickness(5);
    m_velocity = velocity;
}

void Bullet::move_bullet()
{
    m_bullet.move(0, -m_velocity);
}
