#include "GSIntro.h"
#include "ResourceManagers.h"
#include "Define.h"
#include "Sprite2D.h"
#define INTRO_TIME 2.5f
GSIntro::GSIntro() : GameStateBase(StateType::STATE_INTRO), m_time(0.0f)
{
}


GSIntro::~GSIntro()
{
}

void GSIntro::Init()
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("logo.tga");
	m_logo = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_logo->SetSize(500, 500);
	m_logo->Set2DPosition((float)(SCREEN_WIDTH - m_logo->GetWidth())/2 , (float)(SCREEN_HEIGHT - m_logo->GetHeight())/2);
	
	texture = ResourceManagers::GetInstance()->GetTexture("logo_bg.tga");
	m_logobg = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_logobg->SetSize(SCREEN_WIDTH,SCREEN_HEIGHT);
	m_logobg->Set2DPosition(0.0f, 0.0f);
}

void GSIntro::Exit()
{
}


void GSIntro::Pause()
{
}

void GSIntro::Resume()
{

}


void GSIntro::HandleEvents()
{
}

void GSIntro::HandleKeyEvents(SDL_Event& e)
{
}

void GSIntro::HandleTouchEvents(SDL_Event& e)
{
}

void GSIntro::HandleMouseMoveEvents(int x, int y)
{
}

void GSIntro::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > INTRO_TIME)
	{
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		m_time = 0;
	}
}

void GSIntro::Draw(SDL_Renderer* renderer)
{
	m_logobg->Draw(renderer);
	m_logo->Draw(renderer);
}
