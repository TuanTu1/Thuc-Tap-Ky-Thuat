#include "GSPlay.h"
#include "ResourceManagers.h"
#include "GameObject/MouseButton.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/CollisionHandler.h"
#include "GameObject/Robot.h"
#include <iostream>
#include <memory>


#define M_PI 3.14159265358979323846  // Define Pi
#define M_PI_2 (M_PI / 2)  // Define Pi / 2 (90 degrees in radians)


GSPlay::GSPlay() {
    bulletPropertiesMap = {
            {"bullet", {0.3f, "bullet_shot.mp3"}},
            {"fire", {0.5f, "fire_bullet_shot.mp3"}},
            {"sonic", {0.2f, "sonic_bullet_shot.mp3"}},
            {"rocket", {0.5f, "rocket_bullet_shot.mp3"}},
            {"plasma", {0.6f, "plasma_bullet_shot.mp3"}},
    };
    for (const auto& pair : bulletPropertiesMap) {
        m_timeSinceLastBullet[pair.first + "_left"] = 10.0f;  // Initialize all bullet types to > all bullet fire rate
        m_timeSinceLastBullet[pair.first + "_left_p2"] = 10.0f;
        m_timeSinceLastBullet[pair.first + "_right"] = 10.0f;
        m_timeSinceLastBullet[pair.first + "_right_p2"] = 10.0f;
    }
}

GSPlay::~GSPlay() {}

void GSPlay::Init()
{
    // sound
    Sound::GetInstance()->StopSound();
    Sound::GetInstance()->LoadSound("royal-entry-cyberpunk-music-230630.mp3");
    Sound::GetInstance()->PlaySound("royal-entry-cyberpunk-music-230630.mp3");
    Sound::GetInstance()->LoadSfx("saw_trap_sound.mp3");
    Sound::GetInstance()->LoadSfx("lightning_trap_sound.mp3");
    Sound::GetInstance()->LoadSfx("saw_collide.mp3");
    Sound::GetInstance()->LoadSfx("electric_bullet_sound.mp3");
    Sound::GetInstance()->LoadSfx("button_clicked.mp3");
    Sound::GetInstance()->LoadSfx("electric_bullet_collision.mp3");
    Sound::GetInstance()->LoadSfx("lightning_trap_collision.mp3");

    //bullet sound
    Sound::GetInstance()->LoadSfx("bullet_shot.mp3");
    Sound::GetInstance()->LoadSfx("fire_bullet_shot.mp3");
    Sound::GetInstance()->LoadSfx("sonic_bullet_shot.mp3");
    Sound::GetInstance()->LoadSfx("rocket_bullet_shot.mp3");
    Sound::GetInstance()->LoadSfx("plasma_bullet_shot.mp3");


    // Load arena background texture
    auto texture = ResourceManagers::GetInstance()->GetTexture("arena.tga");
    m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
    m_background->SetSize(ARENA_WIDTH, ARENA_HEIGHT);
    m_background->Set2DPosition(0, 0);

    // Load HUD texture
    auto texture0 = ResourceManagers::GetInstance()->GetTexture("HUD.tga");
    m_HUD = std::make_shared<Sprite2D>(texture0, SDL_FLIP_NONE);
    m_HUD->SetSize(HUD_WIDTH, HUD_HEIGHT);
    m_HUD->Set2DPosition(0, ARENA_HEIGHT);

    auto texture1 = ResourceManagers::GetInstance()->GetTexture("Health_Bar_Table_1.tga");
    m_healthTable1 = std::make_shared<Sprite2D>(texture1, SDL_FLIP_NONE);
    m_healthTable1->SetSize(200, 35);
    m_healthTable1->Set2DPosition(40, ARENA_HEIGHT + (HUD_HEIGHT - m_healthBarHeight) / 2);

    auto texture2 = ResourceManagers::GetInstance()->GetTexture("Health_Bar_Table_2.tga");
    m_healthTable2 = std::make_shared<Sprite2D>(texture2, SDL_FLIP_NONE);
    m_healthTable2->SetSize(200, 35);
    m_healthTable2->Set2DPosition(SCREEN_WIDTH - 240, ARENA_HEIGHT + (HUD_HEIGHT - m_healthBarHeight) / 2);

    // Initialize close button
    texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
    button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
    button->SetSize(50, 50);
    button->Set2DPosition(ARENA_WIDTH - 50, 10);
    button->SetOnClick([this]()
        {
            GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
            Sound::GetInstance()->PlaySfx("button_clicked.mp3");
        });
    m_listButton.push_back(button);

    // Initialize robots
    auto Robot1 = std::make_shared<Robot>(SelectedRobotManager::GetSelectedRobot1Texture(), Vector2(60, 305), 90.0f, 200.0f);
    auto Robot2 = std::make_shared<Robot>(SelectedRobotManager::GetSelectedRobot2Texture(), Vector2(1065, 305), -90.0f, 200.0f);

    m_listRobots.push_back(Robot1);
    m_listRobots.push_back(Robot2);

    m_KeyPressPlayer1 = 0;
    m_KeyPressPlayer2 = 0;

    //Initialize arena
    auto Arena(std::make_shared<Arena>());
    Arena->InitializeArena1(); // Initialize a random arena at startup
    m_currentArena = Arena->GetCurrentArena();
    m_listArenas.push_back(Arena);
    m_timer.Start();

    HandleSoundEvents();


    // Initialize text color and font
    auto font = ResourceManagers::GetInstance()->GetFont("PlaymegamesReguler-2OOee.ttf", 28);


    // Initialize text for Robot1 health
    m_textRobot1Health = std::make_shared<Text>("", font, m_textColor);
    m_textRobot1Health->SetSize(50, 20);
    m_textRobot1Health->Set2DPosition(250, ARENA_HEIGHT + HUD_HEIGHT / 2 - 5);

    // Initialize text for Robot2 health
    m_textRobot2Health = std::make_shared<Text>("", font, m_textColor);
    m_textRobot2Health->SetSize(50, 20);
    m_textRobot2Health->Set2DPosition(SCREEN_WIDTH - 350 - 5, ARENA_HEIGHT + HUD_HEIGHT / 2 - 5);

    // Initialize text for Robot1 full health
    m_textRobot1FullHealth = std::make_shared<Text>(" / 1000", font, m_textColor);
    m_textRobot1FullHealth->SetSize(60, 20);
    m_textRobot1FullHealth->Set2DPosition(250 + 50, ARENA_HEIGHT + HUD_HEIGHT / 2 - 5);

    // Initialize text for Robot2 full health
    m_textRobot2FullHealth = std::make_shared<Text>(" / 1000", font, m_textColor);
    m_textRobot2FullHealth->SetSize(60, 20);
    m_textRobot2FullHealth->Set2DPosition(SCREEN_WIDTH - 300 - 5, ARENA_HEIGHT + HUD_HEIGHT / 2 - 5);

    // Initialize text for map change time countdown
    m_textTimeLeft = std::make_shared<Text>("", font, m_textColor);
    m_textTimeLeft->SetSize(250, 50);
    m_textTimeLeft->Set2DPosition(SCREEN_WIDTH / 2 - 125, SCREEN_HEIGHT - 70);

}

