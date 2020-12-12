/* =================[Includes]=============================================== */
#include "Scene.hpp"

#include <cassert>
#include <iostream>
#include <locale>
#include <codecvt>

#include "ResourceManager.hpp"

/* =================[Private Data]=========================================== */

/* =================[Private Function Declaration]=========================== */
std::vector<int> getIDs(const std::wstring& str);
int              getID(const std::wstring& str);
/* =================[Public Class Functions]================================= */
/* --- Line --- */
Line::Line() :
  type(Type::INVALID),
  content(L"") 
{ }

Line::Type Line::getType(const std::wstring& command)
{
  Line::Type type = Type::INVALID;
  if(command == L"TEXT")           { type = Type::TEXT; }
  else if(command == L"SET")       { type = Type::SET; }
  else if(command == L"MUSIC")     { type = Type::MUSIC; }
  else if(command == L"FADEIN")    { type = Type::FADEIN; }
  else if(command == L"FADEOUT")   { type = Type::FADEOUT; }
  else if(command == L"DELAY")     { type = Type::DELAY; }
  
  return(type);
}

unsigned int Line::getTypeSize(Line::Type lineType)
{
  unsigned int size = 0;

  switch(lineType)
  {
    case Line::Type::TEXT:
      size = 4;
      break;
    case Line::Type::SET:
      size = 3;
      break;
    case Line::Type::MUSIC:
      size = 5;
      break;
    case Line::Type::FADEIN:
      size = 6;
      break;
    case Line::Type::FADEOUT:
      size = 7;
      break;
    default:
      break;
  }

  return(size);
}

/* --- Scene --- */
Scene::Scene() :
  m_backgroundVisible(true),
  m_leftCharacterVisible(true),
  m_rightCharacterVisible(true),
  m_currentTextNum(-1)
{
  printf("Scene: Creating...\r\n");
  m_lines.clear();
}

Scene::~Scene()
{
  printf("Scene: Destroying...\r\n");
}

void Scene::updateSize(unsigned int x, unsigned int y)
{
  m_windowX = x;
  m_windowY = y;
}

void Scene::update(const sf::String& lineContent)
{
  std::vector<int> ids = getIDs(lineContent);
  // The command is SET bg;leftChar;rightChar
  // Hence, ids.at(0) is the background id, at(1) the leftChar's, etc..
  if(ids.at(0) >= 0)
  {
    this->makeBackgroundVisible(true);
    this->setBackground(TextureManager::instance().get(ids.at(0)));
  }
  else
  { 
    this->makeBackgroundVisible(false); 
  }

  if(ids.at(1) >= 0)
  {
    this->makeLeftCharacterVisible(true);
    this->setLeftCharacter(TextureManager::instance().get(ids.at(1)));
  }
  else
  {
    this->makeLeftCharacterVisible(false);
  }

  if(ids.at(2) >= 0)
  {
    this->makeRightCharacterVisible(true);
    this->setRightCharacter(TextureManager::instance().get(ids.at(2)));
  }
  else
  {
    this->makeRightCharacterVisible(false);
  }
}

/* -- Text -- */
bool Scene::load(const std::string& path)
{
  bool success = false;
  const std::string gameExtension = ".scene";
  m_currentTextNum = -1;
  m_lines.clear();

  assert(path.find(gameExtension) != std::string::npos);
  
  // Load file
  std::wifstream sceneFile;
  sceneFile.open(path);
  success = sceneFile.good();
  assert(success == true && "File open failed");

  // Enable non utf8 characters like japanese and russian.
  // Have in mind that the font is important too. Arial won't take Japanese
  sceneFile.imbue(std::locale::locale(std::locale::locale(),
                                 new std::codecvt_utf8<wchar_t,
                                 0x10ffffUL,
                                 std::codecvt_mode::consume_header>));

  std::wstring lineRead; //
  int lineReadNum = 0;
  int setCmdRead = 0;
  Line line;

  while(std::getline(sceneFile, lineRead))
  {
    // File ended, stop reading
    if(lineRead.find(L"ENDFILE") != std::string::npos) { break; }
    
    // Search for command in the line
    for(size_t i = 0; i < lineRead.size(); i++)
    {
      if(lineRead[i] == L' ') // Command found (before spacebar)
      {
        line.type = Line::getType(lineRead.substr(0, i));
        switch(line.type)
        {
        case Line::Type::TEXT:
          // If no text was set, user an empty string
          if(lineRead.size() == (Line::getTypeSize(line.type) + 1)) 
            { line.content = L" "; }
          else 
            { line.content = sf::String(lineRead.substr(i + 1)); }
          m_lines.push_back(line);
          break;
        case Line::Type::SET:
          ++setCmdRead;
          line.content = sf::String(lineRead.substr(i + 1));;
          m_lines.push_back(line);
          // Preload files
          for(const int& id : getIDs(line.content))
          {
            if(id != -1)
            { 
              if(!TextureManager::instance().isLoaded(id))
              {
                std::wcout << id << std::endl;
                TextureManager::instance().load(id,
                  "resources/img/" + std::to_string(id) + ".png");
              }
            }
          }
          break;
        case Line::Type::MUSIC:
          printf("MUSIC at line: %d\r\n", lineReadNum);
          break;
        case Line::Type::FADEIN:
          printf("FADEIN at line: %d\r\n", lineReadNum);
          break;
        case Line::Type::FADEOUT:
          printf("FADEOUT at line: %d\r\n", lineReadNum);
          break;
        case Line::Type::DELAY:
          printf("DELAY at line: %d\r\n", lineReadNum);
          break;
        default:
          break;
        }
        break; // Exit for loop
      }
    } // endfor
    ++lineReadNum;
  } // endwhile
  printf("Lines read: %d. %d contained text\r\n", lineReadNum+1, m_lines.size());
  // Close file
  sceneFile.close();

  // Checks
  assert(m_lines.size() > 0 && "File had no lines");
  assert(setCmdRead > 0 && "No SET commands read");
 
  return success;
}

