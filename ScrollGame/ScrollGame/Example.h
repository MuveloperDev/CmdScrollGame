#include "Singleton.h"

#pragma once
class Example : public Singleton<Example>
{
	friend class Singleton<Example>;
public:
	void DoSomthing();
};