void GSPlay::Exit()
{
    // Cleanup resources if necessary
}

void GSPlay::Pause() {}

void GSPlay::Resume() {}

void GSPlay::HandleEvents() {}



void GSPlay::HandleKeyEvents(SDL_Event& e)
{
    // Handle second player key events (WASD)
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_a: m_KeyPressPlayer1 |= 1; break;
        case SDLK_s: m_KeyPressPlayer1 |= 1 << 1; break;
        case SDLK_d: m_KeyPressPlayer1 |= 1 << 2; break;
        case SDLK_w: m_KeyPressPlayer1 |= 1 << 3; break;

        case SDLK_f: // Shoot bullet for player 1 (left hand)
            if (!m_listRobots.empty()) {
                auto robot1 = m_listRobots.front();  // Assuming player 1's robot is the first in the list
                std::string bulletType = robot1->GetLeftHandBulletTypeFromRobot1();

                // Append "_left" to track the left hand separately
                std::string leftBulletKey = bulletType + "_left";

                // Check fire rate based on bullet type for the left hand
                float bulletFireRate = bulletPropertiesMap[bulletType].fireRate;

                if (m_timeSinceLastBullet[leftBulletKey] >= bulletFireRate && robot1->CanShoot()) {
                    // Calculate the bullet's start position and direction for the left hand
                    Vector2 bulletPosition = robot1->Calculate_BlueRobot_LeftHand_StartPosition();
                    Vector2 shootingDirection = robot1->CalculateShootingDirection();

                    // Compute the rotation angle of the bullet based on the shooting direction
                    float bulletRotation = atan2(shootingDirection.y, shootingDirection.x) * 180.0f / M_PI;  // Convert radians to degrees
                    bulletRotation += 90.0f;

                    // Create and shoot the bullet with rotation
                    auto bullet = Bullet::CreateBullet(bulletPosition, shootingDirection, 1, 1000.0f, bulletType, bulletRotation, robot1,true);
                    m_bullets.push_back(bullet);

                    // Play sound for the bullet type
                    Sound::GetInstance()->PlaySfx(bulletPropertiesMap[bulletType].sound, 0);

                    // Reset the fire rate timer for this bullet type and hand
                    m_timeSinceLastBullet[leftBulletKey] = 0.0f;
                }
            }
            break;

        case SDLK_g: // Shoot bullet for player 1 (right hand)
            if (!m_listRobots.empty()) {
                auto robot1 = m_listRobots.front();  // Assuming player 1's robot is the first in the list
                std::string bulletType = robot1->GetRightHandBulletTypeFromRobot1();

                // Append "_right" to track the right hand separately
                std::string rightBulletKey = bulletType + "_right";

                // Check fire rate based on bullet type for the right hand
                float bulletFireRate = bulletPropertiesMap[bulletType].fireRate;

                if (m_timeSinceLastBullet[rightBulletKey] >= bulletFireRate && robot1->CanShoot()) {
                    // Calculate the bullet's start position and direction for the right hand
                    Vector2 bulletPosition = robot1->Calculate_BlueRobot_RightHand_StartPosition();
                    Vector2 shootingDirection = robot1->CalculateShootingDirection();

                    // Compute the rotation angle of the bullet based on the shooting direction
                    float bulletRotation = atan2(shootingDirection.y, shootingDirection.x) * 180.0f / M_PI;  // Convert radians to degrees
                    bulletRotation += 90.0f;

                    // Create and shoot the bullet with rotation
                    auto bullet = Bullet::CreateBullet(bulletPosition, shootingDirection, 1, 1000.0f, bulletType, bulletRotation, robot1, false);
                    m_bullets.push_back(bullet);

                    // Play sound for the bullet type
                    Sound::GetInstance()->PlaySfx(bulletPropertiesMap[bulletType].sound, 0);

                    // Reset the fire rate timer for this bullet type and hand
                    m_timeSinceLastBullet[rightBulletKey] = 0.0f;
                }
            }
            break;

        default: break;
        }
    }
    else if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_a: m_KeyPressPlayer1 ^= 1; break;
        case SDLK_s: m_KeyPressPlayer1 ^= 1 << 1; break;
        case SDLK_d: m_KeyPressPlayer1 ^= 1 << 2; break;
        case SDLK_w: m_KeyPressPlayer1 ^= 1 << 3; break;
        default: break;
        }
    }

    // Handle first player key events (Arrow keys)
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT: m_KeyPressPlayer2 |= 1; break;
        case SDLK_DOWN: m_KeyPressPlayer2 |= 1 << 1; break;
        case SDLK_RIGHT: m_KeyPressPlayer2 |= 1 << 2; break;
        case SDLK_UP: m_KeyPressPlayer2 |= 1 << 3; break;
        case SDLK_k: // Shoot bullet for player 2 (left hand)
            if (m_listRobots.size() > 1) {
                auto robot2 = m_listRobots.back();  // Assuming player 2's robot is the second in the list
                std::string bulletType = robot2->GetLeftHandBulletTypeFromRobot2();

                // Append "_left" to track the left hand separately for Player 2
                std::string leftBulletKey = bulletType + "_left_p2";

                // Check fire rate based on bullet type for the left hand
                float bulletFireRate = bulletPropertiesMap[bulletType].fireRate;

                if (m_timeSinceLastBullet[leftBulletKey] >= bulletFireRate && robot2->CanShoot()) {
                    // Calculate the bullet's start position and direction for the left hand
                    Vector2 bulletPosition = robot2->Calculate_RedRobot_LeftHand_StartPosition();
                    Vector2 shootingDirection = robot2->CalculateShootingDirection();

                    // Compute the rotation angle of the bullet based on the shooting direction
                    float bulletRotation = atan2(shootingDirection.y, shootingDirection.x) * 180.0f / M_PI;  // Convert radians to degrees
                    bulletRotation += 90.0f;
                    // Create and shoot the bullet with rotation
                    auto bullet = Bullet::CreateBullet(bulletPosition, shootingDirection, 2, 1000.0f, bulletType, bulletRotation, robot2, true);
                    m_bullets.push_back(bullet);

                    // Play sound for the bullet type
                    Sound::GetInstance()->PlaySfx(bulletPropertiesMap[bulletType].sound, 0);

                    // Reset the fire rate timer for this bullet type and hand
                    m_timeSinceLastBullet[leftBulletKey] = 0.0f;
                }
            }
            break;

        case SDLK_l: // Shoot bullet for player 2 (right hand)
            if (m_listRobots.size() > 1) {
                auto robot2 = m_listRobots.back();  // Assuming player 2's robot is the second in the list
                std::string bulletType = robot2->GetRightHandBulletTypeFromRobot2();

                // Append "_right" to track the right hand separately for Player 2
                std::string rightBulletKey = bulletType + "_right_p2";

                // Check fire rate based on bullet type for the right hand
                float bulletFireRate = bulletPropertiesMap[bulletType].fireRate;

                if (m_timeSinceLastBullet[rightBulletKey] >= bulletFireRate && robot2->CanShoot()) {
                    // Calculate the bullet's start position and direction for the right hand
                    Vector2 bulletPosition = robot2->Calculate_RedRobot_RightHand_StartPosition();
                    Vector2 shootingDirection = robot2->CalculateShootingDirection();

                    // Compute the rotation angle of the bullet based on the shooting direction
                    float bulletRotation = atan2(shootingDirection.y, shootingDirection.x) * 180.0f / M_PI;  // Convert radians to degrees
                    bulletRotation += 90.0f;

                    // Create and shoot the bullet with rotation
                    auto bullet = Bullet::CreateBullet(bulletPosition, shootingDirection, 2, 1000.0f, bulletType, bulletRotation, robot2, false);
                    m_bullets.push_back(bullet);

                    // Play sound for the bullet type
                    Sound::GetInstance()->PlaySfx(bulletPropertiesMap[bulletType].sound, 0);

                    // Reset the fire rate timer for this bullet type and hand
                    m_timeSinceLastBullet[rightBulletKey] = 0.0f;
                }
            }
            break;

        default: break;
        }
    }

    else if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT: m_KeyPressPlayer2 ^= 1; break;
        case SDLK_DOWN: m_KeyPressPlayer2 ^= 1 << 1; break;
        case SDLK_RIGHT: m_KeyPressPlayer2 ^= 1 << 2; break;
        case SDLK_UP: m_KeyPressPlayer2 ^= 1 << 3; break;
        default: break;
        }
    }
}




