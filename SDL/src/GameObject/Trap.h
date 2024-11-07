#pragma once
#include "SpriteAnimation.h"

class Trap
{
public:
    Trap(std::shared_ptr<TextureManager> texture, int frameCount, int numAction, float frameTime, float x, float y);
    ~Trap();

    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);

    Vector2 GetPosition() const;
    void SetPosition(float x, float y);

    void SetSize(float width, float height);
    Vector2 GetSize() const;

    float GetWidth() const;
    float GetHeight() const;

    int GetCurrentFrame() ;

    void SetRotation(float rotation);
    float GetRotation() const;
private:
    std::shared_ptr<SpriteAnimation> m_animation;
    float m_width;
    float m_height;
    float m_rotation;
};
        