#include "InputHandler.h"
//#include <iostream>
//#include <stdio.h>
//#include <stdint.h>
//#include <random>
#include <windows.h>
#include "Log.h"
InputHandler::InputHandler() : _isInputKey(false), _currentState(InputNone)
{
	Log::Complete("[ Allocated InputHandler ]");
}

InputHandler::~InputHandler()
{
	Log::Complete("[ Deallocated InputHandler ]");
}

void InputHandler::Update()
{
	UpdateInput();
}

void InputHandler::Render()
{
}

void InputHandler::UpdateInput()
{
	SHORT rightState = GetAsyncKeyState(VK_RIGHT);
	SHORT leftState = GetAsyncKeyState(VK_LEFT);
	SHORT uptState = GetAsyncKeyState(VK_UP);
	SHORT downState = GetAsyncKeyState(VK_DOWN);
	SHORT escapeState = GetAsyncKeyState(VK_ESCAPE);
	SHORT enterState = GetAsyncKeyState(VK_RETURN);
	bool isRight = (rightState & 0x8000) != 0;
	bool isLeft = (leftState & 0x8000) != 0;
	bool isUp = (uptState & 0x8000) != 0;
	bool isDown = (downState & 0x8000) != 0;
	bool isESC = (escapeState & 0x8000) != 0;
	bool isEnter = (enterState & 0x8000) != 0;

	if (isRight || isLeft || isUp || isDown || isESC || isEnter)
	{
		if (_isInputKey == false)
		{
			if (isRight)
			{
				_currentState = Right;
			}
			if (isLeft)
			{
				_currentState = Left;
			}
			if (isUp)
			{
				_currentState = Up;
			}
			if (isDown)
			{
				_currentState = Down;
			}
			if (isESC)
			{
				_currentState = ESC;
			}
			if (isEnter)
			{
				_currentState = Enter;
			}
			Log::LogMessage("Player Input = [ " + EInputStateToString(_currentState) + " ]");
		}
		_isInputKey = true;
		return;
	}
	if (false == _isInputKey)
		return;

	_currentState = EInputState::InputNone;
	_isInputKey = false;
}

EInputState InputHandler::GetInputState()
{
	return _currentState;
}

std::string InputHandler::EInputStateToString(EInputState state)
{
	switch (state)
	{
		case Up:
			return "Up";
		case Down:
			return "Down";
		case Left:
			return "Left";
		case Right:
			return "Right";
		case Enter:
			return "Enter";
		case ESC:
			return "ESC";
	}
	Log::Error("[ Invalid input type ]");
	return " [ Empty ] ";
}

