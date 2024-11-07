#include "BoundaryChecker.h"

BoundaryChecker::BoundaryChecker(float width, float height)
    : m_width(width), m_height(height) {}

bool BoundaryChecker::IsWithinBounds(const Vector2& position) const {
    return (position.x >= 20.0f && position.x <= m_width - 20.0f && 
            position.y >= 20.0f && position.y <= m_height - 20.0f);
}

Vector2 BoundaryChecker::ClampPosition(const Vector2& position) const {
    Vector2 clampedPosition = position;
    if (clampedPosition.x < 0) clampedPosition.x = 0;
    if (clampedPosition.x >= m_width - 95) clampedPosition.x = m_width - 95;
    if (clampedPosition.y < 0) clampedPosition.y = 0;
    if (clampedPosition.y >= m_height - 70) clampedPosition.y = m_height - 70;
    return clampedPosition;
}
