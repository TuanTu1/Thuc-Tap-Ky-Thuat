#include "BulletManager.h"

void BulletManager::Update(float deltaTime) {
    for (auto it = m_bullets.begin(); it != m_bullets.end();) {
        (*it)->Update(deltaTime);

        // Check if bullet has exceeded its max range or is off-screen
        if ((*it)->HasExceededMaxRange() || (*it)->IsOffScreen()) {
            it = m_bullets.erase(it);  // Remove bullet from list if it's out of bounds
        }
        else {
            ++it;
        }
    }
}

void BulletManager::Draw(SDL_Renderer* renderer) {
    for (const auto& bullet : m_bullets) {
        bullet->Draw(renderer);
    }
}

std::shared_ptr<Bullet> BulletManager::FireBullet(const Vector2& position, const Vector2& direction, int owner, float maxRange) {
    auto bullet = Bullet::CreateBullet(position, direction, owner, maxRange, "lightning", 0.5f);
    m_bullets.push_back(bullet);
    return bullet;
}


std::vector<std::shared_ptr<Bullet>> BulletManager::GetBullets() const {
    return m_bullets;
}
