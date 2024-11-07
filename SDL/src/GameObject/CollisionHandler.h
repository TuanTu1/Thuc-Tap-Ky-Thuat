#pragma once
#include <SDL.h>
#include <memory>
#include "Robot.h"
#include "GameObject/SpriteAnimation.h"  // Include your SpriteAnimation class

class CollisionHandler {
public:
    // Check if two circles (robots) are colliding
    static bool CheckCircleCollision(const Vector2& center1, float radius1, const Vector2& center2, float radius2);

    // Resolve the collision between two SpriteAnimation objects with weight and circle hitboxes
    static void ResolveCircleCollision(std::shared_ptr<Robot>& robot1, float radius1, float weight1,
        std::shared_ptr<Robot>& robot2, float radius2, float weight2);
    
    // Check if robots & traps are colliding
    static bool CollisionHandler::CheckCircleCollisionForTrap(std::shared_ptr<Robot>& robot1, float radius1, const Vector2& center2, float radius2);
   
    // Check if robots & traps are colliding
    static bool CollisionHandler::CheckRectangleCollisionForLightning(const Vector2& robotPos, float robotWidth, float robotHeight,
        const Vector2& trapPos, float trapWidth, float trapHeight);

    static bool CheckRectangleCollision(const Vector2& objectPos, float objectWidth, float objectHeight,
        const Vector2& targetPos, float targetWidth, float targetHeight);
};
