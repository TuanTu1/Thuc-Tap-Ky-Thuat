#include "CollisionHandler.h"
#include <cmath>

bool CollisionHandler::CheckCircleCollision(const Vector2& center1, float radius1, const Vector2& center2, float radius2)
{
    // Calculate the distance between the centers of the two circles
    float dx = center1.x - center2.x;
    float dy = center1.y - center2.y;
    float distance = sqrt(dx * dx + dy * dy);

    // Check if the distance is less than the sum of the radii
    return distance < (radius1 + radius2);
}

void CollisionHandler::ResolveCircleCollision(std::shared_ptr<Robot>& robot1, float radius1, float weight1,
    std::shared_ptr<Robot>& robot2, float radius2, float weight2)
{
    // Get robots' positions (centers of their circles)
    Vector2 pos1 = robot1->GetPosition();
    Vector2 pos2 = robot2->GetPosition();

    // Calculate the distance between the two robots
    float dx = pos1.x - pos2.x;
    float dy = pos1.y - pos2.y;
    float distance = sqrt(dx * dx + dy * dy);

    // If collision detected
    float combinedRadius = radius1 + radius2;
    
    if (distance < combinedRadius)
    {
        // Penetration depth (how much the circles overlap)
        float penetrationDepth = combinedRadius - distance;
        
        // Calculate the total weight and influence ratio
        float totalWeight = weight1 + weight2;
        float weightRatio1 = weight1 / totalWeight;
        float weightRatio2 = weight2 / totalWeight;
       
        // Normalize the direction vector (dx, dy)
        dx /= distance;
        dy /= distance;

        // Adjust the separation force based on penetration depth
        float separationForce = penetrationDepth * 5.0f; // Factor to fine-tune the push

        // Only push them apart significantly when there's deep penetration
        if (penetrationDepth > 1.0f)  // Edge threshold for sliding
        {
            // Push 1 away from 2 
            pos1.x += separationForce * weightRatio2 * dx;
            pos1.y += separationForce * weightRatio2 * dy;
            robot1->SetPosition(pos1.x, pos1.y);

            // Push 2 away from 1
            pos2.x -= separationForce * weightRatio1 * dx;
            pos2.y -= separationForce * weightRatio1 * dy;
            robot2->SetPosition(pos2.x, pos2.y);
        }
    }
}

bool CollisionHandler::CheckCircleCollisionForTrap(std::shared_ptr<Robot>& robot1, float radius1, const Vector2& center2, float radius2)
{
    // Get robots' positions (centers of their circles)
    Vector2 pos1 = robot1->GetPosition();
    Vector2 pos2 = center2;

    // Calculate the distance between the two robots
    float dx = pos1.x - pos2.x;
    float dy = pos1.y - pos2.y;
    float distance = sqrt(dx * dx + dy * dy);

    // If collision detected
    float combinedRadius = radius1 + radius2;

    if (distance < combinedRadius)
    {
        // Penetration depth (how much the circles overlap)
        float penetrationDepth = combinedRadius - distance;

        // Normalize the direction vector (dx, dy)
        dx /= distance;
        dy /= distance;

        // Adjust the separation force based on penetration depth
        float separationForce = penetrationDepth * 2.0f; // Factor to fine-tune the push

        // Only push them apart significantly when there's deep penetration
        if (penetrationDepth > 10.0f)  // Edge threshold for sliding
        {
            // Push 1 away from 2 
            pos1.x += separationForce * dx;
            pos1.y += separationForce * dy;
            robot1->SetPosition(pos1.x, pos1.y);
            return true;
        }
    }
    // Check if the distance is less than the sum of the radii
    return distance < (radius1 + radius2);
}

bool CollisionHandler::CheckRectangleCollisionForLightning(const Vector2& robotPos, float robotWidth, float robotHeight,
    const Vector2& trapPos, float trapWidth, float trapHeight)
{
    // Calculate the boundaries for the middle quarter of the trap's width
    float quarterWidth = trapWidth / 4.0f; // Width of one quarter
    float middleStartX = trapPos.x + (trapWidth / 2.0f) - (quarterWidth / 2.0f); // Start of the middle quarter
    float middleEndX = middleStartX + quarterWidth; // End of the middle quarter

    // Check for overlaps
    bool overlapX = robotPos.x < middleEndX && robotPos.x + robotWidth > middleStartX;
    bool overlapY = robotPos.y < trapPos.y + trapHeight && robotPos.y + robotHeight > trapPos.y;

    return overlapX && overlapY;
}

bool CollisionHandler::CheckRectangleCollision(const Vector2& objectPos, float objectWidth, float objectHeight,
    const Vector2& targetPos, float targetWidth, float targetHeight)
{
    // Calculate the boundaries of the object and the target
    float objectLeft = objectPos.x;
    float objectRight = objectPos.x + objectWidth;
    float objectTop = objectPos.y;
    float objectBottom = objectPos.y + objectHeight;

    float targetLeft = targetPos.x;
    float targetRight = targetPos.x + targetWidth;
    float targetTop = targetPos.y;
    float targetBottom = targetPos.y + targetHeight;

    // Check for overlap
    return (objectLeft < targetRight && objectRight > targetLeft &&
        objectTop < targetBottom && objectBottom > targetTop);
}
