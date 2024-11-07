#pragma once
#include <vector>
#include <memory>
#include "Trap.h"
#include "Define.h"
#include "Robot.h"
#include "CollisionHandler.h"
#include "BoundaryChecker.h"
#include "ResourceManagers.h"
#include "Timer.h"
#include "Sprite2D.h"
#include "BulletManager.h"
#include <list>
#include "Sound.h"


class Arena {
public:
    Arena();
    ~Arena();

    void LoadTextures();
    void InitializeArena1();
    void InitializeArena2();
    void InitializeArena3();
    std::vector<std::shared_ptr<Trap>> GetTraps() const;
    void Draw(SDL_Renderer* renderer);
    void CheckCollisionsWithSaw(std::shared_ptr<Robot> robot, float deltaTime);
    void CheckCollisionsWithLightning(std::shared_ptr<Robot> robot, float deltaTime);
    void CheckCollisionsWithLightningBullet1(std::shared_ptr<Robot> robot, float deltaTime);
    void CheckCollisionsWithLightningBullet2(std::shared_ptr<Robot> robot, float deltaTime);

    void InitializeRandomArena();
    int GetCurrentArena();
    int m_currentArena = 1;
    void Update(float deltaTime, const std::list<std::shared_ptr<Robot>>&m_listRobots);
    void FireFromElectricCanon();  // Updated this name

    bool robot1IsStuned();
    bool robot2IsStuned();
    void robot1StunedEnd();
    void robot2StunedEnd();

    BulletManager& GetBulletManager();

    std::vector<std::shared_ptr<Bullet>>& Arena::GetArena3ActiveBullets() {
        return m_activeBullets;
    }


private:
    std::vector<std::shared_ptr<Trap>> m_listTraps;  // Trap list for the arena
    BoundaryChecker m_boundaryChecker = BoundaryChecker(ARENA_WIDTH, ARENA_HEIGHT);
    std::unique_ptr<BulletManager> m_bulletManager;  // Use unique_ptr for managing bullets

    float m_shootingInterval;       // Time interval between shots
    float m_timeSinceLastShot;      // Time since the last bullet was fired

    std::vector<std::shared_ptr<Bullet>> m_activeBullets;

    bool m_robot1stuned = false;
    bool m_robot2stuned = false;
};
