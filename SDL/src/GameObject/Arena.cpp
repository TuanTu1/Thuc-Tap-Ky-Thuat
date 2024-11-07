#include "Arena.h"
#include "ResourceManagers.h"
#include <memory>
#include <iostream>
#include "Robot.h"



Arena::Arena()
    : m_bulletManager(std::make_unique<BulletManager>()), // Use std::make_unique for safe memory management
    m_shootingInterval(3.5f), // Interval for shooting bullets
    m_timeSinceLastShot(10.0f)
{
}

Arena::~Arena() {
}
void Arena::InitializeArena1() {
    auto texture = ResourceManagers::GetInstance()->GetTexture("Saw.tga");
    m_listTraps.clear();

    auto trap0 = std::make_shared<Trap>(texture, 8, 1, 0.03f, ARENA_WIDTH / 2 - 50.0f, ARENA_HEIGHT / 2 - 50.0f);
    trap0->SetSize(100.0f, 100.0f);
    m_listTraps.push_back(trap0);

    auto trap1 = std::make_shared<Trap>(texture, 8, 1, 0.03f, 200.0f, 150.0f);
    trap1->SetSize(100.0f, 100.0f);
    m_listTraps.push_back(trap1);

    auto trap2 = std::make_shared<Trap>(texture, 8, 1, 0.03f, ARENA_WIDTH - 300.0f, 150.0f);
    trap2->SetSize(100.0f, 100.0f);
    m_listTraps.push_back(trap2);

    auto trap3 = std::make_shared<Trap>(texture, 8, 1, 0.03f, 200.0f, ARENA_HEIGHT - 250.0f);
    trap3->SetSize(100.0f, 100.0f);
    m_listTraps.push_back(trap3);

    auto trap4 = std::make_shared<Trap>(texture, 8, 1, 0.03f, ARENA_WIDTH - 300.0f, ARENA_HEIGHT - 250.0f);
    trap4->SetSize(100.0f, 100.0f);
    m_listTraps.push_back(trap4);

     
}

void Arena::InitializeArena2() {
    // Initialize Lightning traps (root and light)
    auto texture = ResourceManagers::GetInstance()->GetTexture("Lightning_upper_root.tga");
    m_listTraps.clear();

    auto trap0 = std::make_shared<Trap>(texture, 12, 1, 0.4f, 250.0f, 0.0f);
    trap0->SetSize(220.0f, 220.0f);
    m_listTraps.push_back(trap0);

    texture = ResourceManagers::GetInstance()->GetTexture("Lightning_lower_root.tga");
    auto trap1 = std::make_shared<Trap>(texture, 12, 1, 0.4f, 250.0f, ARENA_HEIGHT - 220.0f);
    trap1->SetSize(220.0f, 220.0f);
    m_listTraps.push_back(trap1);

    texture = ResourceManagers::GetInstance()->GetTexture("Lightning.tga");
    auto trap2 = std::make_shared<Trap>(texture, 12, 1, 0.4f, 250.0f, 0.0f);
    trap2->SetSize(220.0f, 220.0f);
    m_listTraps.push_back(trap2);

    auto trap3 = std::make_shared<Trap>(texture, 12, 1, 0.4f, 250.0f, 170.0f);
    trap3->SetSize(220.0f, 220.0f);
    m_listTraps.push_back(trap3);

    auto trap4 = std::make_shared<Trap>(texture, 12, 1, 0.4f, 250.0f, ARENA_HEIGHT - 390.0f);
    trap4->SetSize(220.0f, 220.0f);
    m_listTraps.push_back(trap4);

    auto trap5 = std::make_shared<Trap>(texture, 12, 1, 0.4f, 250.0f, ARENA_HEIGHT - 220.0f);
    trap5->SetSize(220.0f, 220.0f);
    m_listTraps.push_back(trap5);

    // Initialize Lightning traps on the opposite side
    texture = ResourceManagers::GetInstance()->GetTexture("Lightning_upper_root.tga");
    auto trap6 = std::make_shared<Trap>(texture, 12, 1, 0.4f, ARENA_WIDTH - 470.0f, 0.0f);
    trap6->SetSize(220.0f, 220.0f);
    m_listTraps.push_back(trap6);

    texture = ResourceManagers::GetInstance()->GetTexture("Lightning_lower_root.tga");
    auto trap7 = std::make_shared<Trap>(texture, 12, 1, 0.4f, ARENA_WIDTH - 470.0f, ARENA_HEIGHT - 220.0f);
    trap7->SetSize(220.0f, 220.0f);
    m_listTraps.push_back(trap7);

    texture = ResourceManagers::GetInstance()->GetTexture("Lightning.tga");
    auto trap8 = std::make_shared<Trap>(texture, 12, 1, 0.4f, ARENA_WIDTH - 470.0f, 0.0f);
    trap8->SetSize(220.0f, 220.0f);
    m_listTraps.push_back(trap8);

    auto trap9 = std::make_shared<Trap>(texture, 12, 1, 0.4f, ARENA_WIDTH - 470.0f, 170.0f);
    trap9->SetSize(220.0f, 220.0f);
    m_listTraps.push_back(trap9);

    auto trap10 = std::make_shared<Trap>(texture, 12, 1, 0.4f, ARENA_WIDTH - 470.0f, ARENA_HEIGHT - 390.0f);
    trap10->SetSize(220.0f, 220.0f);
    m_listTraps.push_back(trap10);

    auto trap11 = std::make_shared<Trap>(texture, 12, 1, 0.4f, ARENA_WIDTH - 470.0f, ARENA_HEIGHT - 220.0f);
    trap11->SetSize(220.0f, 220.0f);
    m_listTraps.push_back(trap11);

}

void Arena::InitializeArena3() {

    auto texture2 = ResourceManagers::GetInstance()->GetTexture("Electric_canon.tga");
    m_listTraps.clear();

    // Generate random positions along each side, avoiding 50.0f near edges
    float xPos[4] = {
        50.0f + rand() % (ARENA_WIDTH - 100),  
        50.0f + rand() % (ARENA_WIDTH - 100),  
        0.0f,                                   
        ARENA_WIDTH - 50.0f                    
    };

    float yPos[4] = {
        0.0f,                                   
        ARENA_HEIGHT - 50.0f,                 
        50.0f + rand() % (ARENA_HEIGHT - 100), 
        50.0f + rand() % (ARENA_HEIGHT - 100)  
    };

    // Define rotation angles for each side 
    float rotation[4] = {
        180.0f, 
        0.0f,   
        90.0f,   
        -90.0f   
    };

    // Spawn 4 traps
    for (int i = 0; i < 4; ++i) {
        auto trap = std::make_shared<Trap>(texture2, 1, 1, 0.05f, xPos[i], yPos[i]);
        trap->SetSize(50.0f, 50.0f);
        trap->SetRotation(rotation[i]);  
        m_listTraps.push_back(trap);
    }

}

void Arena::FireFromElectricCanon() {
    if (m_currentArena != 3) {
        return;  // Only fire bullets in Arena 3
    }

    for (size_t i = 0; i < m_listTraps.size(); ++i) {
        auto trap = m_listTraps[i];

        // Get bullet position and direction
        Vector2 bulletPos = trap->GetPosition();
        float rotation = trap->GetRotation() - 90.0f; // Correct rotation for direction
        Vector2 direction = Vector2(cos(rotation * M_PI / 180.0f), sin(rotation * M_PI / 180.0f));

        int owner = i + 3; // Identifier for the owner
        float maxRange = 2000.0f;

        // Fire the bullet using BulletManager
        auto bullet = m_bulletManager->FireBullet(bulletPos, direction, owner, maxRange);

        // Add bullet to m_activeBullets if you're managing them manually
        m_activeBullets.push_back(bullet);

        //sound
        Sound::GetInstance()->PlaySfx("electric_bullet_sound.mp3");
    }
}


void Arena::Update(float deltaTime, const std::list<std::shared_ptr<Robot>>& robots) {
    m_timeSinceLastShot += deltaTime;  // Increment the time since the last shot

    // Check if enough time has passed to fire a new bullet
    if (m_timeSinceLastShot >= m_shootingInterval) {
        FireFromElectricCanon();  // Fire bullets
        m_timeSinceLastShot = 0.0f;  // Reset the timer after firing
    }

    // Update all active bullets
    for (auto& bullet : m_activeBullets) {
        bullet->Update(deltaTime);  // Update the position and status of each bullet
    }

    // Remove bullets that are off-screen or exceeded their range
    m_activeBullets.erase(
        std::remove_if(m_activeBullets.begin(), m_activeBullets.end(),
            [](const std::shared_ptr<Bullet>& bullet) {
                return bullet->IsOffScreen() || bullet->HasExceededMaxRange();
            }),
        m_activeBullets.end());
}




void Arena::InitializeRandomArena() {
    int randomArena;
    do {
        randomArena = std::rand() % 3 + 1;  // Generate a random number between 1 and 3
    } while (randomArena == m_currentArena);  // Repeat until a different arena is selected

    m_currentArena = randomArena;

    if (randomArena == 1) {
        InitializeArena1(); // Initialize Arena 1 (Saw)
    }
    else if (randomArena == 2) {
        InitializeArena2(); // Initialize Arena 2 (Lightning)
    }
    else if (randomArena == 3) {
        InitializeArena3(); // Initialize Arena 3 (Random electric canon)
    }
}


void Arena::CheckCollisionsWithSaw(std::shared_ptr<Robot> robot, float deltaTime) {
    float slowFactor = 0.05f;
    bool collisionDetected = false;

    // Loop through the saw traps (first 5 traps)
    for (int i = 0; i < 5; ++i) {
        if (CollisionHandler::CheckCircleCollisionForTrap(robot, robot->GetRadius(), m_listTraps[i]->GetPosition(), 50.0f)) {
            collisionDetected = true;
            break;
        }
    }

    if (collisionDetected) {
        robot->SetMoveSpeed(250.0f * slowFactor);
        robot->TakeDamage(100.0f * deltaTime);  // Damage over time
        Sound::GetInstance()->PlaySfx("saw_collide.mp3");
    }
    else {
        robot->SetMoveSpeed(250.0f);
    }
    
   
}

