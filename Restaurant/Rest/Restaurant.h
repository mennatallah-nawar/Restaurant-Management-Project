#pragma once

#include <fstream>
#include "Order.h"
#include "Cook.h"
#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include"..\Generic_DS\PriorityQueue.h"
#include "..\Generic_DS\LinkedList.h"
#include <cstdlib>



class Restaurant
{
private:
	GUI* pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	int currentTimeStep;
	int autoP;
	int VIP_waitingT;

	//Waiting orders
	Queue<Order*> NormalOrders;
	Queue<Order*> VeganOrders;
	PriorityQueue<Order*> VIPOrders;

	//Inservice orders
	Queue<Order*> InserviceOrders;
	Queue<Order*> NormalInservice;
	Queue<Order*> VeganInservice;
	Queue<Order*> VIPInservice;

	//Finished orders
	Queue<Order*>NormalFinished;
	Queue<Order*>VeganFinished;
	Queue<Order*>VIPFinished;
	Queue<Order*>TotalFinished;

	//Urgent Orders
	Queue<Order*>UrgOrd;

	//List of cooks
	LinkedList<Cook*> CooksList;         //list of available cooks
	LinkedList<Cook*> INbreakCooksList;  //list of in break cooks
	LinkedList<Cook*> InjCooksList;      //list of injured cooks
   
	//Adding number of cooks
	int numCooks;
	int numNormalCooks;
	int numVeganCooks;
	int numVIPCooks;
	int numInjuredCooks;

	//Adding number of events
	int numberArrivalEvents;
	int numberCancellationEvents;
	int numberPromotionEvents;
	int totalNumEvents;

	//Adding number of orders for Input file
	int numNormalOrders;
	int numVeganOrders;
	int numVIPOrders;
	int totalNumOrders;
	int auto_p;

	//counts for the purpose of printing data
	int NWTcount; //normal waiting order count
	int GWTcount; //vegan waiting order count
	int VWTcount; //VIP waiting order count
	int NFTcount; //normal finished order count
	int GFTcount; //vegan finished order count
	int VFTcount; //VIP finished order count
	int NCcount; // Normal cook count
	int GCcount; // Vegan cook count
	int VCcount; // VIP cook count


	//For the statistics part
	int totalFinishedOrders;
	int NumFinishedNormal;
	int NumFinishedVegan;
	int NumFinishedVIP;
	double AvgWait;
	double AvgServ;
	int numUrgentOrders;
	int numAutoPromOrders;
public:

	Restaurant();
	~Restaurant();

	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	void FillDrawingList();
	void Printdata();


	void FileLoading();
	void Save();        //function responsible for the output file

	void addToVIPQueue(Order* po);
	void addToNormalQueue(Order* po);
	void addToVeganQueue(Order* po);

	void CancelAction(int);

	//Promote&AutoPromote Functions (~Esraa)
	void PromoteAction(int,double);
	void AutoPromote(int);
	
	//Function that gets order at the current timestep  (~Esraa)
	Order* getOrder(int id);    

	//Functions used in output file (~Esraa)
	void getStatistics();
	void sortTotalFinishedOrders();
	

	//Assigning Order Criteria 
	Cook* CookToAssignNormal();    //(~Esraa)
	Cook* CookToAssignVegan();     //(~Esraa)
	Cook* CookToAssignVIP();      //(~Menna)


	//Checks for available cook at current timestep
	bool checkAvailableCook(Cook* c);

	void UpdateCooks();
	void Assigning();

	//Finish ORD effect (Mariam)
	void UpdateInServiceNormal(Queue<Order*>&);
	void UpdateInServiceVIP(Queue<Order*>&);
	void UpdateInServiceVegan(Queue<Order*>&);
	void UpdateTotalFinished(Queue<Order*>);
	void FinishCooks(LinkedList<Cook*>&);
	void InjuryHandling(LinkedList<Cook*>);

	//Assign urgent orders 
	void AssignUrgentOrder(int);
};