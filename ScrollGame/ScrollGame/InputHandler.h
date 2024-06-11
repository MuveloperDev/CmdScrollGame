#include <string>
#pragma once
enum EInputState
{
	InputNone,
	Up,
	Down,
	Left,
	Right,
	Enter,
	ESC
};
class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	void Update();
	void Render();
	
public:
	void UpdateInput();

public:
	EInputState GetInputState();

private:
	std::string EInputStateToString(EInputState state);

protected:
	bool _isInputKey;
	EInputState _currentState;
};