void Arena::CheckCollisionsWithLightning(std::shared_ptr<Robot> robot, float deltaTime) {
    float slowFactor = 0.2f;
    bool collisionDetected = false;

    // Ensure lightning trap animation is in active state (frames 3 to 10)
    if (m_listTraps[0]->GetCurrentFrame() >= 3 && m_listTraps[0]->GetCurrentFrame() <= 10) {
        // Loop through the lightning traps (starting from index 7)
        
        for (int i = 0; i < 10; ++i) {
            if (CollisionHandler::CheckRectangleCollisionForLightning(robot->GetPosition(), robot->GetWidth(), robot->GetHeight(),
                m_listTraps[i]->GetPosition(), m_listTraps[i]->GetWidth(), m_listTraps[i]->GetHeight())) {
                collisionDetected = true;
                break;
            }
        }
    }

    if (collisionDetected) {
        robot->SetMoveSpeed(250.0f * slowFactor);
        robot->TakeDamage(50.0f * deltaTime);  // Damage over time

        //sound
        Sound::GetInstance()->PlaySfx("lightning_trap_collision.mp3");
    }
    else {
        robot->SetMoveSpeed(250.0f);
    }
}

void Arena::CheckCollisionsWithLightningBullet1(std::shared_ptr<Robot> robot, float deltaTime) {
    for (auto it = m_activeBullets.begin(); it != m_activeBullets.end();)
    {
        Vector2 bulletPos = (*it)->GetPosition();
        Vector2 bulletDir = (*it)->GetDirection();

        if (CollisionHandler::CheckCircleCollision(bulletPos, 5.0f, robot->GetPosition(), 45.0f))
        {
            // Handle collision with robot1 (e.g., push robot1 backward)
            float pushForce = 0.0f; // Adjust push force as needed

            // Calculate push direction based on bullet direction (push robot opposite to bullet's movement)
            Vector2 pushDirection = bulletDir * pushForce;
            Vector2 newRobot1Pos = robot->GetPosition() + pushDirection * deltaTime;

            // Clamp new position to make sure the robot stays within bounds
            newRobot1Pos = m_boundaryChecker.ClampPosition(newRobot1Pos);
            robot->SetPosition(newRobot1Pos.x, newRobot1Pos.y);

            //Deal damage
            robot->TakeDamage(100.0f);

            // Remove bullet after collision
            it = m_activeBullets.erase(it);
            m_robot1stuned = true;

            //sound
            Sound::GetInstance()->PlaySfx("electric_bullet_collision.mp3");
     
        }
        else
        {
            ++it;
        }
    }
}

void Arena::CheckCollisionsWithLightningBullet2(std::shared_ptr<Robot> robot, float deltaTime) {
    for (auto it = m_activeBullets.begin(); it != m_activeBullets.end();)
    {
        Vector2 bulletPos = (*it)->GetPosition();
        Vector2 bulletDir = (*it)->GetDirection();

        if (CollisionHandler::CheckCircleCollision(bulletPos, 5.0f, robot->GetPosition(), 45.0f))
        {
            // Handle collision with robot1 (e.g., push robot1 backward)
            float pushForce = 0.0f; // Adjust push force as needed

            // Calculate push direction based on bullet direction (push robot opposite to bullet's movement)
            Vector2 pushDirection = bulletDir * pushForce;
            Vector2 newRobot2Pos = robot->GetPosition() + pushDirection * deltaTime;

            // Clamp new position to make sure the robot stays within bounds
            newRobot2Pos = m_boundaryChecker.ClampPosition(newRobot2Pos);
            robot->SetPosition(newRobot2Pos.x, newRobot2Pos.y);

            //Deal damage
            robot->TakeDamage(100.0f);

            // Remove bullet after collision
            it = m_activeBullets.erase(it);
            m_robot2stuned = true;

            //sound
            Sound::GetInstance()->PlaySfx("electric_bullet_collision.mp3");
        }
        else
        {
            ++it;
        }
    }
}

int Arena::GetCurrentArena() { 
    return m_currentArena;
}

std::vector<std::shared_ptr<Trap>> Arena::GetTraps() const {
    return m_listTraps;
}

BulletManager& Arena::GetBulletManager() {
    return *m_bulletManager; // Dereference the pointer to return the actual object
}

void Arena::Draw(SDL_Renderer* renderer) {
    // Loop through all traps in the arena and draw each one
    for (auto& trap : m_listTraps) {
        trap->Draw(renderer); // Use the Trap's own Draw function
    }

    // Optionally, draw active bullets if needed
    for (auto& bullet : m_activeBullets) {
        bullet->Draw(renderer); // Assuming Bullet class has a Draw function
    }
}

bool Arena::robot1IsStuned() {
    return m_robot1stuned;
}

bool Arena::robot2IsStuned() {
    return m_robot2stuned;
}

void Arena::robot1StunedEnd() {
    m_robot1stuned = false;
}

void Arena::robot2StunedEnd() {
    m_robot2stuned = false;
}

