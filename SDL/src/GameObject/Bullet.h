#pragma once

#include <string>
#include <memory>
#include "CMath.h"
#include "Sprite2D.h"
#include "SpriteAnimation.h"
#include "Robot.h"

class Bullet {
public:
    Bullet(const std::string& texturePath, const Vector2& position, const Vector2& direction, float speed,
        float maxRange, int owner, int width, int height, float rotation, bool isAnimated,
        float animationDuration, std::shared_ptr<Robot> shooterRobot, int frameCount,
        int numAction, float frameTime, bool isAttached, bool isUsingLeftHand);

    static std::shared_ptr<Bullet> CreateBullet(const Vector2& position, const Vector2& direction, int owner,
        float maxRange, const std::string& bulletType, float rotation,
        std::shared_ptr<Robot> shooterRobot = nullptr, bool isUsingLeftHand = false);

    void Update(float deltaTime);

    bool IsOffScreen() const;
    bool HasExceededMaxRange() const;
    bool HasAnimationCompleted() const;

    Vector2 GetPosition() const;
    int GetWidth() const;
    int GetHeight() const;
    void Draw(SDL_Renderer* renderer);
    std::shared_ptr<Sprite2D> GetSprite() const;
    std::shared_ptr<SpriteAnimation> GetAnimation() const;

    int GetOwner() const {
        return m_owner;
    }


    Vector2 GetDirection() const {
        return m_direction;
    }

    void SetHandOffset(const Vector2& offset) {
        m_handOffset = offset; // Setter for hand offset
    }
    void SetBulletType(const std::string& bulletType);
    std::string Bullet::GetBulletType();
    bool m_isUsingLeftHand;

private:
    Vector2 m_position;            // Current position of the bullet
    Vector2 m_direction;           // Direction of the bullet's movement
    Vector2 m_handOffset;          // Offset from the shooter's position for the bullet
    float m_speed;                 // Speed of the bullet
    float m_maxRange;              // Maximum range the bullet can travel
    float m_distanceTraveled;      // Distance the bullet has traveled
    int m_owner;                   // Identifier for the bullet's owner (e.g., which robot fired it)
    


    std::shared_ptr<Sprite2D> m_sprite;              // Sprite for static bullets
    std::shared_ptr<SpriteAnimation> m_animation;    // Animation for animated bullets
    std::string m_bulletType;


    float m_rotation;              // Rotation of the bullet
    bool m_isAnimated;             // Indicates if the bullet is animated
    bool m_isAttached;
    float m_animationDuration;     // Duration for animated bullets
    float m_animationTime;         // Elapsed time of the animation
    std::shared_ptr<Robot> m_shooterRobot; // Pointer to the robot that fired the bullet

};