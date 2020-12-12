#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

/* =================[Dependencies]=========================================== */
#include <SFML/Graphics.hpp>
/* =================[Class Definition]======================================= */

class InputHandler
{
public:
	InputHandler();
  ~InputHandler();

  enum Input
  {
    NoInput = -1,
    WindowClosed = 0,
    NextChat,
    PrevChat,
    EnableDebug
  };

	InputHandler::Input processEvent(const sf::Event& event);

  const sf::Vector2f& playerMovement(void) const;
private: /* Variables */
  sf::Vector2f       m_playerMovement;
  // Character
  int                m_kb_moveUp;
  int                m_kb_moveDown;
  int                m_kb_moveLeft;
  int                m_kb_moveRight;
  // Chat
  int                m_kb_nextChat;
  int                m_ms_nextChat;
  int                m_kb_prevChat;
  int                m_ms_prevChat;
  //
  int                m_kb_enableDebug;
private: /* Functions */
  enum KeyCodeShift
  {
    Keyboard = 0,
    Mouse = sf::Keyboard::KeyCount,
    Joystick = sf::Keyboard::KeyCount + sf::Mouse::ButtonCount
  };
  InputHandler::Input handlePlayerInput(int key,
                                        bool isPressed);
};

#endif /* INPUTHANDLER_HPP */
/* =================[End of file]============================================ */