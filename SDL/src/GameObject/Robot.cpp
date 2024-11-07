#include "Robot.h"
#include "ResourceManagers.h"
#include "Bullet.h"
#include "SelectedRobotManager.h"


// Constructor: Initializes the robot with a texture, position, rotation, and size
Robot::Robot(const std::string& texturePath, const Vector2& position, float rotation, float weight)
    : m_position(position), m_rotation(rotation), m_health(1000.0f), m_weight(weight),
    m_canShoot(true), m_shootCooldown(1.0f), m_timeSinceHit(0.0f) {  // Initialize shooting-related members
    auto texture = ResourceManagers::GetInstance()->GetTexture(texturePath);
    m_sprite = std::make_shared<SpriteAnimation>(texture, 1, 1, 1, 0.2f);
    m_sprite->SetSize(m_width, m_height);
    m_sprite->Set2DPosition(position.x, position.y);
    m_sprite->SetRotation(rotation);
}

// Destructor
Robot::~Robot() {}

// Update the sprite animation and manage shooting cooldown
void Robot::Update(float deltaTime) {
    m_sprite->Update(deltaTime);

    if (m_isDisabled) {
        m_disableDuration -= deltaTime;  // Decrease the duration
        if (m_disableDuration <= 0.0f) {
            m_isDisabled = false;         // Reset the disabled state
            // Reset to original speed, you might want to store the original speed
            SetMoveSpeed( 250.0f); // Reset to the original speed
        }
    }   

    // Manage the cooldown for shooting
    if (!m_canShoot) {
        m_timeSinceHit += deltaTime; // Increment the timer
        if (m_timeSinceHit >= m_shootCooldown) {
            EnableShooting(); // Re-enable shooting after cooldown
        }
    }
}               

// Set the position of the robot
void Robot::SetPosition(float x, float y) {
    m_position.x = x;
    m_position.y = y;
    m_sprite->Set2DPosition(x, y);
}

// Get the current position of the robot
Vector2 Robot::GetPosition() const {
    return m_position;
}

// Set the rotation of the robot
void Robot::SetRotation(float rotation) {
    m_rotation = rotation;
    m_sprite->SetRotation(rotation);
}

// Get the current rotation of the robot
float Robot::GetRotation() const {
    return m_rotation;
}


// Get the sprite associated with the robot
std::shared_ptr<SpriteAnimation> Robot::GetSprite() const {
    return m_sprite;
}

void Robot::TakeDamage(float damage) {
    m_health -= damage;
    if (m_health < 0) m_health = 0;
}

float Robot::GetHealth() const {
    return m_health;
}

float Robot::GetWeight() const {
    return m_weight;
}
void Robot::SetWeight(float weight) {
    m_weight = weight;
}

float Robot::GetRadius() const {
    return m_radius;
}
void Robot::SetRadius(float radius) {
    m_radius = radius;
}

float Robot::GetMoveSpeed(float deltaTime) const {
    return m_moveSpeed * deltaTime;
}

void Robot::SetMoveSpeed(float MoveSpeed) {
    m_moveSpeed = MoveSpeed;
}

std::string Robot::GetLeftHandBulletTypeFromRobot1() const {
    std::string selectedRobotTexture = SelectedRobotManager::GetSelectedRobot1Texture();

    // Determine bullet type based on the selected robot texture
    if (selectedRobotTexture == "robot_bullet_bullet_blue.tga") {
        return "bullet";
    }
    else if (selectedRobotTexture == "robot_bullet_sonic_blue.tga") {
        return "bullet";
    }
    else if (selectedRobotTexture == "robot_fire_fire_blue.tga") {
        return "fire";
    }
    else if (selectedRobotTexture == "robot_plasma_rocket_blue.tga") {
        return "plasma";
    }
    else if (selectedRobotTexture == "robot_plasma_sonic_blue.tga") {
        return "plasma";
    }
    else if (selectedRobotTexture == "robot_fire_rocket_blue.tga") {
        return "fire";
    }

    // Default to normal bullet type if no matching texture is found
    return "bullet";
}