void GSPlay::HandleTouchEvents(SDL_Event& e)
{
    for (auto button : m_listButton)
    {
        if (button->HandleTouchEvent(&e))
        {
            break;
        }
    }
}

void GSPlay::HandleMouseMoveEvents(int x, int y) {}

void GSPlay::HandleSoundEvents() {

    if (m_currentArena == 1) {
        Sound::GetInstance()->PlaySfx("saw_trap_sound.mp3", 22);
    }
    else if (m_currentArena == 2) {
        Sound::GetInstance()->PlaySfx("lightning_trap_sound.mp3", 1);
    }
    else if (m_currentArena == 3) {

    }
}

// Handle bullet collision for generic bullets (can be further refined)
void GSPlay::HandleBulletCollision1(Vector2 bulletPos, Vector2 bulletDir, std::shared_ptr<Robot> targetRobot, std::shared_ptr<Bullet> bullet, std::vector<std::shared_ptr<Bullet>>::iterator& it, std::vector<std::shared_ptr<Bullet>>& bullets, float damage, float pushForce)
{
    // Calculate push direction based on bullet direction (push robot opposite to bullet's movement)
    Vector2 pushDirection = bulletDir * pushForce;
    Vector2 newRobotPos = targetRobot->GetPosition() + pushDirection;

    // Clamp new position to make sure the robot stays within bounds
    newRobotPos = m_boundaryChecker.ClampPosition(newRobotPos);
    targetRobot->SetPosition(newRobotPos.x, newRobotPos.y);

    // Deal damage
    m_Robot1TotalDamage += damage;

    // Remove bullet after collision if it's not a fire bullet
    if (bullet->GetBulletType() != "fire") {
        it = bullets.erase(it); // Erase the bullet and update iterator
        return; // Exit to avoid using an invalid iterator
    }
}

