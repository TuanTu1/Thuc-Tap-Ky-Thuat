#pragma once
#include "GameStateBase.h"
#include "CMath.h"
#include "GameObject/BoundaryChecker.h"
#include "GameObject/Sound.h"
#include "Text.h"
#include "Trap.h"
#include <memory>
#include <list>
#include "Bullet.h"
#include <vector>
#include <cstdlib>   
#include "Timer.h"   
#include "Arena.h"    
#include "GSRobotSelectMenu.h"
#include <utility>

class Sprite2D;
class SpriteAnimation;
class MouseButton;
class Robot;  // Include the Robot class

struct BulletProperties {
    float fireRate;     // Fire rate in seconds
    std::string sound;  // Sound file path
};

class GSPlay : public GameStateBase
{
public:
    GSPlay();
    ~GSPlay();

    void Init() override;
    void Exit() override;

    void Pause() override;
    void Resume() override;

    void HandleEvents() override;
    void HandleSoundEvents();
    void HandleKeyEvents(SDL_Event& e) override;
    void HandleTouchEvents(SDL_Event& e) override;
    void HandleMouseMoveEvents(int x, int y) override;
    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;

    void HandleBulletCollision1(Vector2 bulletPos, Vector2 bulletDir, std::shared_ptr<Robot> targetRobot, std::shared_ptr<Bullet> bullet, std::vector<std::shared_ptr<Bullet>>::iterator& it, std::vector<std::shared_ptr<Bullet>>& bullets, float damage, float pushForce);
    void HandleBulletCollision2(Vector2 bulletPos, Vector2 bulletDir, std::shared_ptr<Robot> targetRobot, std::shared_ptr<Bullet> bullet, std::vector<std::shared_ptr<Bullet>>::iterator& it, std::vector<std::shared_ptr<Bullet>>& bullets, float damage, float pushForce);

    int m_KeyPressPlayer1;
    int m_KeyPressPlayer2;
    float m_LastRotationPlayer1;
    float m_LastRotationPlayer2;


private:
    std::shared_ptr<Sprite2D> m_HUD;
    std::shared_ptr<Sprite2D> m_healthTable1;
    std::shared_ptr<Sprite2D> m_healthTable2;
    std::shared_ptr<Sprite2D> m_tableGameResult;
    std::shared_ptr<Sprite2D> m_background;
    std::list<std::shared_ptr<MouseButton>> m_listButton;
    std::list<std::shared_ptr<Robot>> m_listRobots;
    std::shared_ptr<MouseButton> button;
    std::vector<std::shared_ptr<Bullet>> m_bullets;
    std::list<std::shared_ptr<Arena>> m_listArenas;
    std::unordered_map<std::string, BulletProperties> bulletPropertiesMap;
    std::unordered_map<std::string, float> m_timeSinceLastBullet;
    Timer m_timer;

    int m_currentArena = 1;

    BoundaryChecker m_boundaryChecker = BoundaryChecker(ARENA_WIDTH, ARENA_HEIGHT);
    std::shared_ptr<Text> m_textRobot1Health;
    std::shared_ptr<Text> m_textRobot2Health;
    std::shared_ptr<Text> m_textRobot1FullHealth;
    std::shared_ptr<Text> m_textRobot2FullHealth;
    std::shared_ptr<Text> m_textTimeLeft;
    std::shared_ptr<Text> m_textGameResult;
    std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
    SDL_Color m_textColor = { 255, 255, 255 };
    SDL_Color m_textColor1 = { 0, 162, 255 };
    SDL_Color m_textColor2 = { 210, 65, 64 };

    // Fire rate control variables
    float m_timeSinceLastNormalBulletPlayer1 = 0.0f;
    float m_timeSinceLastFireBulletPlayer1 = 0.0f;

    float m_timeSinceLastNormalBulletPlayer2 = 0.0f;
    float m_timeSinceLastFireBulletPlayer2 = 0.0f;

    float m_timeSinceRobot1Stuned = 0.0f;
    float m_timeSinceRobot2Stuned = 0.0f;

    const float NORMAL_BULLET_FIRE_RATE = 0.2f;
    const float ROCKET_BULLET_FIRE_RATE = 0.6f;
    const float FIRE_BULLET_FIRE_RATE = 0.4f;

    int m_totalBullets;

    float time = 0.5f;
    float m_Velocity = 250.0f;

    // Health bar dimensions
    float m_healthBarWidth = 165;  // Full health bar width
    float m_healthBarHeight = 30;  // Health bar height
    float m_healthBar1Width = 165; // Width of Robot1 health bar
    float m_healthBar2Width = 165; // Width of Robot2 health bar

    float m_Robot1TotalDamage = 0.0f;
    float m_Robot2TotalDamage = 0.0f;

    // Position for health bar
    Vector2 m_healthBar1Pos = Vector2(72, ARENA_HEIGHT + (HUD_HEIGHT - m_healthBarHeight) / 2 + 3);
    Vector2 m_healthBar2Pos = Vector2(SCREEN_WIDTH - 240 + 3, ARENA_HEIGHT + (HUD_HEIGHT - m_healthBarHeight) / 2 + 3);
};