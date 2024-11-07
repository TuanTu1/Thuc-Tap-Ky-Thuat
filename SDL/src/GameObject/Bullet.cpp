#include "Bullet.h"
#include "ResourceManagers.h"
#include "Define.h"
#include "Robot.h"
#include <iostream>

Bullet::Bullet(const std::string& texturePath, const Vector2& position, const Vector2& direction, float speed, float maxRange,
    int owner, int width, int height, float rotation, bool isAnimated, float animationDuration,
    std::shared_ptr<Robot> shooterRobot, int frameCount, int numAction, float frameTime, bool isAttached, bool isUsingLeftHand)
    : m_position(position), m_direction(direction), m_speed(speed), m_maxRange(maxRange),
    m_distanceTraveled(0.0f), m_owner(owner), m_rotation(rotation),
    m_isAnimated(isAnimated), m_animationDuration(animationDuration),
    m_animationTime(0.0f), m_shooterRobot(shooterRobot), m_isAttached(isAttached), m_isUsingLeftHand(isUsingLeftHand) {

    auto texture = ResourceManagers::GetInstance()->GetTexture(texturePath);
    if (texture) {
        if (m_isAnimated) {
            // Create a SpriteAnimation object for animated bullets with custom parameters
            m_animation = std::make_shared<SpriteAnimation>(texture, 1, frameCount, numAction, frameTime);  // Custom values passed
            m_animation->SetSize(width, height);
            m_animation->Set2DPosition(m_position.x, m_position.y);
            if (texturePath == "Plasma_bullet.tga") {
                m_animation->SetRotation(0.0f);
            }
            else {
                m_animation->SetRotation(m_rotation);
            }
        }
        else {
            // Create a Sprite2D object for static bullets
            m_sprite = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
            m_sprite->SetSize(width, height);
            m_sprite->Set2DPosition(m_position.x, m_position.y);
            m_sprite->SetRotation(m_rotation);
        }
    }

}

// Factory method to create a bullet (static or animated)
std::shared_ptr<Bullet> Bullet::CreateBullet(const Vector2& position, const Vector2& direction, int owner,
    float maxRange, const std::string& bulletType, float rotation,
    std::shared_ptr<Robot> shooterRobot, bool isUsingLeftHand) {

    std::string texturePath;

    // Default stats of bullet
    float speed = 1000.0f;
    int width = 50, height = 50;
    bool isAnimated = false;
    float animationDuration = 0.0f;
    int frameCount = 1;
    int numAction = 1;
    float frameTime = 0.1f;
    bool isAttached = false;

    // Determine bullet type, texture, and properties
    if (bulletType == "bullet") {
        texturePath = (owner == 1) ? "bullet_blue.tga" : "bullet_red.tga";
    }
    else if (bulletType == "rocket") {
        texturePath = "Rocket_bullet.tga";
        speed = 400.0f;
        width = 20; height = 60;
        isAnimated = false;

    }
    else if (bulletType == "fire") {
        texturePath = "Fire_bullet.tga";
        speed = 0.0f;
        width = static_cast<int>(45 * 1.5); height = static_cast<int>(90 * 1.5);
        isAnimated = true;
        animationDuration = 0.8f;
        frameCount = 14;
        numAction = 1;
        frameTime = 0.1f;
        isAttached = true;
    }
    else if (bulletType == "sonic") {
        texturePath = "Sonic_bullet.tga";
        speed = 80.0f;
        width = static_cast<int>(50); height = static_cast<int>(50);
        isAnimated = true;
        animationDuration = 0.8f;
        frameCount = 4;
        numAction = 1;
        frameTime = 0.1f;
    }
    else if (bulletType == "plasma") {
        texturePath = (owner == 1) ? "Plasma_bullet_blue.tga" : "Plasma_bullet_red.tga";
        speed = 0.0f;
        width = static_cast<int>(60 * 2); height = static_cast<int>(57 * 2);
        isAnimated = true;
        animationDuration = 4.0f;
        frameCount = 2;
        numAction = 1;
        frameTime = 0.1f;
    }
    else if (bulletType == "lightning") {
        texturePath = "Lightning_bullet.tga";
        speed = 300.0f;
        width = static_cast<int>(65); height = static_cast<int>(45);
        isAnimated = true;
        animationDuration = 3.5f;
        frameCount = 4;
        numAction = 1;
        frameTime = 0.1f;
    }

    // Create the bullet, passing animation details directly into the constructor
    std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(texturePath, position, direction, speed, maxRange, owner, width, height, rotation, isAnimated,
        animationDuration, shooterRobot, frameCount, numAction, frameTime, isAttached, isUsingLeftHand);

    bullet->SetBulletType(bulletType);

    return bullet;
}



