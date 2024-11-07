#include "GameStateBase.h"
#include "GameStates/GSIntro.h"
#include "GSMenu.h"
#include "GSOption.h"
#include "GSPlay.h"
#include "GSRobotSelectMenu.h"
#include "GSCredit.h"

GameStateBase::GameStateBase(StateType stateType) : m_stateType(stateType)
{}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateType stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case StateType::STATE_INVALID:
		break;
	case StateType::STATE_INTRO:
		gs = std::make_shared<GSIntro>();
		//GSINTRO;
		break;
	case StateType::STATE_MENU:
		gs = std::make_shared<GSMenu>();
		//GSMENU
		break;
	case StateType::STATE_CREDIT:
		gs = std::make_shared<GSCredit>();
		//GSMENU
		break;
	case StateType::STATE_OPTION:
		gs = std::make_shared<GSOption>();
		//GSMENU
		break;
	case StateType::STATE_ROBOT_MENU:
		gs = std::make_shared<GSRobotSelectMenu>();
		//GSROBOTSELECTMENU
		break;
	case StateType::STATE_PLAY:
		gs = std::make_shared<GSPlay>();
		//GSPLAY
		break;
	default:
		break;
	}
	return gs;
}

StateType GameStateBase::GetGameStateType()
{
	return m_stateType;
}
