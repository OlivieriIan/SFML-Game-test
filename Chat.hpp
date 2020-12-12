#ifndef CHAT_HPP
#define CHAT_HPP

/* =================[Dependencies]=========================================== */
#include <SFML/Graphics.hpp>
#include <iostream>
/* =================[Class Definition]======================================= */
class Chat
{
public:
  Chat();
  ~Chat();
  void update(void);

  void updateSize(unsigned int x, unsigned int y);
  const sf::RectangleShape& drawable(void) const;
  const sf::Text& text(void) const;
  void setText(const sf::String& str,
               const sf::Color& color = sf::Color::White);
  bool isEnabled(void) const;

private: /* Functions */
  sf::String wrapText(const sf::String& str,
                      unsigned int width,
                      const sf::Font& font,
                      unsigned int charicterSize,
                      bool bold = false);

private: /* Variables */
  // Text
  bool               m_enabled;
  float              m_width;
  float              m_height;
  float              m_x;
  float              m_y;
  size_t             m_textPos; // text position
  bool               m_textOver; // true when the appended text is over
  unsigned int       m_textSize;
  // sf::Font           m_font; // Loaded from ResourceManager
  sf::Text           m_text;
  sf::String         m_string;
  // Graphic
  sf::RectangleShape m_textBox;

};

#endif /* CHAT_HPP */
/* =================[End of file]============================================ */