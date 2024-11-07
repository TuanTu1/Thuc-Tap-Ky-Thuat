#include "GSMenu.h"
#include "ResourceManagers.h"
#include "MouseButton.h"
GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_GameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	Sound::GetInstance()->LoadSfx("button_clicked.mp3");
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_background->Set2DPosition(0, 0);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(50, 50);
	btnClose->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth() -10, 10);
	btnClose->SetOnClick([]() {
		exit(0);
		Sound::GetInstance()->PlaySfx("button_clicked.mp3");
		});
	m_listButton.push_back(btnClose);

	// Play button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_start.tga");
	std::shared_ptr<MouseButton> btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	btnPlay->SetSize(410, 121);
	btnPlay->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth()) / 2, (SCREEN_HEIGHT - btnPlay->GetHeight()) / 2 + SCREEN_HEIGHT / 12);
	btnPlay->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_ROBOT_MENU);
		Sound::GetInstance()->PlaySfx("button_clicked.mp3");
		});
	m_listButton.push_back(btnPlay);

	// Spacing between setting and help buttons
	int spaceBetweenButtons = 50; 

	// Setting button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_settings.tga");
	std::shared_ptr<MouseButton> btnOption = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnOption->SetSize(120, 120);
	btnOption->Set2DPosition((SCREEN_WIDTH - (2 * btnOption->GetWidth()) - spaceBetweenButtons) / 2,
		((SCREEN_HEIGHT - btnPlay->GetHeight()) / 2) + btnPlay->GetHeight() + spaceBetweenButtons + SCREEN_HEIGHT / 12);
	btnOption->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OPTION);
		Sound::GetInstance()->PlaySfx("button_clicked.mp3");
		});
	m_listButton.push_back(btnOption);

	// Credit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_help.tga");
	std::shared_ptr<MouseButton> btnCredit = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnCredit->SetSize(120, 120);
	btnCredit->Set2DPosition(btnOption->Get2DPosition().x + btnOption->GetWidth() + spaceBetweenButtons,
		((SCREEN_HEIGHT - btnPlay->GetHeight()) / 2) + btnPlay->GetHeight() + spaceBetweenButtons + SCREEN_HEIGHT / 12);
	btnCredit->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CREDIT);
		Sound::GetInstance()->PlaySfx("button_clicked.mp3");
		});
	m_listButton.push_back(btnCredit);

	// game title
	texture = ResourceManagers::GetInstance()->GetTexture("GameName.tga");
	m_GameName = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_GameName->SetSize(829, 353);
	m_GameName->Set2DPosition((SCREEN_WIDTH - m_GameName->GetWidth()) / 2, SCREEN_HEIGHT / 12);

	/// sound
	Sound::GetInstance()->StopSound();
	Sound::GetInstance()->LoadSound("cyberpunk-tohican-141620.mp3");
	Sound::GetInstance()->PlaySound("cyberpunk-tohican-141620.mp3");

}

void GSMenu::Exit()
{

}


void GSMenu::Pause()
{

	// button close
	Sound::GetInstance()->PauseSound();

}

void GSMenu::Resume()
{

}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(SDL_Event& e)
{
}

void GSMenu::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}

	m_GameName->Draw(renderer);
}
