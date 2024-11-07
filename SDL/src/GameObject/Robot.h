#pragma once
#include <memory>
#include <string>
#include "SpriteAnimation.h"
#include "CMath.h"

class Robot {
public:
    Robot(const std::string& texturePath, const Vector2& position, float rotation, float weight);
    ~Robot();

    void Update(float deltaTime);
    void SetPosition(float x, float y);
    Vector2 GetPosition() const;
    void SetRotation(float rotation);
    float GetRotation() const;

    Vector2 Calculate_BlueRobot_LeftHand_StartPosition() const;
    Vector2 Calculate_BlueRobot_RightHand_StartPosition() const;
    Vector2 Calculate_RedRobot_LeftHand_StartPosition() const;
    Vector2 Calculate_RedRobot_RightHand_StartPosition() const;
    
   
    Vector2 Calculate_LeftHand_Bullet_StartPosition() const;
    Vector2 Calculate_RightHand_Bullet_StartPosition() const;

    Vector2 Calculate_RightHand_Sonic_StartPosition() const;

    Vector2 Calculate_LeftHand_Plasma_StartPosition() const;

    Vector2 Calculate_LeftHand_Fire_StartPosition() const;
    Vector2 Calculate_RightHand_Fire_StartPosition() const;

    //Vector2 Calculate_LeftHand_Rocket_StartPosition() const;
    Vector2 Calculate_RightHand_Rocket_StartPosition() const;

    Vector2 CalculateShootingDirection() const;

    std::shared_ptr<SpriteAnimation> GetSprite() const;
    void TakeDamage(float damage);
    float GetHealth() const;
    float GetWeight() const;
    float GetRadius() const;
    float GetWidth() const;
    float GetHeight() const;
    float GetMoveSpeed(float deltaTime) const;
    void SetWeight(float weight);
    void SetRadius(float radius);
    void SetMoveSpeed(float MoveSpeed);
    void SetSize(float width, float height);
    Vector2 GetSize() const;

    std::string GetLeftHandBulletTypeFromRobot1() const;
    std::string GetRightHandBulletTypeFromRobot1() const;
    std::string GetLeftHandBulletTypeFromRobot2() const;
    std::string GetRightHandBulletTypeFromRobot2() const;

    // New methods for shooting control
    void DisableShooting();  // Disable shooting
    void EnableShooting();   // Enable shooting
    bool CanShoot() const;   // Check if the robot can shoot

    void SetDisableDuration(float duration);

private:
    std::shared_ptr<SpriteAnimation> m_sprite;
    Vector2 m_position;
    float m_rotation;
    float m_health;
    float m_weight;
    float m_radius = 45.0f;
    float m_moveSpeed = 250.0f;
    float m_width = 95.0f;
    float m_height = 70.0f;

    // New members for shooting control
    bool m_canShoot;          // Flag to control shooting ability
    float m_shootCooldown;    // Cooldown duration after being hit
    float m_timeSinceHit;     // Track time since last hit

    float m_disableDuration = 3.0f; // Time until the robot can move again
    bool m_isDisabled = false;       // Flag to check if the robot is currently disabled
};

