/* =================[Includes]=============================================== */
#include "GameEngine.hpp"
/* =================[Private Data]=========================================== */

/* =================[Private Function Declaration]=========================== */
bool collided(const sf::Sprite& obj1,
              const sf::Sprite& obj2,
              const sf::Vector2f& mov);

/* =================[Public Class Functions]================================= */
GameEngine::GameEngine()
{
  const std::string g_gameTitle = "Our Game :D";
  unsigned int baseWindowX = 1024;
  unsigned int baseWindowY = 719;

  printf("GameEngine: Creating...\r\n");

  unsigned int sf = 1;
  m_window.create(sf::VideoMode(baseWindowX*sf, baseWindowY*sf),
                  g_gameTitle,
                  sf::Style::Titlebar | sf::Style::Close); // No rescale

  m_debugger.setEnabled(false);

  m_player.initialize(1000);
  m_player.setSpeed(50.0f);
  m_player.setPosition(200.0f, 100.0f);
  m_player.setRotation(0.0f);
  m_player.setScale(2.0f, 2.0f);

  m_crate.initialize(1100);
  m_crate.setSpeed(50.0f);
  m_crate.setPosition(400.0f, 300.0f);
  m_crate.setRotation(0.0f);
  m_crate.setScale(2.0f, 2.0f);

  m_scene.updateSize(baseWindowX, baseWindowY);
  m_scene.load("resources/scripts/script.scene");
  m_chat.updateSize(baseWindowX, baseWindowY);
  processLine(m_scene.getNextLine());
}

GameEngine::~GameEngine()
{
  printf("GameEngine: Destroying...\r\n");
}

void GameEngine::run(void)
{
  const sf::Time timePerFrame = sf::seconds(1.f / 120.f);
  sf::Clock gameClock;
  sf::Time dt = sf::Time::Zero;

  while(m_window.isOpen())
  {
    this->handleEvents();
    // Use while instead of if in case the game freezes
    if(gameClock.getElapsedTime() >= timePerFrame)
    {
      dt = gameClock.restart();
      m_debugger.setString("FPS: " + std::to_string(round(1 / dt.asSeconds())),
                           Debugger::FPS);
      this->update(timePerFrame);
      this->render();
    }
  }
}
/* =================[Private Class Functions]================================ */
void GameEngine::handleEvents(void)
{
  sf::Event event;
  while(m_window.pollEvent(event))
  {
    switch(m_inputHandler.processEvent(event))
    {
      case InputHandler::WindowClosed:
        m_window.close();
        break;
      case InputHandler::NextChat:
        processLine(m_scene.getNextLine());
        break;
      case InputHandler::PrevChat:
        /*if(!m_scene.isAtFirstLine())
          { processLine(m_scene.getPrevLine()); }*/
        break;
      case InputHandler::EnableDebug:
        m_debugger.setEnabled(!m_debugger.enabled());
        break;
      default:
        break;
    }
  }
}

void GameEngine::processLine(const Line& line)
{
  if(!m_scene.isAtFinalLine())
  {
    switch(line.type)
    {
    case Line::Type::TEXT:
      m_chat.setText(line.content);
      break;
    case Line::Type::SET:
      m_scene.update(line.content);
      processLine(m_scene.getNextLine());
      break;
    default:
      break;
    }
  }
}

void GameEngine::update(const sf::Time& fps)
{
  fps.asSeconds();
  m_chat.update();

  sf::Vector2f vec = m_inputHandler.playerMovement()
                     * m_player.speed()
                     * fps.asSeconds();
  if(!collided(m_player.drawable(), m_crate.drawable(), vec))
  {
    m_player.move(vec);
  }
  else
    printf("Collided\r\n");

}

void GameEngine::render(void)
{
  m_window.clear(sf::Color(0x18,0x18,0x18));
  // Scene
  if(m_scene.isBackgroundVisible() == true)
    { m_window.draw(m_scene.background()); }
  if(m_scene.leftCharacterIsVisible() == true)
    { m_window.draw(m_scene.leftCharacter()); }
  if(m_scene.rightCharacterIsVisible() == true)
    { m_window.draw(m_scene.rightCharacter()); }
    
  // Chat box
  if(m_chat.isEnabled() == true)
  {
    m_window.draw(m_chat.drawable());
    m_window.draw(m_chat.text());
  }
  
  // Collision objects
  m_window.draw(m_crate.drawable());

  // Player
  m_window.draw(m_player.drawable());
  // Draw HUD

  // Debug
  if(m_debugger.enabled() == true)
  {
    for(size_t i = 0; i < m_debugger.elements(); i++)
    {
      m_window.draw(*m_debugger.drawable(i));
    }
  }

  m_window.display();
}

/* =================[Private Function Definition]=========================== */
// AABB collision detection
bool collided(const sf::Sprite& obj1,
              const sf::Sprite& obj2,
              const sf::Vector2f& mov)
{
  sf::FloatRect obj1Rec = obj1.getGlobalBounds();
  obj1Rec.height += mov.y;
  obj1Rec.width += mov.x;
  return (obj1Rec.intersects(obj2.getGlobalBounds()));
}

/* =================[End of file]============================================ */