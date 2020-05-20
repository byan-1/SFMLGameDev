#ifndef RESOURCEIDENTIFIERS_H
#define RESOURCEIDENTIFIERS_H

namespace sf
{
class Texture;
class Font;
} // namespace sf

namespace Textures
{
enum class ID
{
  Eagle,
  Raptor,
  Desert,
  TitleScreen
};
}

namespace Fonts
{
enum class ID
{
  Ubuntu,
  Arial
};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif