#include "GSCredit.h"
#include "GameStateMachine.h"
#include "ResourceManagers.h"
#include "Sound.h"
#include "Define.h" 

GSCredit::GSCredit() : GameStateBase(StateType::STATE_CREDIT), m_background(nullptr), m_closeButton(nullptr) { }

GSCredit::~GSCredit() { }

void GSCredit::Init() {
    Sound::GetInstance()->LoadSfx("button_clicked.mp3");
    // Set up background
    auto texture = ResourceManagers::GetInstance()->GetTexture("bg_info.tga");
    m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
    m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    m_background->Set2DPosition(0, 0);

    // Initialize close button
    texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
    m_closeButton = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
    m_closeButton->SetSize(50, 50);
    m_closeButton->Set2DPosition(SCREEN_WIDTH - m_closeButton->GetWidth() - 10, 10);
    m_closeButton->SetOnClick([this]() {
        GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
        Sound::GetInstance()->PlaySfx("button_clicked.mp3");
        });
}

void GSCredit::Exit() { }

void GSCredit::Pause() { }

void GSCredit::Resume() { }

void GSCredit::HandleEvents() { }

void GSCredit::HandleKeyEvents(SDL_Event& e) { }

void GSCredit::HandleTouchEvents(SDL_Event& e) {
    if (m_closeButton) {
        m_closeButton->HandleTouchEvent(&e);
    }
}

void GSCredit::HandleMouseMoveEvents(int x, int y) { }

void GSCredit::Update(float deltaTime) {
    if (m_background) m_background->Update(deltaTime);
    if (m_closeButton) m_closeButton->Update(deltaTime);
}

void GSCredit::Draw(SDL_Renderer* renderer) {
    if (m_background) m_background->Draw(renderer);
    if (m_closeButton) m_closeButton->Draw(renderer);
}
