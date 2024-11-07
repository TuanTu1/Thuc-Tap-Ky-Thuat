#include "GSRobotSelectMenu.h"


GSRobotSelectMenu::GSRobotSelectMenu() : GameStateBase(StateType::STATE_ROBOT_MENU),
m_background(nullptr),
m_robotWindow1(nullptr), m_robotWindow2(nullptr),
currentRobot1(0), currentRobot2(0)
{
    // Robot image file names for window 1 (blue) and window 2 (red)
    robotImagesWindow1 = {
        "robot_bullet_bullet_blue.tga",
        "robot_bullet_sonic_blue.tga",
        "robot_fire_fire_blue.tga",
        "robot_plasma_rocket_blue.tga",
        "robot_plasma_sonic_blue.tga",
        "robot_fire_rocket_blue.tga"
    };

    robotImagesWindow2 = {
        "robot_bullet_bullet_red.tga",
        "robot_bullet_sonic_red.tga",
        "robot_fire_fire_red.tga",
        "robot_plasma_rocket_red.tga",
        "robot_plasma_sonic_red.tga",
        "robot_fire_rocket_red.tga"
    };
}

GSRobotSelectMenu::~GSRobotSelectMenu() { }

void GSRobotSelectMenu::Init() {
    // Background setup
    auto texture = ResourceManagers::GetInstance()->GetTexture("bg_robot_select_menu.tga");
    m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
    m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    m_background->Set2DPosition(0, 0);

    // Robot selection windows
    texture = ResourceManagers::GetInstance()->GetTexture("robot_select_window.tga");
    m_robotWindow1 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
    m_robotWindow1->SetSize(350, 400);
    m_robotWindow1->Set2DPosition((SCREEN_WIDTH / 2 - m_robotWindow1->GetWidth()) / 2 - 50, (SCREEN_HEIGHT - m_robotWindow1->GetHeight()) / 2 - 50);

    m_robotWindow2 = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
    m_robotWindow2->SetSize(350, 400);
    m_robotWindow2->Set2DPosition(SCREEN_WIDTH / 2 + (SCREEN_WIDTH / 2 - m_robotWindow2->GetWidth()) / 2 + 50, (SCREEN_HEIGHT - m_robotWindow2->GetHeight()) / 2 - 50);

    // Bullet type list window
    texture = ResourceManagers::GetInstance()->GetTexture("Bullet_list.tga");
    m_bulletTypeList = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
    m_bulletTypeList->SetSize(350, 400);
    m_bulletTypeList->Set2DPosition((SCREEN_WIDTH  - m_bulletTypeList->GetWidth()) / 2, (SCREEN_HEIGHT - m_bulletTypeList->GetHeight()) / 2 - 50);

    // Initialize robot sprites for both windows
    UpdateRobotDisplay();

    // Prev/Next buttons for robot selection
    Sound::GetInstance()->LoadSfx("button_clicked.mp3");
    texture = ResourceManagers::GetInstance()->GetTexture("btn_prev.tga");
    btnPrev1 = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
    btnPrev1->SetSize(80, 80);
    btnPrev1->Set2DPosition(m_robotWindow1->Get2DPosition().x + btnPrev1->GetWidth() / 2, m_robotWindow1->Get2DPosition().y + m_robotWindow1->GetHeight() - 1.5 * btnPrev1->GetHeight());
    btnPrev1->SetOnClick([this]() {
        currentRobot1 = (currentRobot1 - 1 + robotImagesWindow1.size()) % robotImagesWindow1.size();
        UpdateRobotDisplay();
        Sound::GetInstance()->PlaySfx("button_clicked.mp3");
        });
    m_listButton.push_back(btnPrev1);

    btnPrev2 = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
    btnPrev2->SetSize(80, 80);
    btnPrev2->Set2DPosition(m_robotWindow2->Get2DPosition().x + btnPrev2->GetWidth() / 2, m_robotWindow2->Get2DPosition().y + m_robotWindow2->GetHeight() - 1.5 * btnPrev2->GetHeight());
    btnPrev2->SetOnClick([this]() {
        currentRobot2 = (currentRobot2 - 1 + robotImagesWindow2.size()) % robotImagesWindow2.size();
        UpdateRobotDisplay();
        Sound::GetInstance()->PlaySfx("button_clicked.mp3");
        });
    m_listButton.push_back(btnPrev2);

    texture = ResourceManagers::GetInstance()->GetTexture("btn_next.tga");
    btnNext1 = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
    btnNext1->SetSize(80, 80);
    btnNext1->Set2DPosition(m_robotWindow1->Get2DPosition().x + m_robotWindow1->GetWidth() - btnNext1->GetWidth() * 1.5, m_robotWindow1->Get2DPosition().y + m_robotWindow1->GetHeight() - 1.5 * btnNext1->GetHeight());
    btnNext1->SetOnClick([this]() {
        currentRobot1 = (currentRobot1 + 1) % robotImagesWindow1.size();
        UpdateRobotDisplay();
        Sound::GetInstance()->PlaySfx("button_clicked.mp3");
        });
    m_listButton.push_back(btnNext1);

    btnNext2 = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
    btnNext2->SetSize(80, 80);
    btnNext2->Set2DPosition(m_robotWindow2->Get2DPosition().x + m_robotWindow2->GetWidth() - btnNext2->GetWidth() * 1.5, m_robotWindow2->Get2DPosition().y + m_robotWindow2->GetHeight() - 1.5 * btnNext2->GetHeight());
    btnNext2->SetOnClick([this]() {
        currentRobot2 = (currentRobot2 + 1) % robotImagesWindow2.size();
        UpdateRobotDisplay();
        Sound::GetInstance()->PlaySfx("button_clicked.mp3");
        });
    m_listButton.push_back(btnNext2);

    // Start button
    texture = ResourceManagers::GetInstance()->GetTexture("btn_start.tga");
    btnStart = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
    btnStart->SetSize(210, 60);
    btnStart->Set2DPosition((SCREEN_WIDTH - btnStart->GetWidth()) / 2, (SCREEN_HEIGHT + m_robotWindow1->Get2DPosition().y + m_robotWindow1->GetHeight()) / 2 - btnStart->GetHeight());
    btnStart->SetOnClick([this]() {
        GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
        SelectedRobotManager::SetSelectedRobot1Texture(robotImagesWindow1[currentRobot1]);
        SelectedRobotManager::SetSelectedRobot2Texture(robotImagesWindow2[currentRobot2]);
        Sound::GetInstance()->PlaySfx("button_clicked.mp3");
        });
    m_listButton.push_back(btnStart);

    // Back button to return to GSMenu
    texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
    auto btnBack = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
    btnBack->SetSize(50, 50);
    btnBack->Set2DPosition(SCREEN_WIDTH - btnBack->GetWidth() -10, 10); 
    btnBack->SetOnClick([]() {
        GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
        Sound::GetInstance()->PlaySfx("button_clicked.mp3");
        });
    m_listButton.push_back(btnBack);
    
    // Initialize text for Player1 
    auto font = ResourceManagers::GetInstance()->GetFont("PlaymegamesReguler-2OOee.ttf", 28);
    m_textPlayer1 = std::make_shared<Text>("Player 1", font, m_textColor);
    m_textPlayer1->SetSize(120, 40);
    m_textPlayer1->Set2DPosition(m_robotWindow1->Get2DPosition().x + (m_robotWindow1->GetWidth() - m_textPlayer1->GetWidth()) / 2, m_robotWindow1->Get2DPosition().y + 10);

    m_textPlayer2 = std::make_shared<Text>("Player 2", font, m_textColor);
    m_textPlayer2->SetSize(120, 40);
    m_textPlayer2->Set2DPosition(m_robotWindow2->Get2DPosition().x + (m_robotWindow2->GetWidth() - m_textPlayer2->GetWidth()) / 2, m_robotWindow2->Get2DPosition().y + 10);

    // Sound
    Sound::GetInstance()->StopSound();
    Sound::GetInstance()->LoadSound("dystorpian-250560.mp3");
    Sound::GetInstance()->PlaySound("dystorpian-250560.mp3");
}

