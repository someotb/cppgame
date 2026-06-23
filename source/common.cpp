#include "common.hpp"
#include <stdexcept>
#include <string>

StatusBar::StatusBar() : Object(9999999) {
  if (!m_font.loadFromFile("../fonts/ISAACFONTDESCRIPTIONENGRUS-OUTLINE_0.TTF"))
    throw std::runtime_error("Unable to load arial.ttf. Please install it.");
  m_statusBar.setFont(m_font);
  m_statusBar.setCharacterSize(24);
  m_statusBar.setFillColor(sf::Color::White);
}

Layout::Layout(const LayoutType &layout) {
  switch (layout) {
  case LayoutType::WASD:
    m_forward = sf::Keyboard::Key::W;
    m_leftward = sf::Keyboard::Key::A;
    m_backward = sf::Keyboard::Key::S;
    m_rightward = sf::Keyboard::Key::D;
    m_shoot = sf::Keyboard::Key::C;
    break;
  case LayoutType::IJKL:
    m_forward = sf::Keyboard::Key::I;
    m_leftward = sf::Keyboard::Key::J;
    m_backward = sf::Keyboard::Key::K;
    m_rightward = sf::Keyboard::Key::L;
    m_shoot = sf::Keyboard::Key::N;
    break;
  default:
    throw std::invalid_argument("Use supported LayoutType(WASD, IJKL)");
  }
}
