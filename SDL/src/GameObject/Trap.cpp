#include "Trap.h"

Trap::Trap(std::shared_ptr<TextureManager> texture, int frameCount, int numAction, float frameTime, float x, float y)
    : m_width(0), m_height(0), m_rotation(0) // Initialize m_rotation here
{
    m_animation = std::make_shared<SpriteAnimation>(texture, 1, frameCount, numAction, frameTime);
    m_animation->Set2DPosition(x, y);
}

Trap::~Trap()
{
}

void Trap::Update(float deltaTime)
{
    m_animation->Update(deltaTime);
}

void Trap::Draw(SDL_Renderer* renderer)
{
    // Here we can utilize m_width and m_height to define the size for drawing
    Vector2 position = GetPosition();
    m_animation->SetSize(m_width, m_height);
    m_animation->Draw(renderer);
}

Vector2 Trap::GetPosition() const
{
    return m_animation->Get2DPosition();
}

void Trap::SetPosition(float x, float y)
{
    m_animation->Set2DPosition(x, y);
}

void Trap::SetSize(float width, float height) {
    m_width = width;
    m_height = height;
}

Vector2 Trap::GetSize() const {
    return Vector2(m_width, m_height);
}

float Trap::GetWidth() const {
    return m_width;
}

float Trap::GetHeight() const {
    return m_height;
}

int Trap::GetCurrentFrame() {
    return m_animation->GetCurrentFrame();
}

void Trap::SetRotation(float rotation)
{
    m_rotation = rotation; // Set the rotation value
    m_animation->SetRotation(rotation); // Update animation rotation if necessary
}

float Trap::GetRotation() const
{
    return m_rotation; // Return the rotation value
}