std::string Robot::GetRightHandBulletTypeFromRobot1() const {
    std::string selectedRobotTexture = SelectedRobotManager::GetSelectedRobot1Texture();

    // Determine bullet type based on the selected robot texture
    if (selectedRobotTexture == "robot_bullet_bullet_blue.tga") {
        return "bullet";
    }
    else if (selectedRobotTexture == "robot_bullet_sonic_blue.tga") {
        return "sonic";
    }
    else if (selectedRobotTexture == "robot_fire_fire_blue.tga") {
        return "fire";
    }
    else if (selectedRobotTexture == "robot_plasma_rocket_blue.tga") {
        return "rocket";
    }
    else if (selectedRobotTexture == "robot_plasma_sonic_blue.tga") {
        return "sonic";
    }
    else if (selectedRobotTexture == "robot_fire_rocket_blue.tga") {
        return "rocket";
    }

    // Default to normal bullet type if no matching texture is found
    return "bullet";
}

std::string Robot::GetLeftHandBulletTypeFromRobot2() const {
    std::string selectedRobotTexture = SelectedRobotManager::GetSelectedRobot2Texture();

    // Determine bullet type based on the selected robot texture
    if (selectedRobotTexture == "robot_bullet_bullet_red.tga") {
        return "bullet";
    }
    else if (selectedRobotTexture == "robot_bullet_sonic_red.tga") {
        return "bullet";
    }
    else if (selectedRobotTexture == "robot_fire_fire_red.tga") {
        return "fire";
    }
    else if (selectedRobotTexture == "robot_plasma_rocket_red.tga") {
        return "plasma";
    }
    else if (selectedRobotTexture == "robot_plasma_sonic_red.tga") {
        return "plasma";
    }
    else if (selectedRobotTexture == "robot_fire_rocket_red.tga") {
        return "fire";
    }

    // Default to normal bullet type if no matching texture is found
    return "bullet";
}

std::string Robot::GetRightHandBulletTypeFromRobot2() const {
    std::string selectedRobotTexture = SelectedRobotManager::GetSelectedRobot2Texture();

    // Determine bullet type based on the selected robot texture
    if (selectedRobotTexture == "robot_bullet_bullet_red.tga") {
        return "bullet";
    }
    else if (selectedRobotTexture == "robot_bullet_sonic_red.tga") {
        return "sonic";
    }
    else if (selectedRobotTexture == "robot_fire_fire_red.tga") {
        return "fire";
    }
    else if (selectedRobotTexture == "robot_plasma_rocket_red.tga") {
        return "rocket";
    }
    else if (selectedRobotTexture == "robot_plasma_sonic_red.tga") {
        return "sonic";
    }
    else if (selectedRobotTexture == "robot_fire_rocket_red.tga") {
        return "rocket";
    }

    // Default to normal bullet type if no matching texture is found
    return "bullet";
}
// Shooting control methods
void Robot::DisableShooting() {
    m_canShoot = false;
    m_timeSinceHit = 0.0f; // Reset the timer when shooting is disabled
}

void Robot::EnableShooting() {
    m_canShoot = true;
}

bool Robot::CanShoot() const {
    return m_canShoot;
}

void Robot::SetDisableDuration(float duration) {
    m_disableDuration = duration;
    m_isDisabled = true; // Set the robot to be disabled
    SetMoveSpeed(0.0f);  // Optionally, set speed to 0 immediately
}


Vector2 Robot::Calculate_LeftHand_Bullet_StartPosition() const {
    float handOffsetX = 0.0f;
    float handOffsetY = 0.0f;
    float rotation = m_rotation;

    // Normalize the rotation to be within the range [0, 360)
    if (rotation < 0) {
        rotation += 360.0f;
    }

    // Adjust offsets based on robot's rotation
    if (rotation >= 337.5f || rotation < 22.5f) { // Up
        handOffsetX = -10.0f;
        handOffsetY = -40.0f;
    }
    else if (rotation >= 22.5f && rotation < 67.5f) { // Up-Right
        handOffsetX = 30.0f;
        handOffsetY = -40.0f;
    }
    else if (rotation >= 67.5f && rotation < 112.5f) { // Right
        handOffsetX = 70.0f;
        handOffsetY = -20.0f;
    }
    else if (rotation >= 112.5f && rotation < 157.5f) { // Down-Right
        handOffsetX = 80.0f;
        handOffsetY = 30.0f;
    }
    else if (rotation >= 157.5f && rotation < 202.5f) { // Down
        handOffsetX = 55.0f;
        handOffsetY = 70.0f;
    }
    else if (rotation >= 202.5f && rotation < 247.5f) { // Down-Left
        handOffsetX = 20.0f;
        handOffsetY = 70.0f;
    }
    else if (rotation >= 247.5f && rotation < 292.5f) { // Left
        handOffsetX = -30.0f;
        handOffsetY = 45.0f;
    }
    else if (rotation >= 292.5f && rotation < 337.5f) { // Up-Left
        handOffsetX = -30.0f;
        handOffsetY = 0.0f;
    }

    // Manually add the position and offset vectors
    return Vector2(m_position.x + handOffsetX, m_position.y + handOffsetY);
}

Vector2 Robot::Calculate_RightHand_Bullet_StartPosition() const {
    float handOffsetX = 0.0f;
    float handOffsetY = 0.0f;
    float rotation = m_rotation;

    // Normalize the rotation to be within the range [0, 360)
    if (rotation < 0) {
        rotation += 360.0f;
    }

    // Adjust offsets based on robot's rotation
    if (rotation >= 337.5f || rotation < 22.5f) { // Up
        handOffsetX = 55.0f;
        handOffsetY = -40.0f;
    }
    else if (rotation >= 22.5f && rotation < 67.5f) { // Up-Right
        handOffsetX = 80.0f;
        handOffsetY = 5.0f;
    }
    else if (rotation >= 67.5f && rotation < 112.5f) { // Right
        handOffsetX = 70.0f;
        handOffsetY = 40.0f;
    }
    else if (rotation >= 112.5f && rotation < 157.5f) { // Down-Right
        handOffsetX = 20.0f;
        handOffsetY = 60.0f;
    }
    else if (rotation >= 157.5f && rotation < 202.5f) { // Down
        handOffsetX = -10.0f;
        handOffsetY = 70.0f;
    }
    else if (rotation >= 202.5f && rotation < 247.5f) { // Down-Left
        handOffsetX = -40.0f;
        handOffsetY = 20.0f;
    }
    else if (rotation >= 247.5f && rotation < 292.5f) { // Left
        handOffsetX = -30.0f;
        handOffsetY = -25.0f;
    }
    else if (rotation >= 292.5f && rotation < 337.5f) { // Up-Left
        handOffsetX = 40.0f;
        handOffsetY = -20.0f;
    }

    // Manually add the position and offset vectors
    return Vector2(m_position.x + handOffsetX, m_position.y + handOffsetY);
}

Vector2 Robot::Calculate_RightHand_Sonic_StartPosition() const {
    float handOffsetX = 0.0f;
    float handOffsetY = 0.0f;
    float rotation = m_rotation;

    // Normalize the rotation to be within the range [0, 360)
    if (rotation < 0) {
        rotation += 360.0f;
    }

    // Adjust offsets based on robot's rotation
    if (rotation >= 337.5f || rotation < 22.5f) { // Up
        handOffsetX = 55.0f;
        handOffsetY = -40.0f;
    }
    else if (rotation >= 22.5f && rotation < 67.5f) { // Up-Right
        handOffsetX = 90.0f;
        handOffsetY = -10.0f;
    }
    else if (rotation >= 67.5f && rotation < 112.5f) { // Right
        handOffsetX = 80.0f;
        handOffsetY = 45.0f;
    }
    else if (rotation >= 112.5f && rotation < 157.5f) { // Down-Right
        handOffsetX = 40.0f;
        handOffsetY = 80.0f;
    }
    else if (rotation >= 157.5f && rotation < 202.5f) { // Down
        handOffsetX = -10.0f;
        handOffsetY = 70.0f;
    }
    else if (rotation >= 202.5f && rotation < 247.5f) { // Down-Left
        handOffsetX = -50.0f;
        handOffsetY = 30.0f;
    }
    else if (rotation >= 247.5f && rotation < 292.5f) { // Left
        handOffsetX = -35.0f;
        handOffsetY = -20.0f;
    }
    else if (rotation >= 292.5f && rotation < 337.5f) { // Up-Left
        handOffsetX = -10.0f;
        handOffsetY = -60.0f;
    }

    // Manually add the position and offset vectors
    return Vector2(m_position.x + handOffsetX, m_position.y + handOffsetY);
}