const Line& Scene::getNextLine(void)
{
  if(++m_currentTextNum >= m_lines.size()) 
   { m_currentTextNum = m_lines.size() - 1; }
  return(m_lines.at(m_currentTextNum));
}

bool Scene::isAtFinalLine(void) const
{
  return(m_currentTextNum >= m_lines.size() - 1);
}

const Line& Scene::getPrevLine(void)
{
  if(--m_currentTextNum < 0) { m_currentTextNum = 0; }
  return(m_lines.at(m_currentTextNum));
}

bool Scene::isAtFirstLine(void) const
{
  return(m_currentTextNum <= 0);
}

/* -- Background -- */
bool Scene::isBackgroundVisible(void) const
{
  return(m_backgroundVisible);
}

const sf::Sprite& Scene::background(void) const
{
  return(m_backgroundSprite);
}

void Scene::makeBackgroundVisible(bool isVisible)
{
  m_backgroundVisible = isVisible;
}

void Scene::setBackground(const sf::Texture& texture)
{
  m_backgroundSprite.setTexture(texture);
}

/* -- Left Character -- */
bool Scene::leftCharacterIsVisible(void) const
{
  return(m_leftCharacterVisible);
}

const sf::Sprite& Scene::leftCharacter(void) const
{
  return(m_leftCharacterSprite);
}

void Scene::makeLeftCharacterVisible(bool isVisible)
{
  m_leftCharacterVisible = isVisible;
}

void Scene::setLeftCharacter(const sf::Texture& texture)
{
  sf::Vector2u cSize = texture.getSize();
  printf("Loaded left char: (%d,%d)\r\n", cSize.x, cSize.y);
  m_leftCharacterSprite.setTexture(texture);
  m_leftCharacterSprite.setPosition(0.0f, (float)(1024 - cSize.y));
}

/* -- Right Character -- */
bool Scene::rightCharacterIsVisible(void) const
{
  return(m_rightCharacterVisible);
}

const sf::Sprite& Scene::rightCharacter(void) const
{
  return(m_rightCharacterSprite);
}

void Scene::makeRightCharacterVisible(bool isVisible)
{
  m_rightCharacterVisible = isVisible;
}

void Scene::setRightCharacter(const sf::Texture& texture)
{
  sf::Vector2u cSize = texture.getSize();
  printf("Loaded left char: (%d,%d)\r\n", cSize.x, cSize.y);
  m_rightCharacterSprite.setTexture(texture);
  m_rightCharacterSprite.setPosition((float)(m_windowX - cSize.x),
                                     (float)(m_windowY - cSize.y));
}
/* =================[Private Class Functions]================================ */

/* =================[Private Function Definition]============================ */

std::vector<int> getIDs(const std::wstring& str)
{
  const char separator = ';';
  std::vector<int> results;
  std::wstring::const_iterator start = str.begin();
  std::wstring::const_iterator end = str.end();
  std::wstring::const_iterator next = std::find(start, end, separator);
  
  while(next != end) 
  {
    results.push_back(getID(std::wstring(start, next)));
    start = next + 1;
    next = std::find(start, end, separator);
  }
  results.push_back(getID(std::wstring(start, next)));

  assert(results.size() == 3 && "Expected 3 IDs");

  return results;
}

int getID(const std::wstring& str)
{
  int id = -1;
  // Check that the string is actually an integer.
  // If it's not, consider the id as "invalid"
  if(!str.empty() 
    && (str.find_first_not_of(L"0123456789") == std::string::npos) )
  {
    id = std::stoi(str); // If it is, convert it
  }

  return(id);
}
/* =================[End of file]============================================ */