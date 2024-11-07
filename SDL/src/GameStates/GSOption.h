#pragma once
#include "GameStateBase.h"
#include "Sprite2D.h"
#include "MouseButton.h"
#include "GameObject/Sound.h"
#include "Text.h"
#include <vector>

class GSOption : public GameStateBase {
public:
    GSOption();
    virtual ~GSOption();

    void Init() override;
    void Exit() override;
    void Pause() override;
    void Resume() override;

    void HandleEvents() override;
    void HandleKeyEvents(SDL_Event& e) override;
    void HandleTouchEvents(SDL_Event& e) override;
    void HandleMouseMoveEvents(int x, int y) override;
    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;

private:
    std::shared_ptr<Sprite2D> m_background;
    std::shared_ptr<Sprite2D> m_Window;
    std::shared_ptr<MouseButton> m_btnSfx;
    std::shared_ptr<MouseButton> m_btnMusic;
    std::shared_ptr<MouseButton> m_closeButton;
    std::vector<std::shared_ptr<MouseButton>> m_listButton; 

    SDL_Color m_textColor = { 255, 255, 255 };
    std::shared_ptr<Text> m_textSfx;
    std::shared_ptr<Text> m_textSound;
    std::shared_ptr<Text> m_textSettings;

    bool m_sfxEnabled = true;
    bool m_musicEnabled = true;
};