Vector2 Robot::Calculate_LeftHand_Plasma_StartPosition() const {
    float handOffsetX = 0.0f;
    float handOffsetY = 0.0f;
    float rotation = m_rotation;

    // Normalize the rotation to be within the range [0, 360)
    if (rotation < 0) {
        rotation += 360.0f;
    }

    // Adjust offsets based on robot's rotation
    if (rotation >= 337.5f || rotation < 22.5f) { // Up
        handOffsetX = -50.0f;
        handOffsetY = -80.0f;
    }
    else if (rotation >= 22.5f && rotation < 67.5f) { // Up-Right
        handOffsetX = 0.0f;
        handOffsetY = -90.0f;
    }
    else if (rotation >= 67.5f && rotation < 112.5f) { // Right
        handOffsetX = 50.0f;
        handOffsetY = -50.0f;
    }
    else if (rotation >= 112.5f && rotation < 157.5f) { // Down-Right
        handOffsetX = 40.0f;
        handOffsetY = -20.0f;
    }
    else if (rotation >= 157.5f && rotation < 202.5f) { // Down
        handOffsetX = 20.0f;
        handOffsetY = 40.0f;
    }
    else if (rotation >= 202.5f && rotation < 247.5f) { // Down-Left
        handOffsetX = -20.0f;
        handOffsetY = 40.0f;
    }
    else if (rotation >= 247.5f && rotation < 292.5f) { // Left
        handOffsetX = -70.0f;
        handOffsetY = 20.0f;
    }
    else if (rotation >= 292.5f && rotation < 337.5f) { // Up-Left
        handOffsetX = -80.0f;
        handOffsetY = -40.0f;
    }

    // Manually add the position and offset vectors
    return Vector2(m_position.x + handOffsetX, m_position.y + handOffsetY);
}

Vector2 Robot::Calculate_LeftHand_Fire_StartPosition() const {
    float handOffsetX = 0.0f;
    float handOffsetY = 0.0f;
    float rotation = m_rotation;

    // Normalize the rotation to be within the range [0, 360)
    if (rotation < 0) {
        rotation += 360.0f;
    }

    // Adjust offsets based on robot's rotation for the right hand
    if (rotation >= 337.5f || rotation < 22.5f) { // Up
        handOffsetX = -20.0f;  // Adjusted to the right
        handOffsetY = -120.0f;
    }
    else if (rotation >= 22.5f && rotation < 67.5f) { // Up-Right
        handOffsetX = 60.0f;  // Adjusted to the right
        handOffsetY = -120.0f;
    }
    else if (rotation >= 67.5f && rotation < 112.5f) { // Right
        handOffsetX = 105.0f;  // No change needed
        handOffsetY = -65.0f;
    }
    else if (rotation >= 112.5f && rotation < 157.5f) { // Down-Right
        handOffsetX = 100.0f;  // No change needed
        handOffsetY = 10.0f;
    }
    else if (rotation >= 157.5f && rotation < 202.5f) { // Down
        handOffsetX = 45.0f;  // Adjusted to the right
        handOffsetY = 60.0f;
    }
    else if (rotation >= 202.5f && rotation < 247.5f) { // Down-Left
        handOffsetX = -35.0f;  // Adjusted to the right
        handOffsetY = 55.0f;
    }
    else if (rotation >= 247.5f && rotation < 292.5f) { // Left
        handOffsetX = -75.0f; // Adjusted to the right
        handOffsetY = 0.0f;
    }
    else if (rotation >= 292.5f && rotation < 337.5f) { // Up-Left
        handOffsetX = -70.0f; // Adjusted to the right
        handOffsetY = -70.0f;
    }

    // Manually add the position and offset vectors for the right hand
    return Vector2(m_position.x + handOffsetX, m_position.y + handOffsetY);
}

