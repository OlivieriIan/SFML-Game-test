/* =================[Includes]=============================================== */
#include "Chat.hpp"

#include "ResourceManager.hpp"
/* =================[Private Data]=========================================== */

/* =================[Public Class Functions]================================= */
Chat::Chat() :
  m_x(0),
  m_y(0),
  m_width(0),
  m_height(0),
  m_enabled(true),
  m_textOver(true),
  m_textSize(24),
  m_textPos(0)
{
  printf("Chat: Creating...\r\n");
  FontManager::instance().load(Fonts::Chat, "resources/fonts/chat.ttf");
  m_text.setFont(FontManager::instance().get(Fonts::Chat));
  m_text.setString(m_string);
  m_text.setCharacterSize(m_textSize); // in pixels
  m_text.setFillColor(sf::Color::White);
  m_text.setOutlineColor(sf::Color::Black);
  m_text.setOutlineThickness(1);

  // Text
  m_x = (800.0f - m_width)/2;
  m_y = 600.0f - m_height;
  m_text.setPosition(m_x + 10, m_y - 10);

  // Rectangle
  m_width = 800.0f*0.8;
  m_height = 600.0f*0.2;
  m_textBox.setSize(sf::Vector2f(m_width, m_height));
  m_textBox.setFillColor(sf::Color(0xF1,0x1F,0x1F,128));
  m_textBox.setOutlineColor(sf::Color::Black);
  m_textBox.setOutlineThickness(2);
  m_textBox.setPosition(m_x, m_y );
}

Chat::~Chat()
{
  printf("Chat: Destroying...\r\n");
}

void Chat::update(void)
{
  if(m_textOver == false) // is there text left to update?
  {
    if(++m_textPos < m_string.getSize())
    {
      sf::String currentStr = m_text.getString();
      currentStr += m_string[m_textPos];
      sf::String wrappedStr = "";
      wrappedStr = wrapText(currentStr,
                            (unsigned int)m_textBox.getSize().x,
                            FontManager::instance().get(Fonts::Chat),
                            m_textSize,
                            false);

      m_text.setString(wrappedStr);
    }
    else 
    {
      m_textOver = true;
    }
  }
}

void Chat::updateSize(unsigned int x, unsigned int y)
{
  m_width = x*0.8f;
  m_height = (float)m_textSize*5; // ~= textSize * (lineas + 1)
  m_textBox.setSize(sf::Vector2f(m_width, m_height));

  m_x = (x - m_width)/2;
  m_y = y - m_height;
  // Set text m_x + n to separate from box margin
  m_text.setPosition(m_x + 5.0f, m_y + 0.0f); 
  // Set box m_y + n to separate from window botton
  m_textBox.setPosition(m_x + 0.0f, m_y - 5.0f);
}

const sf::RectangleShape& Chat::drawable(void) const
{
  return(m_textBox);
}

const sf::Text& Chat::text(void) const
{
  return(m_text);
}

void Chat::setText(const sf::String& str,
                   const sf::Color& color)
{
  m_string = str;
  m_textOver = false;
  m_textPos = 0;
  m_text.setString(m_string[m_textPos]);
  m_text.setFillColor(color);
}

bool Chat::isEnabled(void) const
{
  return(m_enabled);
}

/* =================[Private Class Functions]================================ */
sf::String Chat::wrapText(const sf::String& string,
                          unsigned int width,
                          const sf::Font& font,
                          unsigned int charicterSize,
                          bool bold)
{
  unsigned currentOffset = 0;
  bool firstWord = true;
  std::size_t wordBegining = 0;
  sf::String wrappedText = string;

  for (std::size_t pos(0); pos < wrappedText.getSize(); ++pos) {
    auto currentChar = wrappedText[pos];
    if(currentChar == '\n') {
      currentOffset = 0;
      firstWord = true;
      continue;
    }
    else if(currentChar == ' ') {
      wordBegining = pos;
      firstWord = false;
    }

    auto glyph = font.getGlyph(currentChar, charicterSize, bold);
    currentOffset += (unsigned int)glyph.advance;

    if(!firstWord && currentOffset > width) {
      pos = wordBegining;
      wrappedText[pos] = '\n';
      firstWord = true;
      currentOffset = 0;
    }
  }

  return wrappedText;
}
/* =================[End of file]============================================ */

