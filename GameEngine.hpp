#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

/* =================[Dependencies]=========================================== */
#include <SFML/Graphics.hpp>

#include "InputHandler.hpp"
#include "Entity.hpp"
#include "Chat.hpp"
#include "Scene.hpp"
#include "Debugger.h"
/* =================[Class Definition]======================================= */

class GameEngine
{
public:
  GameEngine();
  ~GameEngine();

  void run(void);

private: /* Functions */
  void handleEvents(void);
  void processLine(const Line& line);
  void update(const sf::Time& fps);
  void render(void);

private: /* Variables */
  InputHandler       m_inputHandler;
  Chat               m_chat;
  Line               m_line;
  Scene              m_scene;
  Debugger           m_debugger;

  Entity             m_player;
  Entity             m_crate;

  sf::RenderWindow   m_window;
};

#endif /* GAMEENGINE_HPP */
/* =================[End of file]============================================ */