Vector2 Robot::Calculate_RightHand_Fire_StartPosition() const {
    float handOffsetX = 0.0f;
    float handOffsetY = 0.0f;
    float rotation = m_rotation;

    // Normalize the rotation to be within the range [0, 360)
    if (rotation < 0) {
        rotation += 360.0f;
    }

    // Adjust offsets based on robot's rotation for the right hand
    if (rotation >= 337.5f || rotation < 22.5f) { // Up
        handOffsetX = 45.0f;  // Adjusted to the right
        handOffsetY = -120.0f;
    }
    else if (rotation >= 22.5f && rotation < 67.5f) { // Up-Right
        handOffsetX = 100.0f;  // Adjusted to the right
        handOffsetY = -70.0f;
    }
    else if (rotation >= 67.5f && rotation < 112.5f) { // Right
        handOffsetX = 105.0f;  // No change needed
        handOffsetY = 0.0f;
    }
    else if (rotation >= 112.5f && rotation < 157.5f) { // Down-Right
        handOffsetX = 50.0f;  // No change needed
        handOffsetY = 50.0f;
    }
    else if (rotation >= 157.5f && rotation < 202.5f) { // Down
        handOffsetX = -20.0f;  // Adjusted to the right
        handOffsetY = 60.0f;
    }
    else if (rotation >= 202.5f && rotation < 247.5f) { // Down-Left
        handOffsetX = -75.0f;  // Adjusted to the right
        handOffsetY = 15.0f;
    }
    else if (rotation >= 247.5f && rotation < 292.5f) { // Left
        handOffsetX = -75.0f; // Adjusted to the right
        handOffsetY = -60.0f;
    }
    else if (rotation >= 292.5f && rotation < 337.5f) { // Up-Left
        handOffsetX = -30.0f; // Adjusted to the right
        handOffsetY = -120.0f;
    }

    // Manually add the position and offset vectors for the right hand
    return Vector2(m_position.x + handOffsetX, m_position.y + handOffsetY);
}

/*Vector2 Robot::Calculate_LeftHand_Rocket_StartPosition() const {
    float handOffsetX = 0.0f;
    float handOffsetY = 0.0f;
    float rotation = m_rotation;

    // Normalize the rotation to be within the range [0, 360)
    if (rotation < 0) {
        rotation += 360.0f;
    }

    // Adjust offsets based on robot's rotation for the right hand
    if (rotation >= 337.5f || rotation < 22.5f) { // Up
        handOffsetX = 70.0f;  // Adjusted to the right
        handOffsetY = -50.0f;
    }
    else if (rotation >= 22.5f && rotation < 67.5f) { // Up-Right
        handOffsetX = 100.0f;  // Adjusted to the right
        handOffsetY = -10.0f;
    }
    else if (rotation >= 67.5f && rotation < 112.5f) { // Right
        handOffsetX = 105.0f;  // No change needed
        handOffsetY = 30.0f;
    }
    else if (rotation >= 112.5f && rotation < 157.5f) { // Down-Right
        handOffsetX = 50.0f;  // No change needed
        handOffsetY = 50.0f;
    }
    else if (rotation >= 157.5f && rotation < 202.5f) { // Down
        handOffsetX = 0.0f;  // Adjusted to the right
        handOffsetY = 60.0f;
    }
    else if (rotation >= 202.5f && rotation < 247.5f) { // Down-Left
        handOffsetX = -40.0f;  // Adjusted to the right
        handOffsetY = 40.0f;
    }
    else if (rotation >= 247.5f && rotation < 292.5f) { // Left
        handOffsetX = -30.0f; // Adjusted to the right
        handOffsetY = -30.0f;
    }
    else if (rotation >= 292.5f && rotation < 337.5f) { // Up-Left
        handOffsetX = 40.0f; // Adjusted to the right
        handOffsetY = -40.0f;
    }

    // Manually add the position and offset vectors for the right hand
    return Vector2(m_position.x + handOffsetX, m_position.y + handOffsetY);
}*/

