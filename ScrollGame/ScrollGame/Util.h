#include "Singleton.h"

#pragma once
class Util : public Singleton<Util>
{
	friend class Singleton<Util>;

public:
	void Clear();
	void ExitApplication();
	void CacheGM(class GameManager& inGM);
private:
	class GameManager* gm;
};

