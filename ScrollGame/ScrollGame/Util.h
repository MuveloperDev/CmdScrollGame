#include "Singleton.h"

#pragma once
class Util : public Singleton<Util>
{
	friend class Singleton<Util>;

public:
	void Clear();
};

