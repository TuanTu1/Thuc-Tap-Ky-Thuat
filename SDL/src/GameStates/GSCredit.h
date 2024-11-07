#pragma once
#include "GameStateBase.h"
#include "Sprite2D.h"
#include "MouseButton.h"
#include <memory>

class GSCredit : public GameStateBase {
public:
    GSCredit();
    virtual ~GSCredit();

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
    std::shared_ptr<MouseButton> m_closeButton;
};
