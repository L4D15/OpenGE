#include "SpriteRenderer.hpp"
#include "Engine/Core/Game.hpp"
#include <sstream>

/**
 * @brief SpriteRenderer::SpriteRenderer
 */
SpriteRenderer::SpriteRenderer()
: sprite(Game::resourceManager->GetAsset<Sprite>("Assets/Sprites/Missing_Image.png"))
{
    currentAnimation = &sprite.GetDefaultAnimation();
    currentFrame = 0;
    timeFrameStart = Game::time->GetTime();
    frameDuration = 1000.0f / currentAnimation->frameRate;
    animGoingRight = true;
}

/**
 * @brief SpriteRenderer::SpriteRenderer
 * @param spritePath
 */
SpriteRenderer::SpriteRenderer(const std::string spritePath)
: sprite(Game::resourceManager->GetAsset<Sprite>(spritePath))
{
    currentAnimation = &sprite.GetDefaultAnimation();
    currentFrame = 0;
    frameDuration = 1000.0f / currentAnimation->frameRate;
    animGoingRight = true;

    std::stringstream ss;

    ss << "Frame Duration: " << frameDuration;

    Game::Log(ss.str());
}

/**
 * @brief SpriteRenderer::Render
 * @param pos
 * @param rot
 * @param scale
 */
void SpriteRenderer::Render(const Vector3 &pos, const Quaternion &rot, const Vector3 &scale) const
{
    sprite.Render(currentAnimation->name, currentFrame, pos, rot, scale);
}

/**
 * @brief SpriteRenderer::Update
 */
void SpriteRenderer::Update()
{
    Uint32 timeElapsed;

    timeElapsed = Game::time->GetTime() - timeFrameStart;

    if (timeElapsed >= frameDuration && currentAnimation->frames > 1)
    {
        if (animGoingRight == true)
        {
            if (currentFrame == currentAnimation->frames - 1)
            {
                animGoingRight = false;
                --currentFrame;
            }
            else
            {
                ++currentFrame;
            }
        }
        else
        {
            if (currentFrame == 0)
            {
                animGoingRight = true;
                ++currentFrame;
            }
            else
            {
                --currentFrame;
            }
        }
        timeFrameStart = Game::time->GetTime();
    }
}