void GSPlay::HandleBulletCollision2(Vector2 bulletPos, Vector2 bulletDir, std::shared_ptr<Robot> targetRobot, std::shared_ptr<Bullet> bullet, std::vector<std::shared_ptr<Bullet>>::iterator& it, std::vector<std::shared_ptr<Bullet>>& bullets, float damage, float pushForce)
{
    // Calculate push direction based on bullet direction (push robot opposite to bullet's movement)
    Vector2 pushDirection = bulletDir * pushForce;
    Vector2 newRobotPos = targetRobot->GetPosition() + pushDirection;

    // Clamp new position to make sure the robot stays within bounds
    newRobotPos = m_boundaryChecker.ClampPosition(newRobotPos);
    targetRobot->SetPosition(newRobotPos.x, newRobotPos.y);

    // Deal damage
    m_Robot2TotalDamage += damage;

    // Remove bullet after collision if it's not a fire bullet
    if (bullet->GetBulletType() != "fire") {
        it = bullets.erase(it); // Erase the bullet and update iterator
        return; // Exit to avoid using an invalid iterator
    }
}


void GSPlay::Update(float deltaTime)
{
    auto robot1 = m_listRobots.front(); // Get the first robot (blue robot)
    auto robot2 = m_listRobots.back(); // Get the second robot (red robot)


    // Update health text for Robot 1 and Robot 2
    std::string robot1HealthText = std::to_string(static_cast<int>(robot1->GetHealth()));
    m_textRobot1Health->SetText(robot1HealthText);

    std::string robot2HealthText = std::to_string(static_cast<int>(robot2->GetHealth()));
    m_textRobot2Health->SetText(robot2HealthText);

    // Calculate the width of the health bars based on current health 
    m_healthBar1Width = (robot1->GetHealth() / 1000.0f) * m_healthBarWidth;
    m_healthBar2Width = (robot2->GetHealth() / 1000.0f) * m_healthBarWidth;

    // Check if either player's health is 0
    if (robot1->GetHealth() <= 0.0f)
    {
        // result table
        auto texture1 = ResourceManagers::GetInstance()->GetTexture("Game_result_table.tga");
        m_tableGameResult = std::make_shared<Sprite2D>(texture1, SDL_FLIP_NONE);
        m_tableGameResult->SetSize(460, 150);
        m_tableGameResult->Set2DPosition(ARENA_WIDTH / 2 - 200 - 30, ARENA_HEIGHT / 2 - 50 - 20);

        // Player 2 wins
        m_textGameResult = std::make_shared<Text>("Player 2 Wins", ResourceManagers::GetInstance()->GetFont("PlaymegamesReguler-2OOee.ttf", 50), m_textColor2);
        m_textGameResult->SetSize(400, 100);
        m_textGameResult->Set2DPosition(ARENA_WIDTH / 2 - 200, ARENA_HEIGHT / 2 - 50);

        // Initialize restart button
        auto texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
        auto btnRestart = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
        btnRestart->SetSize(80, 80);
        btnRestart->Set2DPosition(ARENA_WIDTH / 2 - 40, ARENA_HEIGHT / 2 + 80);
        btnRestart->SetOnClick([this]()
            {
                // Restart the game 
                GameStateMachine::GetInstance()->PopState();
            });

        m_listButton.push_back(btnRestart);

        // Stop further updates
        return;
    }
    else if (robot2->GetHealth() <= 0.0f)
    {
        // result table
        auto texture1 = ResourceManagers::GetInstance()->GetTexture("Game_result_table.tga");
        m_tableGameResult = std::make_shared<Sprite2D>(texture1, SDL_FLIP_NONE);
        m_tableGameResult->SetSize(460, 150);
        m_tableGameResult->Set2DPosition(ARENA_WIDTH / 2 - 200 - 30, ARENA_HEIGHT / 2 - 50 - 20);

        // Player 1 wins
        m_textGameResult = std::make_shared<Text>("Player 1 Wins", ResourceManagers::GetInstance()->GetFont("PlaymegamesReguler-2OOee.ttf", 50), m_textColor1);
        m_textGameResult->SetSize(400, 100);
        m_textGameResult->Set2DPosition(ARENA_WIDTH / 2 - 200, ARENA_HEIGHT / 2 - 50);

        // Initialize restart button
        auto texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
        auto btnRestart = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
        btnRestart->SetSize(80, 80);
        btnRestart->Set2DPosition(ARENA_WIDTH / 2 - 40, ARENA_HEIGHT / 2 + 80);
        btnRestart->SetOnClick([this]()
            {
                // Restart the game 
                GameStateMachine::GetInstance()->PopState();
            });

        m_listButton.push_back(btnRestart);

        // Stop further updates
        return;
    }

    auto arena = m_listArenas.front();

    

    // Update the timer
    Uint32 elapsedTicks = m_timer.GetTicks(); // Get elapsed time
    Uint32 timeRemaining = 10000 - (elapsedTicks % 10000);
    // Update the time left text
    std::string timeLeftText = "Arena change in: " + std::to_string(timeRemaining / 1000) + "s";
    m_textTimeLeft->SetText(timeLeftText);

    // Check if 10 seconds have passed
    if (elapsedTicks >= 10000) {
        // Restart the timer
        m_timer.Start();

        // Initialize a random arena
        arena->InitializeRandomArena();
        m_currentArena = arena->GetCurrentArena(); // Update the current arena
        HandleSoundEvents();
    }

    // Update time since last bullet for each type
    for (auto& pair : m_timeSinceLastBullet) {
        pair.second += deltaTime;  // Increment by the time elapsed since last frame
    }

    // Handle inputs
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        HandleKeyEvents(e);  // No deltaTime needed
    }

    // Update first player movement
    Vector2 position1 = robot1->GetPosition();
    // Handle movement for player 1
    if (m_KeyPressPlayer1 & 1) // LEFT
        position1.x -= robot1->GetMoveSpeed(deltaTime);
    if (m_KeyPressPlayer1 & (1 << 1)) // DOWN
        position1.y += robot1->GetMoveSpeed(deltaTime);
    if (m_KeyPressPlayer1 & (1 << 2)) // RIGHT
        position1.x += robot1->GetMoveSpeed(deltaTime);
    if (m_KeyPressPlayer1 & (1 << 3)) // UP
        position1.y -= robot1->GetMoveSpeed(deltaTime);

    // Handle diagonal movement
    if ((m_KeyPressPlayer1 & 1) && (m_KeyPressPlayer1 & (1 << 3))) // UP + LEFT
    {
        robot1->SetRotation(-45.0f);
    }
    else if ((m_KeyPressPlayer1 & 1) && (m_KeyPressPlayer1 & (1 << 1))) // DOWN + LEFT
    {
        robot1->SetRotation(-135.0f);
    }
    else if ((m_KeyPressPlayer1 & (1 << 2)) && (m_KeyPressPlayer1 & (1 << 3))) // UP + RIGHT
    {
        robot1->SetRotation(45.0f);
    }
    else if ((m_KeyPressPlayer1 & (1 << 2)) && (m_KeyPressPlayer1 & (1 << 1))) // DOWN + RIGHT
    {
        robot1->SetRotation(135.0f);
    }
    else if (m_KeyPressPlayer1 & 1) // LEFT
    {
        robot1->SetRotation(-90.0f);
    }
    else if (m_KeyPressPlayer1 & (1 << 1)) // DOWN
    {
        robot1->SetRotation(180.0f);
    }
    else if (m_KeyPressPlayer1 & (1 << 2)) // RIGHT
    {
        robot1->SetRotation(90.0f);
    }
    else if (m_KeyPressPlayer1 & (1 << 3)) // UP
    {
        robot1->SetRotation(0.0f);
    }

    // Update second player movement
    Vector2 position2 = robot2->GetPosition();
    // Handle movement for player 2
    if (m_KeyPressPlayer2 & 1) // LEFT
        position2.x -= robot2->GetMoveSpeed(deltaTime);
    if (m_KeyPressPlayer2 & (1 << 1)) // DOWN
        position2.y += robot2->GetMoveSpeed(deltaTime);
    if (m_KeyPressPlayer2 & (1 << 2)) // RIGHT
        position2.x += robot2->GetMoveSpeed(deltaTime);
    if (m_KeyPressPlayer2 & (1 << 3)) // UP
        position2.y -= robot2->GetMoveSpeed(deltaTime);

    // Handle diagonal movement
    if ((m_KeyPressPlayer2 & 1) && (m_KeyPressPlayer2 & (1 << 3))) // UP + LEFT
    {
        robot2->SetRotation(-45.0f);
    }
    else if ((m_KeyPressPlayer2 & 1) && (m_KeyPressPlayer2 & (1 << 1))) // DOWN + LEFT
    {
        robot2->SetRotation(-135.0f);
    }
    else if ((m_KeyPressPlayer2 & (1 << 2)) && (m_KeyPressPlayer2 & (1 << 3))) // UP + RIGHT
    {
        robot2->SetRotation(45.0f);
    }
    else if ((m_KeyPressPlayer2 & (1 << 2)) && (m_KeyPressPlayer2 & (1 << 1))) // DOWN + RIGHT
    {
        robot2->SetRotation(135.0f);
    }
    else if (m_KeyPressPlayer2 & 1) // LEFT
    {
        robot2->SetRotation(-90.0f);
    }
    else if (m_KeyPressPlayer2 & (1 << 1)) // DOWN
    {
        robot2->SetRotation(180.0f);
    }
    else if (m_KeyPressPlayer2 & (1 << 2)) // RIGHT
    {
        robot2->SetRotation(90.0f);
    }
    else if (m_KeyPressPlayer2 & (1 << 3)) // UP
    {
        robot2->SetRotation(0.0f);
    }

    // Clamp position within bounds
    float dangerZoneRange = 20.0f;
    float dangerZoneDamage = 50.0f;

    position2 = m_boundaryChecker.ClampPosition(position2);
    robot2->SetPosition(position2.x, position2.y);
    if (position2.x < dangerZoneRange || position2.x > ARENA_WIDTH - ROBOT_WIDTH - dangerZoneRange ||
        position2.y < dangerZoneRange || position2.y > ARENA_HEIGHT - ROBOT_HEIGHT - dangerZoneRange)
    {
        m_Robot2TotalDamage += (dangerZoneDamage * deltaTime); // Damage over time when in danger zone
        robot2->SetMoveSpeed(250.0f * 0.5);
    }
    else {
        robot2->SetMoveSpeed(250.0f);
    }

    position1 = m_boundaryChecker.ClampPosition(position1);
    robot1->SetPosition(position1.x, position1.y);
    if (position1.x < dangerZoneRange || position1.x > ARENA_WIDTH - ROBOT_WIDTH - dangerZoneRange ||
        position1.y < dangerZoneRange || position1.y > ARENA_HEIGHT - ROBOT_HEIGHT - dangerZoneRange)
    {
        m_Robot1TotalDamage += (dangerZoneDamage * deltaTime); // Damage over time when in danger zone
        robot1->SetMoveSpeed(250.0f * 0.5);
    }
    else {
        robot1->SetMoveSpeed(250.0f);
    }

    //Robot vs robot collision 
    CollisionHandler::ResolveCircleCollision(robot1, robot1->GetRadius(), robot1->GetWeight(), robot2, robot2->GetRadius(), robot2->GetWeight());

    //traps collision
    if (m_currentArena == 1) {
        arena->CheckCollisionsWithSaw(robot1, deltaTime);
        arena->CheckCollisionsWithSaw(robot2, deltaTime);
    }
    else if (m_currentArena == 2) {
        arena->CheckCollisionsWithLightning(robot1, deltaTime);
        arena->CheckCollisionsWithLightning(robot2, deltaTime);
    }
    else if (m_currentArena == 3) {
        arena->CheckCollisionsWithLightningBullet1(robot1, deltaTime);
        arena->CheckCollisionsWithLightningBullet2(robot2, deltaTime);
        if (arena->robot1IsStuned())
        {
            robot1->DisableShooting();
            robot1->SetMoveSpeed(0.0f);
            m_timeSinceRobot1Stuned += deltaTime;
        }
        if (m_timeSinceRobot1Stuned >= 1.0f) {
            robot1->EnableShooting();
            robot1->SetMoveSpeed(250.0f);
            arena->robot1StunedEnd();
            m_timeSinceRobot1Stuned = 0.0f;
        }

        if (arena->robot2IsStuned())
        {
            robot2->DisableShooting();
            robot2->SetMoveSpeed(0.0f);
            m_timeSinceRobot2Stuned += deltaTime;
        }
        if (m_timeSinceRobot2Stuned >= 1.0f) {
            robot2->EnableShooting();
            robot2->SetMoveSpeed(250.0f);
            arena->robot2StunedEnd();
            m_timeSinceRobot2Stuned = 0.0f;
        }
    }