void GSRobotSelectMenu::UpdateRobotDisplay() {
    // Update robot images for window 1
    auto texture1 = ResourceManagers::GetInstance()->GetTexture(robotImagesWindow1[currentRobot1]);
    m_robot1 = std::make_shared<Sprite2D>(texture1, SDL_FLIP_NONE);
    m_robot1->SetSize(190, 140);  
    m_robot1->Set2DPosition(m_robotWindow1->Get2DPosition().x + (m_robotWindow1->GetWidth() - m_robot1->GetWidth()) / 2,
        m_robotWindow1->Get2DPosition().y + (m_robotWindow1->GetHeight() - m_robot1->GetHeight()) / 2 - 20);

    // Update robot images for window 2
    auto texture2 = ResourceManagers::GetInstance()->GetTexture(robotImagesWindow2[currentRobot2]);
    m_robot2 = std::make_shared<Sprite2D>(texture2, SDL_FLIP_NONE);
    m_robot2->SetSize(190, 140);  
    m_robot2->Set2DPosition(m_robotWindow2->Get2DPosition().x + (m_robotWindow2->GetWidth() - m_robot2->GetWidth()) / 2,
        m_robotWindow2->Get2DPosition().y + (m_robotWindow2->GetHeight() - m_robot2->GetHeight()) / 2 - 20);
}

void GSRobotSelectMenu::Update(float deltaTime) {
    m_background->Update(deltaTime);
    m_robotWindow1->Update(deltaTime);
    m_robotWindow2->Update(deltaTime);
    m_robot1->Update(deltaTime);  // Update the robot images
    m_robot2->Update(deltaTime);
    for (auto& button : m_listButton) {
        button->Update(deltaTime);
    }
}

void GSRobotSelectMenu::Draw(SDL_Renderer* renderer) {
    m_background->Draw(renderer);
    m_robotWindow1->Draw(renderer);
    m_robotWindow2->Draw(renderer);
    m_bulletTypeList->Draw(renderer);
    m_robot1->Draw(renderer);  
    m_robot2->Draw(renderer);
    for (auto& button : m_listButton) {
        button->Draw(renderer);
    }
    m_textPlayer1->Draw(renderer);
    m_textPlayer2->Draw(renderer);
}


void GSRobotSelectMenu::Exit() { }

void GSRobotSelectMenu::Pause() { Sound::GetInstance()->PauseSound(); }

void GSRobotSelectMenu::Resume() { Sound::GetInstance()->ResumeSound(); }

void GSRobotSelectMenu::HandleEvents() { }

void GSRobotSelectMenu::HandleKeyEvents(SDL_Event& e) { }

void GSRobotSelectMenu::HandleTouchEvents(SDL_Event& e) {
    for (auto& button : m_listButton) {
        if (button->HandleTouchEvent(&e)) {
            break;
        }
    }
}

void GSRobotSelectMenu::HandleMouseMoveEvents(int x, int y) { }

