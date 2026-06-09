#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <cstddef>
#include <ctime>
#include <vector>

class Bullet
{
    private:
        sf::CircleShape m_bullet;
        float m_velocity = 200;
    public:
        void move_bullet();

        sf::CircleShape get_bullet() { return m_bullet; }

        Bullet(const float radius, const float point_count, const float velocity, const sf::Vector2f current_pos);
        ~Bullet() = default;
};

class Player
{
    private:
        sf::CircleShape m_player;
        float m_speed;
        float m_dt;
        std::vector<Bullet> bullets;
    public:
        void actions_handler();

        void create_bullet();

        void update_actions(sf::RenderWindow &window);

        void set_size(const float radius, const std::size_t point_count) { m_player.setRadius(radius); m_player.setPointCount(point_count); }
        float get_radius() { return m_player.getRadius(); }
        std::size_t get_point_count() { return m_player.getPointCount(); }

        void set_pos(const float x, const float y) { m_player.setPosition(x, y); }
        sf::Vector2f get_pos() { return m_player.getPosition(); }

        void set_dt(const float dt) { m_dt = dt; }
        float get_dt() { return m_dt; }

        void set_speed(const float speed) { m_speed = speed; }
        float get_speed() { return m_speed; }

        sf::CircleShape get_player() { return m_player; }

        Player(const float radius, const std::size_t point_count);
        ~Player() = default;
};
