#pragma once
#include "GameStateBase.h"
#include "Text.h"
#include "Sound.h"
#include "ResourceManagers.h"
#include "MouseButton.h"
#include "Robot.h"
#include "SelectedRobotManager.h"

class MouseButton;

class GSRobotSelectMenu : public GameStateBase {
public:
    GSRobotSelectMenu();
    ~GSRobotSelectMenu();

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
    std::shared_ptr<Robot> m_Robot;
    std::shared_ptr<Sprite2D> m_background;
    std::shared_ptr<Sprite2D> m_bulletTypeList;
    std::shared_ptr<Sprite2D> m_robotWindow1;
    std::shared_ptr<Sprite2D> m_robotWindow2;
    std::shared_ptr<Sprite2D> m_robot1;  // Robot image for window 1
    std::shared_ptr<Sprite2D> m_robot2;  // Robot image for window 2
    
    SDL_Color m_textColor = { 255, 255, 255 };
    std::shared_ptr<Text> m_textPlayer1;
    std::shared_ptr<Text> m_textPlayer2;
    
    std::list<std::shared_ptr<MouseButton>> m_listButton;
    std::shared_ptr<MouseButton> btnPrev1;
    std::shared_ptr<MouseButton> btnNext1;
    std::shared_ptr<MouseButton> btnPrev2;
    std::shared_ptr<MouseButton> btnNext2;
    std::shared_ptr<MouseButton> btnStart;
    std::vector<std::string> robotNames;
    int currentRobot1;  
    int currentRobot2; 

    std::vector<std::string> robotImagesWindow1;  
    std::vector<std::string> robotImagesWindow2;  

    void UpdateRobotDisplay();  
};
