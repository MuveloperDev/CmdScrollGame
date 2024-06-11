#include "GameManager.h"
#include "Util.h"
#include "Log.h"
#include "InputHandler.h"

GameManager::GameManager() : StateApplication(EAppliactaionState::ApplicationStateNone), _inputHandler(new InputHandler)
{
	Log::Complete("[ Allocated GameManager ]");
	ChangeStateApplication(Run);
	Util& util = Util::GetInstance();
	util.CacheGM(*this);
}

GameManager::~GameManager()
{
	Log::Complete("[ Deallocated GameManager ]");
}

void GameManager::Update()
{
	_inputHandler->Update();
	if (EInputState::ESC == _inputHandler->GetInputState())
	{
		Util& util = Util::GetInstance();
		util.ExitApplication();
	}
}

void GameManager::Render()
{
	Util& util = Util::GetInstance();
	util.Clear();
}

void GameManager::Finalize()
{
	Log::Complete("[ Finalize GameManager ]");
	delete _inputHandler;

	_inputHandler = nullptr;
}

void GameManager::ChangeStateApplication(EAppliactaionState state)
{
	Log::Complete("Changed Application State1 - [ " + StateApplicationToString(StateApplication) + " ] /" + StateApplicationToString(state));
	if (state == StateApplication)
		return;

	StateApplication = state;
	Log::Complete("Changed Application State - [ " + StateApplicationToString(StateApplication) + " ]");
}

std::string GameManager::StateApplicationToString(EAppliactaionState state)
{
	std::string result = "";
	switch (state)
	{
	case InputNone:
		result = "NONE";
		break;
	case Run:
		result = "RUN";
		break;
	case Running:
		result = "RUNNING";
		break;
	case Exit:
		result = "EXIT";
		break;
	}

	if (true == result.empty())
	{
		Log::Error("StateApplicationToString - result is empty");
	}
	return result;
}
