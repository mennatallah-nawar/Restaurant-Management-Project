#pragma once

#include "..\Defs.h"

class Cook;

class Order
{

protected:
	int ID;               //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		 //order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int Distance;	   //The distance (in meters) between the order location and the resturant 

	double totalMoney;	                 //Total order money
	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times
	int ordersize;                     //No. of dishes in order
	Cook* AssignedCook;               //Pointer to the cook assigned for the order 
	double priority;                //For promoted normal orders or vip orders
	double ExMony;                 //For promoted normal orders or vip orders
	int autoP;                    //num of ticks after which a normal order becomes promoted
	int VIPurg;                    //num of ticks after which a vip order becomes urgent
	int WaitPrd;
	int ServePrd;

public:
	Order(int ID, ORD_TYPE r_Type, int size, double price);
	

	//void PromoteOrder(Restaurant* pRest);  //function that calls promote function in Rest

	virtual ~Order();


	//Getters
	int GetID() const;
	double GettotalMoney() const;
	double GetExMony() const;
	int Getordersize() const;
	ORD_TYPE GetType() const;
	int GetDistance() const;

	int GetArrTime() const;
	int GetServTime() const;
	int GetFinishTime() const;

	int GetWaitingPrd() const;
	int GetServingPrd() const;

	double getPriority() const;
	ORD_STATUS getStatus() const;

	int GetAutoP() const;
	int GetVIPurg() const;
	Cook* getAssignedCook();

	//Setters
	void SetDistance(int d);
	void SetArrTime(int a);
	void SetServTime(int s);
	void SetFinishTime(int f);
	void setStatus(ORD_STATUS s);
	void setType(ORD_TYPE);
	void setPriority(double);
	void setExMony(double);
	void setTotalMoney(double);
	void setAutoP(int);
	void setVIPurg(int v);
	void setAssignedCook(Cook* C);
	void setordersize(int);
	void setWaitPrd(int);
	void setServePrd(int);
	/*void SetServingPeriod();*/

};
