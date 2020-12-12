/* =================[Includes]=============================================== */

#include "InputHandler.hpp"

/* =================[Private Data]=========================================== */

/* =================[Public Class Functions]================================= */

InputHandler::InputHandler()
{
  printf("InputHandler: Creating...\r\n");
  // Player Movement
  m_kb_moveUp       = sf::Keyboard::W     + KeyCodeShift::Keyboard;
  m_kb_moveDown     = sf::Keyboard::S     + KeyCodeShift::Keyboard;
  m_kb_moveLeft     = sf::Keyboard::A     + KeyCodeShift::Keyboard;
  m_kb_moveRight    = sf::Keyboard::D     + KeyCodeShift::Keyboard;
  // Chat
  m_kb_nextChat     = sf::Keyboard::Right + KeyCodeShift::Keyboard;
  m_ms_nextChat     = sf::Mouse::Left     + KeyCodeShift::Mouse;
  m_kb_prevChat     = sf::Keyboard::Left  + KeyCodeShift::Keyboard;
  m_ms_prevChat     = sf::Mouse::Right    + KeyCodeShift::Mouse;
  // 
  m_kb_enableDebug  = sf::Keyboard::F1    + KeyCodeShift::Keyboard;
}

InputHandler::~InputHandler()
{
  printf("InputHandler: Destroying...\r\n");
}

InputHandler::Input InputHandler::processEvent(const sf::Event& event)
{
	Input ret = InputHandler::NoInput;
  switch(event.type)
  {
  case sf::Event::KeyReleased:
    ret = handlePlayerInput(event.key.code + KeyCodeShift::Keyboard, false);
    break;
  case sf::Event::KeyPressed:
    ret = handlePlayerInput(event.key.code + KeyCodeShift::Keyboard, true);
    break;
  case sf::Event::MouseButtonReleased:
    ret = handlePlayerInput(event.key.code + KeyCodeShift::Mouse, false);
    break;
  case sf::Event::MouseButtonPressed:
    ret = handlePlayerInput(event.key.code + KeyCodeShift::Mouse, true);
    break;
  case sf::Event::Closed:
    ret = InputHandler::WindowClosed;
    break;
  default:
    break;
  }
	return ret;
}

const sf::Vector2f& InputHandler::playerMovement(void) const
{
  return(m_playerMovement);
}

/* =================[Private Class Functions]================================ */

InputHandler::Input InputHandler::handlePlayerInput(int keyCode, 
                                                    bool isPressed)
{
  InputHandler::Input ret = InputHandler::NoInput;
  if((keyCode == m_kb_moveUp) || (keyCode == m_kb_moveDown))
  {
    if((keyCode == m_kb_moveUp))
    {
      m_playerMovement.y = -1.0f*(int)isPressed;
    }
    else if(keyCode == m_kb_moveDown)
    {
      m_playerMovement.y = 1.0f*(int)isPressed;
    }
  }
  else if((keyCode == m_kb_moveLeft) || (keyCode == m_kb_moveRight))
  {
    if(keyCode == m_kb_moveLeft)
    {
      m_playerMovement.x = -1.0f * (int)isPressed;
    }
    else if(keyCode == m_kb_moveRight)
    {
      m_playerMovement.x = 1.0f * (int)isPressed;
    }
  }
  else
  {
    m_playerMovement.x = 0;
    m_playerMovement.y = 0;
  }

  if(((keyCode == m_kb_nextChat) || (keyCode == m_ms_nextChat))
    && (isPressed == false))
  { 
    ret = InputHandler::NextChat;
  }
  if(((keyCode == m_kb_prevChat) || (keyCode == m_ms_prevChat))
    && (isPressed == false))
  { 
    ret = InputHandler::PrevChat;
  }
  
  if((keyCode == m_kb_enableDebug) && (isPressed == false))
  { 
    ret = InputHandler::EnableDebug;
  }
 
  return(ret);
}

/* =================[End of file]============================================ */
