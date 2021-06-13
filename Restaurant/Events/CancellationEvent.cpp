#include "CancellationEvent.h"


CancellationEvent::CancellationEvent(int eTime, int oID, ORD_TYPE oType) :Event(eTime, oID)
{
	TimeStep = eTime;
	OrdType = oType;

}


void CancellationEvent::Execute(Restaurant* pRest)
{
	pRest->CancelAction(TimeStep);
}