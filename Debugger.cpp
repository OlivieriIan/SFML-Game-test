/* =================[Includes]=============================================== */
#include "Debugger.h"

#include <assert.h>

#include "ResourceManager.hpp"
/* =================[Private Data]=========================================== */
Debugger::Debugger() : 
  m_enabled(true)
{
  printf("Debugger: Creating...\r\n");
  FontManager::instance().load(Fonts::Debug, "resources/fonts/debug.ttf");
  m_texts.push_back(new sf::Text);

  for(size_t i = 0; i < m_texts.size(); i++)
  {
    m_texts[i]->setFont(FontManager::instance().get(Fonts::Debug));
    m_texts[i]->setCharacterSize(20); // in pixels
    m_texts[i]->setFillColor(sf::Color::Black);
    m_texts[i]->setPosition(0.0f, 0.0f);
  }
}
Debugger::~Debugger()
{
  printf("Debugger: Destroying...\r\n");
  for(size_t i = 0; i < m_texts.size(); i++)
  {
    delete m_texts[i];
  }
  m_texts.clear();
}

void Debugger::setEnabled(bool state)
{
  m_enabled = state;
}

bool Debugger::enabled(void) const
{
  return m_enabled;
}

size_t Debugger::elements(void) const
{
  return(m_texts.size() + 0); // drawable elements count
}

void Debugger::setString(const sf::String& text, size_t i)
{
  assert(i < m_texts.size() && "Index out of bounds");
  m_texts[i]->setString(text);
}

void Debugger::setPosition(float x, float y, size_t i)
{
  assert(i < this->elements() && "Index out of bounds");
  m_texts[i]->setPosition(x, y);
}

const sf::Drawable* Debugger::drawable(size_t i) const
{
  assert(i < this->elements() && "Index out of bounds");
  return m_texts[i];
}
/* =================[Public Class Functions]================================= */

/* =================[Private Class Functions]================================ */

/* =================[End of file]============================================ */