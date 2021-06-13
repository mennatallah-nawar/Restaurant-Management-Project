#pragma once
#include "Event.h"
#include"../Rest/Restaurant.h"

class PromotionEvent : public Event
{
	//ORD_TYPE OrdType;
	double ExMony;

	int AutoP;      //num of ticks after which an order is automatically promoted
	int VIP_WT;     // num of ticks after which a VIP order becomes an urgent order
public:
	PromotionEvent(int eTime, int O_id, double M);
	virtual void Execute(Restaurant* pRest);

	//setters
	void setExMony(double);
	void setAutoP(int);
	void setVIP_WT(int);

	//getters
	int getAutoP() const;
	int getVIP_WT() const;
};