Vector2 Robot::Calculate_RightHand_Rocket_StartPosition() const {
    float handOffsetX = 0.0f;
    float handOffsetY = 0.0f;
    float rotation = m_rotation;

    // Normalize the rotation to be within the range [0, 360)
    if (rotation < 0) {
        rotation += 360.0f;
    }

    // Adjust offsets based on robot's rotation for the right hand
    if (rotation >= 337.5f || rotation < 22.5f) { // Up
        handOffsetX = 70.0f;  // Adjusted to the right
        handOffsetY = -50.0f;
    }
    else if (rotation >= 22.5f && rotation < 67.5f) { // Up-Right
        handOffsetX = 100.0f;  // Adjusted to the right
        handOffsetY = -10.0f;
    }
    else if (rotation >= 67.5f && rotation < 112.5f) { // Right
        handOffsetX = 105.0f;  // No change needed
        handOffsetY = 35.0f;
    }
    else if (rotation >= 112.5f && rotation < 157.5f) { // Down-Right
        handOffsetX = 55.0f;  // No change needed
        handOffsetY = 65.0f;
    }
    else if (rotation >= 157.5f && rotation < 202.5f) { // Down
        handOffsetX = 5.0f;  // Adjusted to the right
        handOffsetY = 60.0f;
    }
    else if (rotation >= 202.5f && rotation < 247.5f) { // Down-Left
        handOffsetX = -40.0f;  // Adjusted to the right
        handOffsetY = 40.0f;
    }
    else if (rotation >= 247.5f && rotation < 292.5f) { // Left
        handOffsetX = -30.0f; // Adjusted to the right
        handOffsetY = -30.0f;
    }
    else if (rotation >= 292.5f && rotation < 337.5f) { // Up-Left
        handOffsetX = 35.0f; // Adjusted to the right
        handOffsetY = -45.0f;
    }

    // Manually add the position and offset vectors for the right hand
    return Vector2(m_position.x + handOffsetX, m_position.y + handOffsetY);
}

Vector2 Robot::Calculate_BlueRobot_LeftHand_StartPosition() const {
    std::string selectedRobotTexture = SelectedRobotManager::GetSelectedRobot1Texture(); 

    // Determine which robot texture is selected and choose the appropriate offset calculation method
    if (selectedRobotTexture == "robot_bullet_bullet_blue.tga") {
        return Calculate_LeftHand_Bullet_StartPosition();
    }
    else if (selectedRobotTexture == "robot_bullet_sonic_blue.tga") {
        return Calculate_LeftHand_Bullet_StartPosition();
    }
    else if (selectedRobotTexture == "robot_fire_fire_blue.tga") {
        return Calculate_LeftHand_Fire_StartPosition();
    }
    else if (selectedRobotTexture == "robot_plasma_rocket_blue.tga") {
        return Calculate_LeftHand_Plasma_StartPosition();
    }
    else if (selectedRobotTexture == "robot_plasma_sonic_blue.tga") {
        return Calculate_LeftHand_Plasma_StartPosition();
    }
    else if (selectedRobotTexture == "robot_fire_rocket_blue.tga") {
        return Calculate_LeftHand_Fire_StartPosition();
    }

    // Default to zero offset if no matching robot is found
    return Vector2(m_position.x, m_position.y);
}

