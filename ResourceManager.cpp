/* =================[Includes]=============================================== */
#include "ResourceManager.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>
/* =================[Private Data]=========================================== */

/* =================[Public Class Functions]================================= */

template <typename Resource>
void ResourceManager<Resource>::load(Identifier id,
                                     const std::string& filename,
                                     int* opRes)
{
  std::unique_ptr<Resource> resource(new Resource());

  if(opRes != nullptr){ *opRes = OperationResult::LoadSuccessful; }
  // Try to load the resource
  if(!resource->loadFromFile(filename))
  {
    if(opRes != nullptr){ *opRes = OperationResult::UnableToOpenFile; }
    throw std::runtime_error("ResourceHolder::load - Failed to load "
                             + filename);
  }

  auto inserted = m_resourceMap.insert(std::make_pair(id, std::move(resource)));

  assert(inserted.second == true && "Resources loaded mutiple times");
  if(inserted.second == false) // Check that the insert was successful
  {
    if(opRes != nullptr){ *opRes = OperationResult::KeyAlreadyExists; }
  }
}

template <typename Resource>
void ResourceManager<Resource>::unload(Identifier id)
{
  auto remElNum = m_resourceMap.erase(id);
  assert(remElNum != 0 && "No resouce with the given ID");
}

template <typename Resource>
bool ResourceManager<Resource>::isLoaded(Identifier id)
{
  auto found = m_resourceMap.find(id);
  return( found != m_resourceMap.end() );
}

template <typename Resource>
const Resource& ResourceManager<Resource>::get(Identifier id,
                                               int* opRes) const
{
  auto found = m_resourceMap.find(id);

  if(opRes != nullptr){ *opRes = OperationResult::GetSuccessful; }
  if(found == m_resourceMap.end()) //Check that the resource was found
  {
    assert((found != m_resourceMap.end()) && "The resource was not found");
    if(opRes != nullptr){ *opRes = OperationResult::KeyDoesNotExist; }
  }
  return( *found->second ); // Return the resource
}


// Explicitely instanciate used templates so the compiler will compile them
template class ResourceManager<sf::Texture>;
template class ResourceManager<sf::Font>;

/* =================[Private Class Functions]================================ */
template <typename Resource>
ResourceManager<Resource>::ResourceManager()
{ 
  std::cout << m_name + ": Creating.." << std::endl; 
}
template <typename Resource>
ResourceManager<Resource>::~ResourceManager() 
{ 
  std::cout << m_name + ": Destroying.." << std::endl; 
}
/* =================[End of file]============================================ */