void Bullet::Update(float deltaTime) {
    if (m_isAttached && m_shooterRobot) {
        // Follow the appropriate hand position based on whether the bullet is using the left or right hand
        if (m_isUsingLeftHand) {
            m_position = m_shooterRobot->Calculate_LeftHand_Fire_StartPosition();
            m_rotation = m_shooterRobot->GetRotation();
        }
        else {
            m_position = m_shooterRobot->Calculate_RightHand_Fire_StartPosition();
            m_rotation = m_shooterRobot->GetRotation();
        }
    }
    else {
        // Update bullet's position normally
        m_position.x += m_direction.x * m_speed * deltaTime;
        m_position.y += m_direction.y * m_speed * deltaTime;
    }

    // Update distance traveled (only for non-attached bullets)
    if (!m_isAttached) {
        m_distanceTraveled += m_speed * deltaTime;
    }

    // Update animation if bullet is animated
    if (m_isAnimated && m_animation) {
        m_animation->Set2DPosition(m_position.x, m_position.y);
        if (m_bulletType == "plasma") {
            m_animation->SetRotation(0.0f);
        }
        else {
            m_animation->SetRotation(m_rotation);
        }
        m_animation->Update(deltaTime);
        m_animationTime += deltaTime; // Update animation time
    }
    else if (m_sprite) {
        m_sprite->Set2DPosition(m_position.x, m_position.y);
        m_sprite->SetRotation(m_rotation);
    }
}




bool Bullet::HasAnimationCompleted() const {
    return m_isAnimated && (m_animationTime >= m_animationDuration);
}

void Bullet::Draw(SDL_Renderer* renderer) {
    if (m_isAnimated && m_animation) {
        m_animation->Draw(renderer);
    }
    else if (m_sprite) {
        m_sprite->Draw(renderer);
    }
}

bool Bullet::IsOffScreen() const {
    return m_position.x < 0 || m_position.x > ARENA_WIDTH || m_position.y < 0 || m_position.y > ARENA_HEIGHT;
}

bool Bullet::HasExceededMaxRange() const {
    return m_distanceTraveled >= m_maxRange;
}

Vector2 Bullet::GetPosition() const {
    return m_position;
}

std::shared_ptr<Sprite2D> Bullet::GetSprite() const {
    return m_sprite;
}

std::shared_ptr<SpriteAnimation> Bullet::GetAnimation() const {
    return m_animation;
}

int Bullet::GetWidth() const {
    if (m_isAnimated && m_animation) {
        return m_animation->GetWidth();  // Assuming your SpriteAnimation class has a method to get width
    }
    else if (m_sprite) {
        return m_sprite->GetWidth();  // Assuming your Sprite2D class has a method to get width
    }
    return 0; // Default case if neither is valid
}

int Bullet::GetHeight() const {
    if (m_isAnimated && m_animation) {
        return m_animation->GetHeight();  // Assuming your SpriteAnimation class has a method to get height
    }
    else if (m_sprite) {
        return m_sprite->GetHeight();  // Assuming your Sprite2D class has a method to get height
    }
    return 0; // Default case if neither is valid
}

void Bullet::SetBulletType(const std::string& bulletType) {
    m_bulletType = bulletType;
}

std::string Bullet::GetBulletType() {
    return m_bulletType;
}