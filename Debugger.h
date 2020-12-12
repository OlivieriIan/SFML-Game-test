#ifndef DEBUGGER_HPP
#define DEBUGGER_HPP

/* =================[Dependencies]=========================================== */
#include <SFML/Graphics.hpp>
/* =================[Class Definition]======================================= */
class Debugger
{
public:
  enum TEXTS
  {
    FPS = 0
  };
  Debugger();
  ~Debugger();
  void                setEnabled(bool state);
  bool                enabled(void) const;
  size_t              elements(void) const;
  const sf::Drawable* drawable(size_t i) const;
  void                setPosition(float x, float y, size_t i);
  void                setString(const sf::String& text, size_t i);
private: /* Functions */
private: /* Variables */
  bool                   m_enabled;
  std::vector<sf::Text*> m_texts;

};
#endif /* DEBUGGER_HPP */
/* =================[End of file]============================================ */