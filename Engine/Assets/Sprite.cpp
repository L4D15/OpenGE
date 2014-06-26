#include "Engine/Assets/Sprite.hpp"
#include "Engine/Core/Math/Vector3.hpp"
#include "Engine/Core/Game.hpp"
#include <sstream>
#include <fstream>

/**
 * @brief Sprite::Sprite
 * @param name
 * @param filePath
 */
Sprite::Sprite(const std::string name, const std::string filePath)
: RenderizableAsset(name, filePath)
{
    std::fstream file;
    std::string jsonFilePath;
    json_spirit::Value root;

    jsonFilePath = filePath.substr(0,filePath.find_last_of('.')).append(".json");

    bool bParsed;

    file.open(jsonFilePath.c_str());

    bParsed = json_spirit::read(file, root);

    if (bParsed == true)
    {
      json_spirit::Array animations;

      animations = root.getObject().at("animations").getArray();

      std::string name;
      int w, h, frames;
      float frameRate;
      bool oscillate;

      int heightAcum = 0;

      for (unsigned int index = 0; index < animations.size(); ++index)
      {
        name = animations[index].getObject().at("name").getString();
        w = animations[index].getObject().at("width").getInt();
        h = animations[index].getObject().at("height").getInt();
        frames = animations[index].getObject().at("frames").getInt();
        frameRate = animations[index].getObject().at("frame-rate").getReal();
        oscillate = animations[index].getObject().at("oscillate").getBool();

        AddAnimation(name, 0, heightAcum, w, h, frames, frameRate, oscillate);
        heightAcum += h;
      }

      defaultAnimation = root.getObject().at("default_animation").getString();

      // Load image
      texture = IMG_LoadTexture(Game::window->renderer, filePath.c_str());
      SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }
    else
    {
        std::stringstream ss;

        ss << "-- [!] Sprite::Sprite() - Error, JSON file " << jsonFilePath << " couldn't be parsed.";
        Game::Log(ss.str());
    }
    file.close();
}

/**
 * @brief Sprite::~Sprite
 */
Sprite::~Sprite()
{

}

/**
 * @brief Sprite::Render
 * @param pos
 * @param rot
 * @param scale
 */
void Sprite::Render(const Vector3& pos, const Quaternion& rot, const Vector3& scale) const
{
    SDL_Rect geometry;

    geometry.x = pos.x - width * scale.x * 0.5f;
    geometry.y = pos.y - height * scale.y * 0.5f;
    geometry.w = width * scale.x;
    geometry.h = height * scale.y;

    float rotation = 0.0f;
    // TODO: Convert quaternion to fixed euler angles

    SDL_Point pivotPoint;

    pivotPoint.x = pos.x;
    pivotPoint.y = pos.y;

    SDL_RenderCopyEx(Game::window->renderer, texture, NULL, &geometry, rotation, &pivotPoint, SDL_FLIP_NONE);

}

/**
 * @brief Sprite::Render
 * @param animation
 * @param frame
 * @param pos
 * @param rot
 * @param scale
 */
void Sprite::Render(const string animation, const unsigned int frame, const Vector3 &pos, const Quaternion &rot, const Vector3 &scale) const
{
    const Animation& anim = animationsMapper.at(animation);

    SDL_Rect drawGeometry;

    drawGeometry.x = pos.x - anim.w * scale.x * 0.5f;
    drawGeometry.y = pos.y - anim.h * scale.y * 0.5f;
    drawGeometry.w = anim.w * scale.x;
    drawGeometry.h = anim.h * scale.y;

    SDL_Rect frameGeometry;

    frameGeometry = anim.ToSDLRect(frame);

    SDL_Point pivotPoint;

    pivotPoint.x = pos.x;
    pivotPoint.y = pos.y;

    // TODO: Convert quaternion to fixed euler angles
    float rotation = 0.0f;

    SDL_RenderCopyEx(Game::window->renderer, texture, &frameGeometry, &drawGeometry, rotation, &pivotPoint, SDL_FLIP_NONE);
}

/**
 * @brief Sprite::AddAnimation
 * @param name
 * @param x
 * @param y
 * @param w
 * @param h
 * @param frames
 * @param frameRate
 */
void Sprite::AddAnimation(const string name, const int x, const int y, const int w, const int h, const int frames, const float frameRate, const bool oscillate)
{
    Animation* animation;

    animation = new Animation(x, y, w, h, frames, frameRate, oscillate, name);

    std::pair<std::string, Animation> mappedAnimation(name, *animation);

    animationsMapper.insert(mappedAnimation);
}

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param name [description]
 * @return [description]
 */
Sprite::Animation* Sprite::GetAnimation(const std::string name)
{
    std::map<std::string, Animation>::iterator animIt = animationsMapper.find(name);

    if (animIt != animationsMapper.end())
    {
        return & animIt->second;
    }
    else
    {
        return NULL;
    }
}

/**
 * @brief Sprite::ToString
 * @return
 */
std::string Sprite::ToString() const
{
	std::stringstream ss;

	ss << "-- [#] " << name << " @ " << filePath;

	return ss.str();
}