// Check bullet collisions
    for (auto it = m_bullets.begin(); it != m_bullets.end();)
    {
        Vector2 bulletPos = (*it)->GetPosition();
        Vector2 bulletDir = (*it)->GetDirection();
        float bulletWidth = (*it)->GetWidth();
        float bulletHeight = (*it)->GetHeight();
        float bulletRadius = 5.0f;
        std::string bulletType = (*it)->GetBulletType();  // Get bullet type
        auto bullet = *it;  // Store the bullet in a variable for easy access


        // Check collision with robot2, but make sure the bullet wasn't fired by robot2 (owner != 2)
        if (bullet->GetOwner() == 1)
        {
            // Use CheckRectangleCollision for specific bullet types
            if (bulletType == "rocket" || bulletType == "fire" || bulletType == "sonic")
            {
                if (CollisionHandler::CheckRectangleCollision(bulletPos, bulletWidth, bulletHeight, robot2->GetPosition(), 95.0f, 70.0f)) // Assuming robot height is 90
                {
                    if (bulletType == "rocket")
                    {
                        HandleBulletCollision2(bulletPos, bulletDir, robot2, bullet, it, m_bullets, 100.0f, 100.0f);
                    }
                    else if (bulletType == "fire")
                    {
                        HandleBulletCollision2(bulletPos, bulletDir, robot2, bullet, it, m_bullets, 1.2f, 0.0f);
                        
                        ++it; // Erase this bullet
                    }
                    else if (bulletType == "sonic")
                    {
                        HandleBulletCollision2(bulletPos, bulletDir, robot2, bullet, it, m_bullets, 0.0f, 200.0f);
                    }
                }
                else
                {
                    ++it;
                }
            }
            else if (bulletType == "bullet" || bulletType == "plasma")
            {
                if (CollisionHandler::CheckCircleCollision(bulletPos, bulletRadius, robot2->GetPosition(), 45.0f)) // Assuming robot height is 90
                {
                    if (bulletType == "bullet")
                    {
                        HandleBulletCollision2(bulletPos, bulletDir, robot2, bullet, it, m_bullets, 25.0f, 50.0f);
                        
                    }
                    else if (bulletType == "plasma")
                    {
                        HandleBulletCollision2(bulletPos, bulletDir, robot2, bullet, it, m_bullets, 100.0f, 100.0f);
                        
                    }
                }
                else
                {
                    ++it;
                }
            }
        }

        // Check collision with robot1, but make sure the bullet wasn't fired by robot1 (owner != 1)
        else if (bullet->GetOwner() == 2)
        {
            // Use CheckRectangleCollision for specific bullet types
            if (bulletType == "rocket" || bulletType == "fire" || bulletType == "sonic")
            {
                if (CollisionHandler::CheckRectangleCollision(bulletPos, bulletWidth, bulletHeight, robot1->GetPosition(), 95.0f, 70.0f)) // Assuming robot height is 90
                {
                    if (bulletType == "rocket")
                    {
                        HandleBulletCollision1(bulletPos, bulletDir, robot1, bullet, it, m_bullets, 100.0f, 100.0f);
                    }
                    else if (bulletType == "fire")
                    {
                        HandleBulletCollision1(bulletPos, bulletDir, robot1, bullet, it, m_bullets, 1.2f, 0.0f);
                        
                        ++it; // Erase this bullet
                    }
                    else if (bulletType == "sonic")
                    {
                        HandleBulletCollision1(bulletPos, bulletDir, robot1, bullet, it, m_bullets, 0.0f, 200.0f);
                    }
                }
                else
                {
                    ++it;
                }
            }
            else if (bulletType == "bullet" || bulletType == "plasma")
            {
                if (CollisionHandler::CheckCircleCollision(bulletPos, bulletRadius, robot1->GetPosition(), 45.0f)) // Assuming robot height is 90
                {
                    if (bulletType == "bullet")
                    {
                        HandleBulletCollision1(bulletPos, bulletDir, robot1, bullet, it, m_bullets, 25.0f, 50.0f);
                        
                    }
                    else if (bulletType == "plasma")
                    {
                        HandleBulletCollision1(bulletPos, bulletDir, robot1, bullet, it, m_bullets, 100.0f, 100.0f);
                        
                    }
                }
                else
                {
                    ++it;
                }
            }
        }
        else
        {
            ++it;
        }
    }





    // Update buttons 
    for (auto button : m_listButton)
    {
        button->Update(deltaTime);
    }

    // Update traps
    for (auto trap : arena->GetTraps())
    {
        trap->Update(deltaTime);
    }

    //arena update
    arena->Update(deltaTime, m_listRobots);

    // Update robot
    robot1->TakeDamage(m_Robot1TotalDamage);
    robot2->TakeDamage(m_Robot2TotalDamage);

    m_Robot1TotalDamage = 0.0f;
    m_Robot2TotalDamage = 0.0f;

    robot1->Update(deltaTime);
    robot2->Update(deltaTime);

    // Update bullets
    for (auto it = m_bullets.begin(); it != m_bullets.end();)
    {
        (*it)->Update(deltaTime); // Update the bullet's position and animation (if any)

        // Check if the bullet has exceeded its max range, is off-screen, or if its animation has completed (for fire bullets)
        if ((*it)->HasExceededMaxRange() || (*it)->IsOffScreen() || (*it)->HasAnimationCompleted())
        {
            // Remove bullet if it meets any of the above conditions
            it = m_bullets.erase(it);
        }
        else
        {
            ++it;
        }
    }

}




