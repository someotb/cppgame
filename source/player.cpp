#include "player.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <memory>

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
    Bullet bullet(10.0f, 100, 1000, get_pos());
    m_bullets.push_back(bullet);
    m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), [](Bullet& b){ return b.bullet_is_out(); }), m_bullets.end());
}

void Player::update_actions(sf::RenderWindow &window)
{
    // PLAYER
    window.draw(m_player);

    // BULLET
    for (auto &b : m_bullets)
    {
        b.move_bullet(m_dt);
        window.draw(b.get_bullet());
    }
}

void Player::actions_handler(sf::RenderWindow &window)
{
    static bool space_was_pressed = false;
    bool space_pressed_now = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    auto win_size = window.getSize();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and not player_out(win_size, sf::Keyboard::W))
        m_player.move(0.0f, -m_speed * m_dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and not player_out(win_size, sf::Keyboard::A))
        m_player.move(-m_speed * m_dt, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and not player_out(win_size, sf::Keyboard::S))
        m_player.move(0.0f, m_speed * m_dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and not player_out(win_size, sf::Keyboard::D))
        m_player.move(m_speed * m_dt, 0.0f);
    if (space_was_pressed == false and space_pressed_now == true)
        create_bullet();
    space_was_pressed = space_pressed_now;
}

bool Player::player_out(sf::Vector2u &win_size, const sf::Keyboard::Key &direction)
{
    auto player_pos = get_pos();
    if ((direction == sf::Keyboard::W) and (player_pos.y + m_speed * m_dt < 0.0f))
        return true;
    else if ((direction == sf::Keyboard::A) and (player_pos.x + m_speed * m_dt < 0.0f))
        return true;
    else if ((direction == sf::Keyboard::S) and (player_pos.y + m_speed * m_dt > win_size.y))
        return true;
    else if ((direction == sf::Keyboard::D) and (player_pos.x + m_speed * m_dt > win_size.x))
        return true;
    else return false;
}

Bullet::Bullet(const float radius, const float point_count, const float velocity, const sf::Vector2f current_pos)
{
    m_bullet.setPosition(current_pos);
    m_bullet.setRadius(radius);
    m_bullet.setPointCount(point_count);
    m_bullet.setFillColor(sf::Color::Transparent);
    m_bullet.setOutlineColor(sf::Color::Magenta);
    m_bullet.setOutlineThickness(1);
    m_velocity = velocity;
}

void Bullet::move_bullet(const float dt)
{
    m_bullet.move(0, -m_velocity * dt);
}

bool Bullet::bullet_is_out() const
{
    auto bulletPos = get_pos();
    if (bulletPos.x < 0 || bulletPos.y < 0)
        return true;
    return false;
}
