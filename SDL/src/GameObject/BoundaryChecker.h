     #pragma once
#include "CMath.h" 

class BoundaryChecker {
public:
    BoundaryChecker(float width, float height);
    bool IsWithinBounds(const Vector2& position) const;
    Vector2 ClampPosition(const Vector2& position) const;

private:
    float m_width;
    float m_height;
};

