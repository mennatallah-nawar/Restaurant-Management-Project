#pragma once

#include"Event.h"
#include "..\Rest\Restaurant.h"

class CancellationEvent :public Event
{

public:
	ORD_TYPE OrdType;//Must be Normal
	int TimeStep;
public:
	CancellationEvent(int eTime, int oID, ORD_TYPE oType);
	virtual void Execute(Restaurant* pRest);

};


