#ifndef ResourceManager_HPP
#define ResourceManager_HPP

/* =================[Dependencies]=========================================== */
#include <SFML/Graphics.hpp>
#include <iostream>
/* =================[Class Definition]======================================= */

class Fonts
{
public:
  enum ID
  {
    Chat,
    Debug
  };
};

typedef unsigned int Identifier;

template <typename Resource>
class ResourceManager // Singleton
{
public:
  // https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
  static ResourceManager& instance(void)
  {
    static ResourceManager instance;

    return instance;
  }

  void            load(Identifier id,
                       const std::string& filename,
                       int* opRes = nullptr);
  void            unload(Identifier id);
  bool            isLoaded(Identifier id);
  const Resource& get(Identifier id,
                      int* opRest = nullptr) const;
  //Resource&       get(Identifier id);

  enum OperationResult // Operation Result
  {
    Undefined = -1,
    LoadSuccessful = 0,
    UnableToOpenFile,
    KeyAlreadyExists,
    GetSuccessful,
    KeyDoesNotExist
  };

private: /* Functions */
  ResourceManager();
  ~ResourceManager();

private: /* Variables */
  static std::string                              m_name;
  std::map<Identifier, std::unique_ptr<Resource>> m_resourceMap;
};

// Remermber to explicitely instanciate used templates in the cpp file
typedef ResourceManager<sf::Texture> TextureManager;
typedef ResourceManager<sf::Font> FontManager;

std::string TextureManager::m_name = "TextureManager";
std::string FontManager::m_name = "FontManager";

#endif /* ResourceManager_HPP */
/* =================[End of file]============================================ */