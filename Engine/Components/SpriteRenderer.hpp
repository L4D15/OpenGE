#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include "Engine/Libraries/Libraries.hpp"
#include "Engine/Assets/Sprite.hpp"
#include "Engine/Core/Math/Vector3.hpp"
#include "Engine/Core/Math/Quaternion.hpp"

namespace Components
{

class SpriteRenderer : public anax::Component<SpriteRenderer>
{
public:
    SpriteRenderer();
    SpriteRenderer(const std::string spritePath);

    void                        Render(const Vector3& pos, const Quaternion& rot, const Vector3& scale) const;
    void                        Update();

protected:
    Sprite&                     sprite;

    // Animation
    Sprite::Animation const*    currentAnimation;
    Uint8                       currentFrame;
    float                       frameDuration;
    Uint32                      timeFrameStart;

private:
    bool                        animGoingRight;    
};
}

#endif // SPRITERENDERER_HPP
