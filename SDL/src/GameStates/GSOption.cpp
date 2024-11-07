#include "GSOption.h"
#include "ResourceManagers.h"

GSOption::GSOption() : GameStateBase(StateType::STATE_OPTION) { }

GSOption::~GSOption() { }

void GSOption::Init() {
    Sound::GetInstance()->LoadSfx("button_clicked.mp3");
    //load current sound and sfx state
    m_sfxEnabled = Sound::GetInstance()->IsSfxEnabled();
    m_musicEnabled = Sound::GetInstance()->IsMusicEnabled();

    // Load the background texture
    auto texture = ResourceManagers::GetInstance()->GetTexture("bg_option_menu.tga");
    m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
    m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    m_background->Set2DPosition(0, 0);

    // Load the robot selection window texture
    texture = ResourceManagers::GetInstance()->GetTexture("option_table.tga");
    m_Window = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
    m_Window->SetSize(600, 350);
    m_Window->Set2DPosition((SCREEN_WIDTH - m_Window->GetWidth()) / 2, (SCREEN_HEIGHT - m_Window->GetHeight()) / 2);

    // Get the center Y position for the buttons
    float centerY = m_Window->Get2DPosition().y + (m_Window->GetHeight() / 2);

    // Load font
    auto font = ResourceManagers::GetInstance()->GetFont("PlaymegamesReguler-2OOee.ttf", 28);

    // Create settings title text
    m_textSettings = std::make_shared<Text>("SETTINGS", font, m_textColor);
    m_textSettings->SetSize(140, 60); 
    m_textSettings->Set2DPosition(m_Window->Get2DPosition().x + (m_Window->GetWidth() / 2) - (m_textSettings->GetWidth() / 2),m_Window->Get2DPosition().y + 20); 

    // SFX button
    texture = ResourceManagers::GetInstance()->GetTexture(m_sfxEnabled ? "btn_sfx.tga" : "btn_sfx_off.tga");
    m_btnSfx = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
    m_btnSfx->SetSize(120, 120);
    // Set position for SFX button (middle of the left half)
    m_btnSfx->Set2DPosition(m_Window->Get2DPosition().x + (m_Window->GetWidth() / 4) - (m_btnSfx->GetWidth() / 2), centerY - (m_btnSfx->GetHeight() / 2));
    m_btnSfx->SetOnClick([this]() {
        m_sfxEnabled = !m_sfxEnabled; // Toggle SFX state
        Sound::GetInstance()->SetSfxEnabled(m_sfxEnabled);
        auto texture = ResourceManagers::GetInstance()->GetTexture(m_sfxEnabled ? "btn_sfx.tga" : "btn_sfx_off.tga");
        m_btnSfx->SetTexture(texture);
        Sound::GetInstance()->PlaySfx("button_clicked.mp3");
        });

    // Create text under the SFX button
    m_textSfx = std::make_shared<Text>("SFX", font, m_textColor);
    m_textSfx->SetSize(60, 25);
    m_textSfx->Set2DPosition(m_btnSfx->Get2DPosition().x + (m_btnSfx->GetWidth() / 2) - (m_textSfx->GetWidth() / 2),
        m_btnSfx->Get2DPosition().y + m_btnSfx->GetHeight() + 10);

    // Music button
    texture = ResourceManagers::GetInstance()->GetTexture(m_musicEnabled ? "btn_music.tga" : "btn_music_off.tga");
    m_btnMusic = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
    m_btnMusic->SetSize(120, 120);
    // Set position for Music button (middle of the right half)
    m_btnMusic->Set2DPosition(m_Window->Get2DPosition().x + (3 * m_Window->GetWidth() / 4) - (m_btnMusic->GetWidth() / 2), centerY - (m_btnMusic->GetHeight() / 2));
    m_btnMusic->SetOnClick([this]() {
        m_musicEnabled = !m_musicEnabled; // Toggle Music state
        Sound::GetInstance()->SetMusicEnabled(m_musicEnabled);
        auto texture = ResourceManagers::GetInstance()->GetTexture(m_musicEnabled ? "btn_music.tga" : "btn_music_off.tga");
        m_btnMusic->SetTexture(texture);
        Sound::GetInstance()->PlaySfx("button_clicked.mp3");
        });

    // Create text under the Music button
    m_textSound = std::make_shared<Text>("MUSIC", font, m_textColor);
    m_textSound->SetSize(100, 25);
    m_textSound->Set2DPosition(m_btnMusic->Get2DPosition().x + (m_btnMusic->GetWidth() / 2) - (m_textSound->GetWidth() / 2),
        m_btnMusic->Get2DPosition().y + m_btnMusic->GetHeight() + 10);

    // Initialize close button
    texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
    m_closeButton = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
    m_closeButton->SetSize(50, 50);
    m_closeButton->Set2DPosition(m_Window->Get2DPosition().x + m_Window->GetWidth() - m_closeButton->GetWidth() / 2 - 10,
        m_Window->Get2DPosition().y - m_closeButton->GetHeight() / 2 + 10);
    m_closeButton->SetOnClick([this]() {
        GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
        Sound::GetInstance()->PlaySfx("button_clicked.mp3");
        });
    m_listButton.push_back(m_closeButton);

    // Add buttons to the list
    m_listButton.push_back(m_btnSfx);
    m_listButton.push_back(m_btnMusic);
}

void GSOption::Exit() { }

void GSOption::Pause() { }

void GSOption::Resume() { }

void GSOption::HandleEvents() { }

void GSOption::HandleKeyEvents(SDL_Event& e) { }

void GSOption::HandleTouchEvents(SDL_Event& e) {
    for (auto button : m_listButton)
    {
        if (button->HandleTouchEvent(&e))
        {
            break;
        }
    }
}

void GSOption::HandleMouseMoveEvents(int x, int y) { }

void GSOption::Update(float deltaTime) {
    for (auto& button : m_listButton) {
        button->Update(deltaTime);
    }
}

void GSOption::Draw(SDL_Renderer* renderer) {
    m_background->Draw(renderer);
    m_Window->Draw(renderer);
    for (auto& button : m_listButton) {
        button->Draw(renderer);
    }

    // Draw the texts
    m_textSettings->Draw(renderer);
    m_textSfx->Draw(renderer);
    m_textSound->Draw(renderer);
}
