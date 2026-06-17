#include "common.hpp"

StatusBar::StatusBar() : Object(9999999) {
  if (!m_font.loadFromFile("../fonts/ISAACFONTDESCRIPTIONENGRUS-OUTLINE_0.TTF"))
    throw std::runtime_error("Unable to load arial.ttf. Please install it.");
  m_statusBar.setFont(m_font);
  m_statusBar.setCharacterSize(24);
  m_statusBar.setFillColor(sf::Color::White);
}
