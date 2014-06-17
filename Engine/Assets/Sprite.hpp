#ifndef OPENGE_SPRITE_H
#define OPENGE_SPRITE_H

#include "Engine/Assets/RenderizableAsset.hpp"
#include "Engine/Libraries/Libraries.hpp"
#include <map>

class ResourceManager;
class TestScene;

class Sprite : public RenderizableAsset
{
public:
    // Animation Class
    class Animation
    {
    public:
        Animation(const float x, const float y,
                  const float w, const float h,
                  const unsigned int frames,
                  const float frameRate,
                  const std::string name) :
                x(x), y(y),
                w(w), h(h),
                frames(frames), frameRate(frameRate),
                name(name)
        {

        }

        const SDL_Rect ToSDLRect(unsigned int frame) const
        {
            SDL_Rect rect;

            rect.x = x + ((w * frame) % frames);
            rect.y = y;
            rect.w = w;
            rect.h = h;

            return rect;
        }

    public:
        int x, y;
        unsigned int w, h, frames;
        float frameRate;
        std::string name;
    };
    // ---

protected:
    Sprite(const std::string name, const std::string filePath);
    virtual ~Sprite();

    virtual void                Render(const Vector3& pos, const Quaternion& rot, const Vector3& scale) const;
    virtual void                Render(const std::string animation,
                                       const unsigned int frame,
                                       const Vector3& pos,
                                       const Quaternion& rot,
                                       const Vector3& scale) const;

    void                        AddAnimation(const std::string name,
                                             const int x, const int y,
                                             const int w, const int h,
                                             const int frames,
                                             const float frameRate);

public:
    virtual std::string         ToString() const;

protected:
    SDL_Texture*                texture;
    int                         width;
    int                         height;
    std::map<std::string,
                 Animation>     animationsMapper;

    friend class ResourceManager;
    friend class TestScene;
};


#endif // OPENGE_SPRITE_H
