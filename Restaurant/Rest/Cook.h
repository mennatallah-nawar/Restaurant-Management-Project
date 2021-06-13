#pragma once
#include "..\Defs.h"
#include"Order.h"

class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		//dishes it can prepare in one clock tick (in one timestep) speed=No. of dishes/time step

	//Adding Extra Members
	int BreakDuration;         //No. of time steps that cook take in break
	int RequiredNoOfOrders;   //No. of orders required before take break
	C_STATUS status;         //status of Cooks
	int finshtimeofCurOrd;  //the time step at which cook finish the current order

	//Adding Extra Members in Phase2
	double InjProp;         // probablity a busy cook gets injured
	int RstPrd;            // and the rest period respectively
	Order* CurOrder;      //Pointer to the current assigned order
	int orders;		     //No. of the orders that have been assigned to the cook
	int BTS;            //The timestep at which cook had break
	int RTS;           //The timestep at which cook had rest

public:
	Cook();
	virtual ~Cook();


	//Seters functions
	void setID(int);
	void setType(ORD_TYPE);
	void setBreakDuration(int);
	void setRequiredNoOfOrders(int);
	void setSpeed(int);
	void setstatus(C_STATUS);
	void setfinshtimeofCurOrd(int);
	void setInjProp(double);
	void setRstPrd(int);
	void SetCurOrder(Order*);
	void Setorders(int);
	void SetBTS(int);
	void SetRTS(int);

	//Getters functions
	int GetID() const;
	ORD_TYPE GetType() const;
	int getBreakDuration();
	int getRequiredNoOfOrders();
	int getSpeed();
	C_STATUS getstatus() const;
	int getfinshtimeofCurOrd();
	Order* GetCurOrder();
	int Getorders();
	int GetBTS();
	int GetRTS();
	int GetRstPrd();
	double GetInjProp();

	///////////////////////
	void updatestatus();

	//bool checkAvailibility(int);
	
};