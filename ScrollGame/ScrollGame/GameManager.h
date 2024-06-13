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
private:
	void AllocateClasses();

public:
	void Update();
	void Render();
	void Finalize();
	
public:
	void ChangeStateApplication(EAppliactaionState state);
	void ExitApplication();
	void SetConsoleSize(int width, int height);
	void GetConsoleSize(int& width, int& height);
	void SetConsoleWindow();
	std::string StateApplicationToString(EAppliactaionState state);


public:
	EAppliactaionState StateApplication;

private:
	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;
private:
	class InputHandler* _inputHandler = nullptr;
	class Map* _map = nullptr;
	
};

