#include "ArrivalEvent.h"
#include "..\Rest\Order.h"
#include "..\Rest\Restaurant.h"
ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType):Event(eTime, oID)
{
	OrdType = oType;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1
	Order* newOrd=new Order(OrderID,OrdType, size, OrdMoney);
	newOrd->SetArrTime(EventTime);
	
	if(OrdType==TYPE_NRM)
	{
		pRest->addToNormalQueue(newOrd);
	}
	if(OrdType==TYPE_VGAN)
	{
		
		pRest->addToVeganQueue(newOrd);
	}
	if(OrdType==TYPE_VIP)
	{
		pRest->addToVIPQueue(newOrd);
	}
	
	
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phases 1&2
	/*Order* pOrd = new Order(OrderID,OrdType,size, OrdMoney);
	pRest->AddtoDemoQueue(pOrd);*/
}

void ArrivalEvent::setSize(int s)
{
	size=s;
}
void ArrivalEvent::setMony(double m)
{
	OrdMoney=m;
}

ORD_TYPE ArrivalEvent::getOrderType() const
{
	return OrdType;
}