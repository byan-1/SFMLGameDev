#ifndef TEXTURE_H
#define TEXTURE_H
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include "ResourceIdentifiers.h"

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
  void load(Identifier id, const std::string &filename);
  template <typename Parameter>
  void load(Identifier id, const std::string &filename, const Parameter &secondParam);
  Resource &get(Identifier id);
  const Resource &get(Identifier id) const;

private:
  void insertResource(Identifier id, std::unique_ptr<Resource> resource);
  std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"

#endif