void GSPlay::Draw(SDL_Renderer* renderer) {

    m_background->Draw(renderer);
    m_HUD->Draw(renderer);

    // Draw bullets
    for (const auto& bullet : m_bullets) {
        if (bullet->GetAnimation() && bullet->GetBulletType() != "fire") {
            bullet->GetAnimation()->Draw(renderer); // Draw animated bullet
        }
        else if (bullet->GetSprite()) {
            bullet->GetSprite()->Draw(renderer);    // Draw static bullet
        }
    }
   
    //Draw Robots
    for (auto robot : m_listRobots) {
        robot->GetSprite()->Draw(renderer);
    }

    for (auto button : m_listButton) {
        button->Draw(renderer);
    }
    
    // Draw bullets fire
    for (const auto& bullet : m_bullets) {
        if (bullet->GetAnimation()) {
            if (bullet->GetBulletType() == "fire") {
                bullet->GetAnimation()->Draw(renderer); // Draw animated bullet
            }
        }
    }
    
    // Draw arena traps
    auto arena = m_listArenas.front();
    arena->Draw(renderer); // Get the list of traps 

    //health bar table
    m_healthTable1->Draw(renderer);
    m_healthTable2->Draw(renderer);

    // Render Robot1 health bar
    SDL_Rect healthBar1Background = { (int)m_healthBar1Pos.x, (int)m_healthBar1Pos.y, m_healthBarWidth, m_healthBarHeight };
    SDL_Rect healthBar1Foreground = { (int)m_healthBar1Pos.x, (int)m_healthBar1Pos.y, (int)m_healthBar1Width, m_healthBarHeight };

    // Background health bar (gray)
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);  // Gray
    SDL_RenderFillRect(renderer, &healthBar1Background);

    // Foreground health bar (green for healthy robot)
    SDL_SetRenderDrawColor(renderer, 0, 162, 255, 255);  // blue
    SDL_RenderFillRect(renderer, &healthBar1Foreground);

    // Render Robot2 health bar
    SDL_Rect healthBar2Background = { (int)m_healthBar2Pos.x, (int)m_healthBar2Pos.y, m_healthBarWidth, m_healthBarHeight };
    SDL_Rect healthBar2Foreground = {
    (int)(m_healthBar2Pos.x + (m_healthBarWidth - m_healthBar2Width)), (int)m_healthBar2Pos.y, (int)m_healthBar2Width, m_healthBarHeight };

    // Background health bar (gray)
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);  // Gray
    SDL_RenderFillRect(renderer, &healthBar2Background);

    // Foreground health bar (red for damaged robot)
    SDL_SetRenderDrawColor(renderer, 210, 65, 64, 255);  // Red
    SDL_RenderFillRect(renderer, &healthBar2Foreground);

    // Render the text

    m_textRobot1Health->Draw(renderer);
    m_textRobot2Health->Draw(renderer);

    m_textRobot1FullHealth->Draw(renderer);
    m_textRobot2FullHealth->Draw(renderer);

    m_textTimeLeft->Draw(renderer);

    if (m_textGameResult)
    {
        m_tableGameResult->Draw(renderer);
        m_textGameResult->Draw(renderer);
    }
}