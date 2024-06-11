#include <string>
#pragma once

enum EAppliactaionState
{
	ApplicationStateNone,
	Run,
	Running,
	Exit
};
class GameManager
{
public:
	GameManager();
	~GameManager();

public:
	void Update();
	void Render();
	void Finalize();
	
public:
	void ChangeStateApplication(EAppliactaionState state);
	std::string StateApplicationToString(EAppliactaionState state);
public:
	EAppliactaionState StateApplication;

private:
	class InputHandler* _inputHandler = nullptr;
};

