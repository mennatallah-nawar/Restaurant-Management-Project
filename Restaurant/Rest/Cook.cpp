#include "Cook.h"



Cook::Cook()
{
	BTS=RTS=orders=0;
	RstPrd=InjProp=0;
	finshtimeofCurOrd=RequiredNoOfOrders=BreakDuration=0;
}


Cook::~Cook()
{
}


int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}

int Cook::getBreakDuration()
{
	return BreakDuration;
}

int Cook::getRequiredNoOfOrders()
{
	return RequiredNoOfOrders;
}

int Cook::getSpeed()
{
	return speed;
}
C_STATUS Cook::getstatus() const
{
	return status;
}

void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}

void Cook::setBreakDuration(int bd)
{
	BreakDuration = bd;
}

void Cook::setRequiredNoOfOrders(int r)
{
	RequiredNoOfOrders = r;
}
void Cook::setSpeed(int s)
{
	speed = s;
}

void Cook::setstatus(C_STATUS cs)
{
	status = cs;
}

void Cook::setfinshtimeofCurOrd(int x)
{
	finshtimeofCurOrd = x;
}

int Cook::getfinshtimeofCurOrd()
{
	return finshtimeofCurOrd;
}

void Cook::setInjProp(double p)
{
	InjProp = p;
}
void Cook::setRstPrd(int rp)
{
	RstPrd = rp;
}

void Cook::SetCurOrder(Order* order)
{
	CurOrder = order;
}

Order* Cook::GetCurOrder()
{
	return CurOrder;
}

void Cook::Setorders(int O)
{
	orders = O;
}

int Cook::Getorders()
{
	return orders;
}

void Cook::SetBTS(int bts)
{
	BTS = bts;
}

int Cook::GetBTS()
{
	return BTS;
}

void Cook::updatestatus()
{
	if (Getorders() == getRequiredNoOfOrders())
	{
		setstatus(INbreak);

	}
	else if (Getorders() != getRequiredNoOfOrders() && GetCurOrder())
	{
		setstatus(Busy);
	}
	else
	{
		setstatus(Av);
	}

}

/*bool Cook::checkAvailibility(int timestep)
{
	if(status == IDLE && timestep==currentTS)
		return true;
	return false;
		
}*/

double Cook::GetInjProp()
{
	return InjProp;
}

void Cook::SetRTS(int n)
{
	RTS = n;
}

int Cook::GetRTS()
{
	return RTS;
}

int Cook::GetRstPrd()
{
	return RstPrd;
}