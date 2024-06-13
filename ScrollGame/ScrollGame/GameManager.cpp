#include <iostream>
#include <windows.h>
#include "GameManager.h"
#include "Util.h"
#include "Log.h"
#include "InputHandler.h"
#include "Map.h"

GameManager::GameManager() : StateApplication(EAppliactaionState::ApplicationStateNone), 
_inputHandler(nullptr),
_map(nullptr)
{
	Log::Complete("[ Allocated GameManager ]");
	// set cmd window size
	SetConsoleWindow();

	ChangeStateApplication(Run);
	Util& util = Util::GetInstance();
	util.CacheGM(*this);
	util.Clear();
	AllocateClasses();
}

GameManager::~GameManager()
{
	Log::Complete("[ Deallocated GameManager ]");
}

void GameManager::AllocateClasses()
{
	_inputHandler = new InputHandler();
	_map = new Map();
}

void GameManager::Update()
{
	_inputHandler->Update();
	_map->Update();
	ExitApplication();
}

void GameManager::Render()
{
	//Util& util = Util::GetInstance();
	//util.Clear();
	COORD cur;
	cur.X = 0;
	cur.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
	_map->Render();
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

void GameManager::ExitApplication()
{
	if (EInputState::ESC == _inputHandler->GetInputState())
	{
		Util& util = Util::GetInstance();
		util.ExitApplication();
	}
}

void GameManager::SetConsoleSize(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
	std::string log = "Setted console window size [ width : " + std::to_string(width) + "  height : " + std::to_string(height) + " ]";
	Log::Complete(log);
}

void GameManager::GetConsoleSize(int& width, int& height)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	width = columns;
	height = rows;
}

void GameManager::SetConsoleWindow()
{
	// CMD 창 크기 설정
	SetConsoleSize(1020, 1020);

	// CMD 창의 너비와 높이 얻기
	GetConsoleSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// CMD 창 고정시키기
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style &= ~WS_MAXIMIZEBOX; // 최대화 버튼 비활성화
	style &= ~WS_SIZEBOX; // 크기 조절 비활성화
	SetWindowLong(consoleWindow, GWL_STYLE, style);

	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

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
