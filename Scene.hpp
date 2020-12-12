#ifndef SCENE_HPP
#define SCENE_HPP

/* =================[Dependencies]=========================================== */
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
/* =================[Class Definition]======================================= */

class Line
{
public:
  Line();
  enum Type
  {
    INVALID = 0,
    TEXT,
    SET,
    MUSIC,
    FADEIN,
    FADEOUT,
    DELAY
  };
  
  static Line::Type getType(const std::wstring& command);
  static unsigned int getTypeSize(Line::Type lineType);

  Line::Type   type;
  sf::String   content;
private:
  
};

class Scene
{
public:
  Scene();
  ~Scene();
  void updateSize(unsigned int x, unsigned int y);
  // Text
  bool load(const std::string& path);
  const Line& getNextLine(void);
  bool isAtFinalLine(void) const;
  const Line& getPrevLine(void);
  bool isAtFirstLine(void) const;
  
  // Graphics
  void update(const sf::String& str);
  /* -- Background -- */
  bool isBackgroundVisible(void) const;
  const sf::Sprite& background(void) const;
  void makeBackgroundVisible(bool isVisible);
  void setBackground(const sf::Texture& texture);
  /* -- Left Character -- */
  bool leftCharacterIsVisible(void) const;
  const sf::Sprite& leftCharacter(void) const;
  void makeLeftCharacterVisible(bool isVisible);
  void setLeftCharacter(const sf::Texture& texture);
  /* -- Right Character -- */
  bool rightCharacterIsVisible(void) const;
  const sf::Sprite& rightCharacter(void) const;
  void makeRightCharacterVisible(bool isVisible);
  void setRightCharacter(const sf::Texture& texture);

private: /* Functions */

private: /* Variables */
  unsigned int        m_windowX;
  unsigned int        m_windowY;
  // Text                   
  size_t              m_currentTextNum;
  std::vector<Line>   m_lines;
  // Background
  bool                m_backgroundVisible;
  sf::Sprite          m_backgroundSprite;
  // Left Character   
  bool                m_leftCharacterVisible;
  sf::Sprite          m_leftCharacterSprite;
  // Right Character  
  bool                m_rightCharacterVisible;
  sf::Sprite          m_rightCharacterSprite;
};

#endif /* SCENE_HPP */
/* =================[End of file]============================================ */