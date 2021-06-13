#include"Order.h"

Order::Order(int id, ORD_TYPE r_Type, int size, double price)
{
	ID = (id > 0 && id < 1000) ? id : 0;	//1<ID<999
	type = r_Type;
	status = WAIT;
	ordersize = size;
	totalMoney = price;
}

Order::~Order()
{
}

int Order::GetID()const
{
	return ID;
}

double Order::GettotalMoney()const
{
	return totalMoney;
}

double Order::GetExMony() const
{
	return ExMony;
}

int Order::Getordersize()const
{
	return ordersize;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::SetDistance(int d)
{
	Distance = d > 0 ? d : 0;
}

int Order::GetDistance()const
{
	return Distance;
}

int Order::GetArrTime()const
{
	return ArrTime;
}

void Order::SetArrTime(int a)
{
	ArrTime = a;
}

int Order::GetServTime()const
{
	return ServTime;
}

void Order::SetServTime(int s)
{
	ServTime = s;
}

int Order::GetFinishTime()const
{
	return FinishTime;
}

void Order::SetFinishTime(int f)
{
	FinishTime = f;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

double Order::getPriority()const
{
	double priority = 2 * (this->GettotalMoney() + Getordersize() - GetArrTime());
	return priority;
}

void Order::setPriority(double p)
{
	priority=p;
}

void Order::setExMony(double m)
{
	ExMony=m;
}

void Order::setTotalMoney(double tm)
{
	totalMoney=tm;
}

void Order::setType(ORD_TYPE ordtype)
{
	type = ordtype;
}

void Order::setAutoP(int ap)
{
	autoP=ap;
}

void Order::setVIPurg(int v)
{
	VIPurg = v;
}

int Order::GetWaitingPrd()const
{
	return WaitPrd;
}
int Order::GetServingPrd()const
{
	return ServePrd;
}

int Order::GetAutoP() const
{
	return autoP;
}

int Order::GetVIPurg() const
{
	return VIPurg;
}

void Order::setAssignedCook(Cook* C)
{
	AssignedCook = C;
}

void Order::setordersize(int so)
{
	ordersize = so;
}


Cook* Order::getAssignedCook()
{
	return AssignedCook;
}

void Order::setWaitPrd(int wp)
{
	WaitPrd=wp;
}

void Order::setServePrd(int sp)
{
	ServePrd=sp;
}
