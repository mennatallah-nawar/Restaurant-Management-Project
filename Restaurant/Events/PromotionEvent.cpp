#include "PromotionEvent.h"
PromotionEvent::PromotionEvent(int eTime, int O_id, double M) :Event(eTime, O_id)
{
	ExMony = M;

}
void PromotionEvent::Execute(Restaurant* pRest)
{

	pRest->PromoteAction(OrderID, ExMony);

}

void PromotionEvent::setExMony(double m)
{
	ExMony = m;
}

void PromotionEvent::setAutoP(int ap)
{
	AutoP=ap;
}

void PromotionEvent::setVIP_WT(int wt)
{
	VIP_WT=wt;
}

int PromotionEvent::getAutoP() const
{
	return AutoP;
}

int PromotionEvent::getVIP_WT() const
{
	return VIP_WT;
}