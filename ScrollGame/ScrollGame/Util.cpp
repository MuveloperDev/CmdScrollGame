#include "Util.h"
#include "Log.h"
#include "GameManager.h"

void Util::Clear()
{
	system("cls");
}

void Util::ExitApplication()
{
	if (nullptr == gm)
	{
		Log::Error("ExitApplacation - [ GameManager is null. ]");
		return;
	}
	gm->ChangeStateApplication(Exit);
}

void Util::CacheGM(GameManager& inGM)
{
	gm = &inGM;
}
