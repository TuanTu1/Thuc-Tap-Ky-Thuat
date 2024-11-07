#pragma once
// BulletManager.h
#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include <vector>
#include <memory>
#include "Bullet.h"

class BulletManager {
public:
    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);
    std::shared_ptr<Bullet> FireBullet(const Vector2& position, const Vector2& direction, int owner, float maxRange);
    std::vector<std::shared_ptr<Bullet>> GetBullets() const;

private:
    std::vector<std::shared_ptr<Bullet>> m_bullets;
};

#endif // BULLET_MANAGER_H