Vector2 Robot::Calculate_BlueRobot_RightHand_StartPosition() const {
    std::string selectedRobotTexture = SelectedRobotManager::GetSelectedRobot1Texture();

    // Determine which robot texture is selected and choose the appropriate offset calculation method
    if (selectedRobotTexture == "robot_bullet_bullet_blue.tga") {
        return Calculate_RightHand_Bullet_StartPosition();
    }
    else if (selectedRobotTexture == "robot_bullet_sonic_blue.tga") {
        return Calculate_RightHand_Sonic_StartPosition();
    }
    else if (selectedRobotTexture == "robot_fire_fire_blue.tga") {
        return Calculate_RightHand_Fire_StartPosition();
    }
    else if (selectedRobotTexture == "robot_plasma_rocket_blue.tga") {
        return Calculate_RightHand_Rocket_StartPosition();
    }
    else if (selectedRobotTexture == "robot_plasma_sonic_blue.tga") {
        return Calculate_RightHand_Sonic_StartPosition();
    }
    else if (selectedRobotTexture == "robot_fire_rocket_blue.tga") {
        return Calculate_RightHand_Rocket_StartPosition();
    }

    // Default to zero offset if no matching robot is found
    return Vector2(m_position.x, m_position.y);
}

Vector2 Robot::Calculate_RedRobot_LeftHand_StartPosition() const {
    std::string selectedRobotTexture = SelectedRobotManager::GetSelectedRobot2Texture();

    // Determine which robot texture is selected and choose the appropriate offset calculation method
    if (selectedRobotTexture == "robot_bullet_bullet_red.tga") {
        return Calculate_LeftHand_Bullet_StartPosition();
    }
    else if (selectedRobotTexture == "robot_bullet_sonic_red.tga") {
        return Calculate_LeftHand_Bullet_StartPosition();
    }
    else if (selectedRobotTexture == "robot_fire_fire_red.tga") {
        return Calculate_LeftHand_Fire_StartPosition();
    }
    else if (selectedRobotTexture == "robot_plasma_rocket_red.tga") {
        return Calculate_LeftHand_Plasma_StartPosition();
    }
    else if (selectedRobotTexture == "robot_plasma_sonic_red.tga") {
        return Calculate_LeftHand_Plasma_StartPosition();
    }
    else if (selectedRobotTexture == "robot_fire_rocket_red.tga") { 
        return Calculate_LeftHand_Fire_StartPosition();
    }

    // Default to zero offset if no matching robot is found
    return Vector2(m_position.x, m_position.y);
}

Vector2 Robot::Calculate_RedRobot_RightHand_StartPosition() const {
    std::string selectedRobotTexture = SelectedRobotManager::GetSelectedRobot2Texture();

    // Determine which robot texture is selected and choose the appropriate offset calculation method
    if (selectedRobotTexture == "robot_bullet_bullet_red.tga") {
        return Calculate_RightHand_Bullet_StartPosition();
    }
    else if (selectedRobotTexture == "robot_bullet_sonic_red.tga") {
        return Calculate_RightHand_Sonic_StartPosition();
    }
    else if (selectedRobotTexture == "robot_fire_fire_red.tga") {
        return Calculate_RightHand_Fire_StartPosition();
    }
    else if (selectedRobotTexture == "robot_plasma_rocket_red.tga") {
        return Calculate_RightHand_Rocket_StartPosition();
    }
    else if (selectedRobotTexture == "robot_plasma_sonic_red.tga") {
        return Calculate_RightHand_Sonic_StartPosition();
    }
    else if (selectedRobotTexture == "robot_fire_rocket_red.tga") {
        return Calculate_RightHand_Rocket_StartPosition();
    }

    // Default to zero offset if no matching robot is found
    return Vector2(m_position.x, m_position.y);
}


Vector2 Robot::CalculateShootingDirection() const {
    float rotationInRadians = (m_rotation - 90.0f) * M_PI / 180.0f;
    return Vector2(cos(rotationInRadians), sin(rotationInRadians));
}

float Robot::GetWidth() const {
    return m_width;
}


float Robot::GetHeight() const {
    return m_height;
}

void Robot::SetSize(float width, float height) {
    m_width = width;
    m_height = height;
}

Vector2 Robot::GetSize() const {
    return Vector2(m_width, m_height);
}