#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancellationEvent.h"
#include "..\Events\PromotionEvent.h"




Restaurant::Restaurant()
{
	pGUI = NULL;
	autoP=VIP_waitingT=numAutoPromOrders=0;
	numberArrivalEvents = numberCancellationEvents = numberPromotionEvents = 0;
	numNormalOrders = numVeganOrders = numVIPOrders = 0;
	numUrgentOrders=0;
	NWTcount = GWTcount = VWTcount = 0;
	NFTcount = GFTcount = VFTcount = 0;
	totalNumOrders=0; totalNumEvents=0;
	numNormalCooks = numVeganCooks = numVIPCooks = 0;
	NCcount = GCcount = VCcount = 0;
	numInjuredCooks=0;
	numNormalCooks = 0;
	currentTimeStep=0;
	auto_p=0;
	AvgWait=AvgServ=0;
	totalFinishedOrders=NumFinishedVIP=NumFinishedVegan=NumFinishedNormal=0;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE mode = pGUI->getGUIMode();


	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
	{
		FileLoading();
	pGUI->PrintMessage("Reading Input File");
	while (!EventsQueue.isEmpty())	//as long as events queue is not empty yet
	{
		
		//part a
		getOrder(currentTimeStep);
		Assigning();
		Printdata();
		UpdateCooks();
		FinishCooks(CooksList);
		AutoPromote(currentTimeStep);
		AssignUrgentOrder(currentTimeStep);
		//InjuryHandling(CooksList);
		UpdateInServiceNormal(NormalOrders);
		UpdateInServiceVegan(InserviceOrders);
		UpdateInServiceVIP(InserviceOrders);
		UpdateTotalFinished(InserviceOrders);
		pGUI->waitForClick();
		currentTimeStep++;
		ExecuteEvents(currentTimeStep);
		FillDrawingList();
		pGUI->UpdateInterface();
		pGUI->ResetDrawingList();
	}

	pGUI->PrintMessage("generation done, click to END program");
	Save();
	pGUI->waitForClick();}
		break;
	case MODE_STEP: 
	{
		FileLoading();
		pGUI->PrintMessage("Reading Input File");
		while (!EventsQueue.isEmpty())	//as long as events queue is not empty yet
		{
			getOrder(currentTimeStep);
			Assigning();
			Printdata();
			UpdateCooks();
			FinishCooks(CooksList);
			AutoPromote(currentTimeStep);
			AssignUrgentOrder(currentTimeStep);
			//InjuryHandling(CooksList);
			UpdateInServiceNormal(NormalOrders);
			UpdateInServiceVegan(InserviceOrders);
			UpdateInServiceVIP(InserviceOrders);
			UpdateTotalFinished(InserviceOrders);
			Sleep(1000);
			currentTimeStep++;
			ExecuteEvents(currentTimeStep);
			FillDrawingList();
			pGUI->UpdateInterface();
			pGUI->ResetDrawingList();
		}

		pGUI->PrintMessage("generation done, click to END program");
		Save();
		pGUI->waitForClick();

	}
		break;
	case MODE_SLNT:
	{
		FileLoading();
		pGUI->PrintMessage("Reading Input File");
		while (!EventsQueue.isEmpty())	//as long as events queue is not empty yet
		{
			
			getOrder(currentTimeStep);
			Assigning();
			UpdateCooks();
			FinishCooks(CooksList);
			AutoPromote(currentTimeStep);
			AssignUrgentOrder(currentTimeStep);
			//InjuryHandling(CooksList);
			UpdateInServiceNormal(NormalOrders);
			UpdateInServiceVegan(InserviceOrders);
			UpdateInServiceVIP(InserviceOrders);
			UpdateTotalFinished(TotalFinished);
			Sleep(100);
			currentTimeStep++;
			ExecuteEvents(currentTimeStep);
			pGUI->UpdateInterface();
			pGUI->ResetDrawingList();
		}

		pGUI->PrintMessage("generation done, click to END program");
		Save();
		pGUI->waitForClick();
	}
		break;
	default:
		break;
	};

}

//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event* pE;
	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current timestep
			return;

		pE->Execute(this);          //executes the event
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;					//deallocate event object from memory
	}
}


Restaurant::~Restaurant()
{
	if (pGUI)
		delete pGUI;
}

void Restaurant::FillDrawingList()
{
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);
	/////////////////////////////////////////////////////////////////////////////////////////
	//normal orders
	Order* po;
	int size = 0;
	NWTcount = 0;
	Order** Normal_Orders_Array = NormalOrders.toArray(size);
	NWTcount=NWTcount+size;
	for (int i = 0; i < size; i++)
	{
		
		po = Normal_Orders_Array[i];
		pGUI->AddToDrawingList(po);
		
	}
	//vegan orders
	GWTcount = 0;
	Order** Vegan_Orders_Array = VeganOrders.toArray(size);
	GWTcount =GWTcount+size;
	for (int i = 0; i < size; i++)
	{
		po = Vegan_Orders_Array[i];
		pGUI->AddToDrawingList(po);
		
	}
	//vip orders
	VWTcount = 0;
	Order** VIP_Orders_Array = VIPOrders.toArray(size);
    VWTcount=VWTcount+size;
	for (int i = 0; i < size; i++)
	{
		po = VIP_Orders_Array[i];
		pGUI->AddToDrawingList(po);
		
	}
	//inservice orders
	Order* poS;
	int sizeS = 0;
	Order** Inservice_Orders_Array = InserviceOrders.toArray(sizeS);
	for (int i = 0; i < sizeS; i++)
	{
		poS = Inservice_Orders_Array[i];
		pGUI->AddToDrawingList(poS);
	}
	
	Order* poF;
	int sizeF = 0;
	//NFTcount = 0;
	Order** NFinished_Orders_Array = NormalFinished.toArray(sizeF);
	//NFTcount+=sizeF;
	for (int i = 0; i < sizeF; i++)
	{
		poF = NFinished_Orders_Array[i];
		pGUI->AddToDrawingList(poF);
		
	}
	//GFTcount = 0;
	Order** VFinished_Orders_Array = VeganFinished.toArray(sizeF);
	//GFTcount=GFTcount+sizeF;
	for (int i = 0; i <sizeF; i++)
	{
		poF = VFinished_Orders_Array[i];
		pGUI->AddToDrawingList(poF);
	
	}
	//VFTcount = 0;
	Order** VIPFinished_Orders_Array = VIPFinished.toArray(sizeF);
	//VFTcount=VFTcount+sizeF;
	for (int i = 0; i < sizeF; i++)
	{
		poF = VIPFinished_Orders_Array[i];
		pGUI->AddToDrawingList(poF);
		
	}

	int sizeCook = 0;
	Cook** CookArr = CooksList.toArray(sizeCook);
	for (int i = 0; i < sizeCook; i++)
	{
		pGUI->AddToDrawingList(CookArr[i]);
	}
}
void Restaurant::Printdata()
{
	std::string currentTS = std::to_string(currentTimeStep);
	std::string numNormalOrd = std::to_string(NWTcount);
	std::string numVeganOrd = std::to_string(GWTcount);
	std::string numVIPOrd = std::to_string(VWTcount);
	std::string numNCooks = std::to_string(NCcount);
	std::string numGCooks = std::to_string(GCcount);
	std::string numVCooks = std::to_string(VCcount);
	std::string numFN = std::to_string(NumFinishedNormal);
	std::string numFG = std::to_string(GFTcount);
	std::string numFV = std::to_string(VFTcount);
	pGUI->PrintMessage("TS" + currentTS);
	pGUI->PrintWTorders("Normal Waiting Order:" + numNormalOrd + " , " + "Vegan Waiting Order:" + numVeganOrd + " , " + "VIP Waiting Order:" + numVIPOrd);
	//if (Av && !INbreak && !InRest &&!Busy) {
		pGUI->Printcooks("Normal cooks:" + numNCooks + " , " + "Vegan cooks:" + numGCooks + " , " + "VIP cooks:" + numVCooks);
	//}
	//else
		//	pGUI->Printcooks("Normal cooks:0 ,Vegan cooks:0 ,VIP cooks:0");
	pGUI->PrintFTorders("Normal Served Order:" + numFN + " , " + "Vegan Served Order:" + numFG + " , " + "VIP Served Order:" + numFV);
}
void Restaurant::FileLoading()
{
	string fileName;
	pGUI->PrintMessage("Please enter file name you want to open");
	fileName = pGUI->GetString() + ".txt";
	ifstream file;
	file.open(fileName, ios::in);
	if (file.is_open())
	{
		int noN, noG, noV;
		int SN_min, SN_max, SG_min, SG_max, SV_min, SV_max;
		int BO, BN_min, BN_max, BG_min, BG_max, BV_min, BV_max;
		double InjProp; 
		int RstPrd;
		int AutoP; 
		int VIP_WT;
		int M;
		char eventLetter;
		file >> noN;
		numNormalCooks = noN;
		NCcount = noN; //for printing data

		

		file >> noG;
		numVeganCooks = noG;
		GCcount = noG;

		file >> noV;
		numVIPCooks = noV;
		VCcount = noV;

		numCooks = numNormalCooks + numVeganCooks + numVIPCooks;

		file >> SN_min >> SN_max >> SG_min >> SG_max >> SV_min >> SV_max;
		file >> BO >> BN_min >> BN_max >> BG_min >> BG_max>> BV_min >> BV_max;
		file>>InjProp >> RstPrd;
		file >> AutoP >> VIP_WT;
		file >> M;

		autoP=AutoP;
		VIP_waitingT=VIP_waitingT;
		int startVeganID=noN+1; 
		for (int i = 0;i < noN;i++)
		{
			Cook* NC = new Cook();
			double SN = rand() % SN_max + SN_min;   //generating a random number between SN_min & SN_max
			NC->setSpeed(SN);
			double BN = rand() % BN_max + BN_min;  //generating a random number between BN_min & BN_max
			NC->setBreakDuration(BN);
		    NC->setType(TYPE_NRM); NC->setstatus(Av);
		    NC->setRequiredNoOfOrders(BO);
			NC->setID(i + 1);
			NC->setInjProp(InjProp);
			NC->setRstPrd(RstPrd);
			CooksList.InsertEnd(NC);
			
		}
	
		for (int i = 0;i<noG;i++)
		{
			Cook* GC = new Cook();
			double SG = rand() % SG_max + SG_min;   //generating a random number between SG_min & SG_max 
			GC->setSpeed(SG);
			double BV = rand() % BV_max + BV_min;  //generating a random number between BV_min & BV_max
			GC->setBreakDuration(BV);
		    GC->setType(TYPE_VGAN); GC->setstatus(Av);
		    GC->setRequiredNoOfOrders(BO);
		    GC->setID(i + startVeganID);
		    GC->setInjProp(InjProp);
		    GC->setRstPrd(RstPrd);
			CooksList.InsertEnd(GC);
			
		}

	    int startVIPID=noG+noN+1;
		for (int i = 0;i < noV;i++)
		{
		    Cook* VC = new Cook();
			double SV = rand() % SV_max + SV_min;   //generating a random number between SV_min & SV_max
			VC->setSpeed(SV);
			double BG = rand() % BG_max + BG_min;  //generating a random number between BG_min & BG_max
			VC->setBreakDuration(BG);
		    VC->setRequiredNoOfOrders(BO);
		    VC->setType(TYPE_VIP); VC->setstatus(Av);
			VC->setID(i + startVIPID);
			VC->setInjProp(InjProp);
			VC->setRstPrd(RstPrd);
			CooksList.InsertEnd(VC);
			
		}

		// LOADING EVENTS

		char orderType;
		int timeStep;
		int ID;
		int size;
		int mony;
		int ExMony;



		for (int i = 0;i < M;i++)
		{
			file >> eventLetter;
			switch (eventLetter)
			{
			case 'R':
			{
				file >> orderType;
				file >> timeStep;
				file >> ID;
				file >> size >> mony;
				if (orderType == 'N')
				{
					ArrivalEvent* AE = new ArrivalEvent(timeStep, ID, TYPE_NRM);
					AE->setSize(size);
					AE->setMony(mony);
					EventsQueue.enqueue(AE);
					numNormalOrders++;
					totalNumOrders++;
				}
				else if (orderType == 'G')
				{
					ArrivalEvent* AE = new ArrivalEvent(timeStep, ID, TYPE_VGAN);
					AE->setSize(size);
					AE->setMony(mony);
					EventsQueue.enqueue(AE);
					numVeganOrders++;
					totalNumOrders++;
				}
				else
				{
					ArrivalEvent* AE = new ArrivalEvent(timeStep, ID, TYPE_VIP);
					AE->setSize(size);
					AE->setMony(mony);
					EventsQueue.enqueue(AE);
					numVIPOrders++;
					totalNumOrders++;
				}
				numberArrivalEvents++;
			}
			break;
			case 'X':
			{
				file >> timeStep;
				file >> ID;
				CancellationEvent* CE = new CancellationEvent(timeStep, ID, TYPE_NRM);
				EventsQueue.enqueue(CE);
				numberCancellationEvents++;
				totalNumOrders--;
			}
			break;
			case 'P':
			{
				file >> timeStep;
				file >> ID;
				file >> ExMony;
				PromotionEvent* PE = new PromotionEvent(timeStep, ID, TYPE_NRM);
				PE->setExMony(ExMony);
				EventsQueue.enqueue(PE);
				numberPromotionEvents++;
			}
			break;
			default:
				break;
			}
		}

	}


}


void Restaurant::Save()
{
	pGUI->PrintMessage("Saving, please enter filename: ");
	string fileName;
	fileName=pGUI->GetString() + ".txt";
	ofstream outFile;
	outFile.open(fileName, ios::out);
	if(outFile.is_open())
	{
		//Get number of finished orders
		int countFinished;
		Order** finishedordersArr=TotalFinished.toArray(countFinished);


		Queue<Order*> FinishedOrders;
		sortTotalFinishedOrders();
		
		outFile<<"FT"<<"\t"<<"ID"<<"\t"<<"AT"<<"\t"<<"WT"<<"\t"<<"ST"<<endl;
		while(!TotalFinished.isEmpty())
		{
			Order* od;
			TotalFinished.dequeue(od);
			outFile<<od->GetFinishTime()<<"\t"<<od->GetID()<<"\t"<<od->GetArrTime()<<"\t"<<od->GetWaitingPrd()<<" \t"<<od->GetServingPrd()<<endl;
			FinishedOrders.enqueue(od);
		}

		while(!FinishedOrders.isEmpty())
		{
			Order* od;
			FinishedOrders.dequeue(od);
			TotalFinished.enqueue(od);
		}
		getStatistics();
		outFile<<"Orders:"<<countFinished;
		outFile<<"[Norm:"<<NumFinishedNormal<<", Veg:"<<NumFinishedVegan<<", VIP:"<<NumFinishedVIP<<"]"<<endl;
		outFile<<"cooks:"<<numCooks<<"   [Norm:"<<numNormalCooks<<", Veg:"<<numVeganCooks<<", VIP:"<<numVIPCooks;
		outFile<<",  injured:"<<numInjuredCooks<<"]"<<endl;
		outFile<<"Avg Wait = "<<AvgWait<<",  Avg Serv = "<<AvgServ<<endl;
		outFile<<"Urgent orders: "<<numUrgentOrders<<",  Auto-promoted: "<<numAutoPromOrders<<endl;
		outFile.close();
	}
}




void  Restaurant::addToVIPQueue(Order* od)	//adds an order to the demo queue
{	// To Calculate The Periority Of The Order
	
	VIPOrders.enqueue(od, od->getPriority());
}

void  Restaurant::addToNormalQueue(Order* od)
{
	NormalOrders.enqueue(od);
}

void  Restaurant::addToVeganQueue(Order* od)
{
	VeganOrders.enqueue(od);
}

Order* Restaurant::getOrder(int id)
{
	int countNormal, countVegan, countVIP;

	Order* ord=NULL;

	Order**  arrayNormalOrders;
	arrayNormalOrders= NormalOrders.toArray(countNormal);

	Order** arrayVeganOrders= VeganOrders.toArray(countVegan);

	Order** arrayVIPOrders= VIPOrders.toArray(countVIP);

	for(int i=0; i<countNormal; i++)
	{
		if(arrayNormalOrders[i]->GetID() == id)
		{
			ord=arrayNormalOrders[i];
		}
	}

	for(int i=0; i<countVegan; i++)
	{
		if(arrayVeganOrders[i]->GetID() == id)
			ord=arrayVeganOrders[i];
	}

	for(int i=0; i<countVIP; i++)
	{
		if(arrayVIPOrders[i]->GetID() == id)
			ord=arrayVIPOrders[i];
	}
	
	return ord;
}

bool Restaurant::checkAvailableCook(Cook* c)
{
	if(c->getstatus()== Av)
		return true;
	return false;
}


void Restaurant::PromoteAction(int id,double em)
{
	Order* od;
	Queue<Order*> newQueue;

	if(NormalOrders.isEmpty())
	{
		return ;
	}

	NormalOrders.peekFront(od);
	if (od->GetID() == id)
	{
       NormalOrders.dequeue(od);
	   od->setExMony(em);
	   od->setTotalMoney(od->GettotalMoney() + em);
	   od->setType(TYPE_VIP);
	   
		VIPOrders.enqueue(od, od->getPriority());
		return ;
		//NormalOrders.peekFront(od);
	}

		while (!NormalOrders.isEmpty())
		{
			NormalOrders.dequeue(od);
			if (od->GetID() == id)
			{
				VIPOrders.enqueue(od, od->getPriority());
				 od->setExMony(em);
	             od->setTotalMoney(od->GettotalMoney() + em);
				od->setType(TYPE_VIP);
				return ;
			}
		else
			{
				newQueue.enqueue(od);
			}
		}

		while(!newQueue.isEmpty())
		{
			Order* od;
			newQueue.dequeue(od);
			NormalOrders.enqueue(od);
		}

}

void Restaurant::CancelAction(int id)
{

	Order* od;
	Queue<Order*> newQueue;

	if(NormalOrders.isEmpty())
	{
		return ;
	}

	NormalOrders.peekFront(od);
	if (od->GetID() == id)
	{
       NormalOrders.dequeue(od);
	   delete od;
		return ;
		//NormalOrders.peekFront(od);
	}

		while (!NormalOrders.isEmpty())
		{
			NormalOrders.dequeue(od);
			if (od->GetID() == id)
			{
				delete od;
				return ;
			}
		else
			{
				newQueue.enqueue(od);
			}
		}

		while(!newQueue.isEmpty())
		{
			Order* od;
			newQueue.dequeue(od);
			NormalOrders.enqueue(od);
		}

}

void Restaurant::AutoPromote(int TS)
{
	int countNormal;
	
	Order** NormalOrdersArray=NormalOrders.toArray(countNormal);
	for(int i=0; i<countNormal; i++)
	{
		if(TS >= NormalOrdersArray[i]->GetArrTime() + auto_p)
		{
			//NormalOrdersArray[i]->PromoteOrder(this);
			PromoteAction(NormalOrdersArray[i]->GetID(), NormalOrdersArray[i]->GetExMony());
			numAutoPromOrders++;
		}
	}
}

//To be used in output file 
void Restaurant::getStatistics()
{
	//1] get AvgWait, AvgServ

	int totalWait=0;
	int totalServ=0;
	int countNorm,countVeg, countVIP;

	Order** NormalArr=NormalFinished.toArray(countNorm);
	Order** VeganArr=VeganFinished.toArray(countVeg);
	Order** VIPArray=VIPFinished.toArray(countVIP);

	totalFinishedOrders=countNorm+countVeg+countVIP;

	for(int i=0;i<countNorm;i++)
	{
		totalWait+=NormalArr[i]->GetWaitingPrd();
		totalServ+=NormalArr[i]->GetServingPrd();
	}
	for(int i=0; i<countVeg;i++)
	{
		totalWait+=VeganArr[i]->GetWaitingPrd();
		totalServ+=VeganArr[i]->GetServingPrd();
	}
	for(int i=0;i<countVIP;i++)
	{
		totalWait+=VIPArray[i]->GetWaitingPrd();
		totalServ+=VIPArray[i]->GetServingPrd();
	}
	AvgWait=totalWait/totalFinishedOrders;
	AvgServ=totalServ/totalFinishedOrders;

	//2] Set total number of delivered orders
	NumFinishedNormal=countNorm;
	NumFinishedVegan=countVeg;
	NumFinishedVIP=countVIP;
}

//Function responsible for sorting total finished orders by serving prd (if they have same FT)
void Restaurant::sortTotalFinishedOrders()
{

	
	int count;
	Order** TotalFinishedArr=TotalFinished.toArray(count);
	for(int i=0;i<count - 1;i++)
	{
		if(TotalFinishedArr[i]->GetFinishTime() == TotalFinishedArr[i+1]->GetFinishTime())
		{
			if(TotalFinishedArr[i]->GetServingPrd() > TotalFinishedArr[i+1]->GetServingPrd())
			{
				Order* temp= TotalFinishedArr[i];
				TotalFinishedArr[i]=TotalFinishedArr[i+1];
				TotalFinishedArr[i+1]=temp;
			}
		}
	}

	while(!TotalFinished.isEmpty())
	{
		Order* od;
		TotalFinished.dequeue(od);
	}

	for(int i=0; i<count; i++)
	{
		TotalFinished.enqueue(TotalFinishedArr[i]);
	}
}



                            ////////////////////////////Responsible for VIP ORDERS Service Criteria////////////////////////////////


Cook* Restaurant::CookToAssignVIP()
{
	//VIP Orders can be serviced by VIP ,Normal or vegan Cooks

	int check = 0; 
	Cook* CookToAssign = NULL;
	int countCooks = 0;
	Cook** CooksArray = CooksList.toArray(countCooks);

	//First:Check the entire list for VIP Cooks
	for (int i = 0; i < countCooks; i++)
	{
		if (CooksArray[i]->GetType() == TYPE_VIP && CooksArray[i]->getstatus() == Av)
		{
			CookToAssign = CooksArray[i];
			check = 1;
			break;
		}
	}

	//Second:If VIP Cook wasn't found, check the list for Normal ones
	if (check == 0)
	{
		for (int i = 0; i < countCooks; i++)
		{
			if (CooksArray[i]->GetType() == TYPE_NRM && CooksArray[i]->getstatus() == Av)
			{
				CookToAssign = CooksArray[i];
				break;
			}
		}
	}

	//last:If VIP and Normal Cooks weren't found, check the list for Vegan ones
	if (check == 0)
	{
		for (int i = 0; i < countCooks; i++)
		{
			if (CooksArray[i]->GetType() == TYPE_VGAN && CooksArray[i]->getstatus() == Av)
			{
				CookToAssign = CooksArray[i];
				break;
			}
		}
	}

	return CookToAssign;
}


                              ////////////////////////////Responsible for NORMAL ORDERS Service Criteria////////////////////////////////


Cook* Restaurant::CookToAssignNormal()
{
   //Normal Orders can be serviced either by Normal Cooks or VIP cooks (if Normal not found)

	int check=0; //To help in knowing if Normal Cooks weren't found
	Cook* CookToAssign=NULL;
	int countCooks=0;
	Cook** CooksArray=CooksList.toArray(countCooks);

	//First:Check the entire list for Normal Cooks
	for(int i=0;i<countCooks;i++)
	{
		if(CooksArray[i]->GetType()==TYPE_NRM && CooksArray[i]->getstatus()==Av)
		{
			CookToAssign=CooksArray[i];
			check=1;
			break;
		}
	}

	//Second:If Normal Cook wasn't found, check the list for VIP ones
	if(check==0)
	{
		for(int i=0;i<countCooks;i++)
		{
			if(CooksArray[i]->GetType()==TYPE_VIP && CooksArray[i]->getstatus()==Av)
			{
				CookToAssign=CooksArray[i];
				break;
			}
		}
	}

	return CookToAssign;
}

                                   /////////////////////Responsobile for VEGAN ORDER Service Criteria////////////////////////////////////////

Cook* Restaurant::CookToAssignVegan()
{
	//Vegan Orders are ONLY serviced by Vegan Cooks
	int countCooks=0;
	Cook* CookToAssign=NULL;
	Cook** CooksArray=CooksList.toArray(countCooks);

	//Search for an available Vegan Cook
	for(int i=0;i<countCooks;i++)
	{
		if(CooksArray[i]->GetType()==TYPE_VGAN && CooksArray[i]->getstatus()==Av)
		{
			CookToAssign=CooksArray[i];
			break;
		}
	}

	return CookToAssign;
}



void Restaurant::UpdateCooks() //BREAK handling
{
	int size = 0;
	                 ////////////////////////////////UBDATE AVAILABLE COOKS////////////////////////////////


	Cook** CookArr = CooksList.toArray(size);
	for (int i = 0; i < size; i++)

		if (CookArr[i] && CookArr[i]->GetCurOrder() && !CookArr[i]->getstatus() == INbreak) //Check for busy cooks
		{
			if ((CookArr[i]->getfinshtimeofCurOrd() == CookArr[i]->Getorders()) && CookArr[i]->GetCurOrder()->getStatus() == DONE) //Check for cooks should take break
			{
				CookArr[i]->setstatus(INbreak);
				CookArr[i]->SetBTS(currentTimeStep);
				CookArr[i]->SetCurOrder(nullptr);
				CookArr[i]->Setorders(0);
				if (CookArr[i]->GetType() == TYPE_NRM)
				{
					numNormalCooks--;
				}
				else if (CookArr[i]->GetType() == TYPE_VGAN)
				{
					numVeganCooks--;
				}
				else
				{
					numVIPCooks--;
				}
				INbreakCooksList.InsertEnd(CookArr[i]); //Adding them to inbreak list & Removing in break cooks from available list 
				CooksList.Remove(CookArr[i]);
			}
		}

	                ////////////////////////////////UBDATE INBREAK COOKS////////////////////////////////


	Cook** CookinBreakArr = INbreakCooksList.toArray(size);
	for (int i = 0; i < size; i++)        //Check for cooks should go back to available list

		if (currentTimeStep - (CookinBreakArr[i]->GetBTS()) == CookinBreakArr[i]->getBreakDuration())
		{
			CooksList.InsertEnd(CookinBreakArr[i]);
			INbreakCooksList.Remove(CookinBreakArr[i]);
			CookinBreakArr[i]->setstatus(Av);
			if (CookArr[i]->GetType() == TYPE_NRM)
			{
				numNormalCooks++;
			}
			else if (CookArr[i]->GetType() == TYPE_VGAN)
			{
				numVeganCooks++;
			}
			else
			{
				numVIPCooks++;
			}
		}

		else if ((CookArr[i]->getfinshtimeofCurOrd() > CookArr[i]->Getorders()) && CookArr[i]->GetCurOrder()->getStatus() == DONE)
		{
			CookArr[i]->SetCurOrder(nullptr);
		}
}

void Restaurant::Assigning()  //Assign ORD Effect 
{
	Order* pOrd;
	int size = 0;
	Cook** CookArr = CooksList.toArray(size);

	                        ///////////////////////////////////Assigning VIP orders///////////////////////////////////

	while (VIPOrders.peekFront(pOrd) && pOrd->GetArrTime() <= currentTimeStep)            //while there is VIP orders in waiting list
	{
		if (!size) return;        //if there is no cooks available

		Cook* AvCook = CookToAssignVIP();

		if (AvCook)
		{
		
				VIPOrders.dequeue(pOrd);
				AvCook->SetCurOrder(pOrd);
				AvCook->Setorders(AvCook->Getorders() + 1);
				pOrd->setAssignedCook(AvCook);
				pOrd->SetServTime(currentTimeStep);
				pOrd->setWaitPrd(currentTimeStep - pOrd->GetArrTime());
				//pOrd->SetFinishTime(currentTimeStep + ceil(pOrd->Getordersize() / AvCook->getSpeed()));  //time step=No. of dishes /speed of cook
				pOrd->setServePrd(ceil(pOrd->Getordersize() / AvCook->getSpeed()));
				pOrd->SetFinishTime(pOrd->GetArrTime() + pOrd->GetWaitingPrd() + pOrd->GetServingPrd());
				pOrd->setStatus(SRV);
				InserviceOrders.enqueue(pOrd);
				CooksList.InsertEnd(CooksList.EraseFirstNode()->getItem());
				VCcount--;
				//break;                        
		
			
		}
	}

	                  ///////////////////////////////////Assigning Vegan Orders///////////////////////////////////



	while (VeganOrders.peekFront(pOrd) && pOrd->GetArrTime() <= currentTimeStep)  //while there is vegan orders in waiting list till
	{
		if (!size) return;
		Cook* AvailableVegCook=CookToAssignVegan();

		if(AvailableVegCook)
		{
				VeganOrders.dequeue(pOrd);
				AvailableVegCook->SetCurOrder(pOrd);
				AvailableVegCook->Setorders(AvailableVegCook->Getorders() + 1);
				pOrd->setAssignedCook(AvailableVegCook);
				pOrd->SetServTime(currentTimeStep);
				pOrd->setWaitPrd(currentTimeStep - pOrd->GetArrTime());
				//pOrd->SetFinishTime(currentTimeStep + ceil(pOrd->Getordersize() / AvailableVegCook->getSpeed()));
				pOrd->setServePrd(ceil(pOrd->Getordersize() / AvailableVegCook->getSpeed()));
				pOrd->SetFinishTime(pOrd->GetArrTime() + pOrd->GetWaitingPrd() + pOrd->GetServingPrd());
				pOrd->setStatus(SRV);
				InserviceOrders.enqueue(pOrd);
				CooksList.InsertEnd(CooksList.EraseFirstNode()->getItem());
				GCcount--;
				//break;
		}
	}



	                     ///////////////////////////////////Assigning Normal Orders///////////////////////////////////

	while (NormalOrders.peekFront(pOrd) && pOrd->GetArrTime() <= currentTimeStep)                       //while there is more normal orders in waiting list 
	{
		if (!size)return;
		Cook* AvNormOrVIPCook=CookToAssignNormal();

		if(AvNormOrVIPCook)
		{
				NormalOrders.dequeue(pOrd);
				AvNormOrVIPCook->SetCurOrder(pOrd);
				AvNormOrVIPCook->Setorders(AvNormOrVIPCook->Getorders() + 1);
				pOrd->setAssignedCook(AvNormOrVIPCook);
				pOrd->setWaitPrd(currentTimeStep - pOrd->GetArrTime());
				pOrd->SetServTime(currentTimeStep);
				//pOrd->SetFinishTime(currentTimeStep + ceil(pOrd->Getordersize() / AvNormOrVIPCook->getSpeed()));
				pOrd->setServePrd(ceil(pOrd->Getordersize() / AvNormOrVIPCook->getSpeed()));
				pOrd->SetFinishTime(pOrd->GetArrTime() + pOrd->GetWaitingPrd() + pOrd->GetServingPrd());
				pOrd->setStatus(SRV);
				InserviceOrders.enqueue(pOrd);
				CooksList.InsertEnd(CooksList.EraseFirstNode()->getItem());
				NCcount--;
				//break;
		}
	}

}


void Restaurant::UpdateInServiceNormal(Queue<Order*>& InserviceOrders)
{
	if (InserviceOrders.isEmpty())//Check if Inservice queue is empty
		return;

	int nOrders;//count of orders in inservice queue
	Order** currOrder = InserviceOrders.toArray(nOrders);
	//NumFinishedNormal = 0;
	for (int i = 0; i < nOrders; i++)
	{
		if (currOrder[i]->GetType() == TYPE_NRM && currOrder[i]->GetFinishTime()==currentTimeStep)//FinishTime already calculated when assigning the cook to the order
		{
			currOrder[i]->setStatus(DONE);
			NormalFinished.enqueue(currOrder[i]);
			//NumFinishedNormal ++;
		    
			//Removing the finished normal order from the array to be later removed from inservice queue
			int pos = i;
			for (int j = pos; j < nOrders - 1; j++)
				currOrder[j] = currOrder[j + 1];
		}
	}

	//Updating inservice queue after removing the finished orders
	while (!InserviceOrders.isEmpty())
	{
		Order* item;
		InserviceOrders.dequeue(item);
	}

	for (int i = 0; i < nOrders; i++)
	{
		InserviceOrders.enqueue(currOrder[i]);
	}
		
}

void Restaurant::UpdateInServiceVIP(Queue<Order*>& InserviceOrders)
{
	if (InserviceOrders.isEmpty())//Check if Inservice queue is empty
		return;

	int nOrders;//count of orders in inservice queue
	Order** currOrder = InserviceOrders.toArray(nOrders);
	for (int i = 0; i < nOrders; i++)
	{
		if (currOrder[i]->GetType() == TYPE_VIP && currOrder[i]->GetFinishTime() == currentTimeStep)//FinishTime already calculated when assigning the cook to the order
		{
			currOrder[i]->setStatus(DONE);
			VIPFinished.enqueue(currOrder[i]);
			NumFinishedVIP++;

			//Removing the finished normal order from the array to be later removed from inservice queue
			int pos = i;
			for (int j = pos; j < nOrders - 1; j++)
				currOrder[j] = currOrder[j + 1];
		}
	}

	//Updating inservice queue after removing the finished orders
	while (!InserviceOrders.isEmpty())
	{
		Order* item;
		InserviceOrders.dequeue(item);
	}

	for (int i = 0; i < nOrders; i++)
	{
		InserviceOrders.enqueue(currOrder[i]);
	}

}

void Restaurant::UpdateInServiceVegan(Queue<Order*>& InserviceOrders)
{
	if (InserviceOrders.isEmpty())//Check if Inservice queue is empty
		return;

	int nOrders = 0;//count of orders in inservice queue
	Order** currOrder = InserviceOrders.toArray(nOrders);
	for (int i = 0; i < nOrders; i++)
	{
		if (currOrder[i]->GetType() == TYPE_VGAN && currOrder[i]->GetFinishTime() == currentTimeStep)//FinishTime already calculated when assigning the cook to the order
		{
			currOrder[i]->setStatus(DONE);
			VeganFinished.enqueue(currOrder[i]);
			//NumFinishedVegan+=nOrders;

			//Removing the finished normal order from the array to be later removed from inservice queue
			int pos = i;
			for (int j = pos; j < nOrders - 1; j++)
				currOrder[j] = currOrder[j + 1];
		}
	}

	//Updating inservice queue after removing the finished orders
	while (!InserviceOrders.isEmpty())
	{
		Order* item;
		InserviceOrders.dequeue(item);
	}

	for (int i = 0; i < nOrders; i++)
	{
		InserviceOrders.enqueue(currOrder[i]);
	}

}

void Restaurant::UpdateTotalFinished(Queue<Order*> InserviceOrders)
{
	if (InserviceOrders.isEmpty())
		return;

	int nOrders = 0;
	//NFTcount = 0;
	Order** pOrd = InserviceOrders.toArray(nOrders);
	//NFTcount += nOrders;
	for (int i = 0; i < nOrders; i++)
	{
		if (pOrd[i]->GetFinishTime() == currentTimeStep)
		{
			pOrd[i]->setStatus(DONE);
			TotalFinished.enqueue(pOrd[i]);
			totalNumOrders++;
		}
	}
	

	//The following part is added by Esraa

	/*int count;
	Order** TotalFinishedArr=TotalFinished.toArray(count);
	for(int i=0;i<count;i++)
	{
		if(TotalFinishedArr[i]->GetFinishTime() == TotalFinishedArr[i+1]->GetFinishTime())
		{
			if(TotalFinishedArr[i]->GetServingPrd() > TotalFinishedArr[i+1]->GetServingPrd())
			{
				Order* temp= TotalFinishedArr[i];
				TotalFinishedArr[i]=TotalFinishedArr[i+1];
				TotalFinishedArr[i+1]=temp;
			}
		}
	}*/
}

void Restaurant::FinishCooks(LinkedList<Cook*>& CooksList)
{
	if (CooksList.isEmpty())
		return;

	int nCooks = 0;
	Cook** pCook = CooksList.toArray(nCooks);
	for (int i = 0; i < nCooks; i++)
	{
		if (pCook[i]->getstatus() == Busy && pCook[i]->getfinshtimeofCurOrd() == currentTimeStep)
		{
			pCook[i]->setstatus(Av);
			pCook[i]->SetCurOrder(nullptr);
			pCook[i]->updatestatus();
		}
	}
}

void Restaurant::InjuryHandling(LinkedList<Cook*> CooksList)
{
	if (CooksList.isEmpty())
		return;

	int check = 0;
	double R = 1+ (rand()%100);   //generating a random number between 1 and 100
	int nCooks = 0;
	Cook** pCook = CooksList.toArray(nCooks);
	if (R <= pCook[1]->GetInjProp())//pCook[1] ==> just to be able to get injury probability of cooks
	{
		for (int i = 0; i < nCooks; i++)
		{
			if (pCook[i]->getstatus() == Busy)
			{
				check = 1;
				numInjuredCooks++;
				/*pCook[i]->setstatus(InRest);*/
				InjCooksList.InsertEnd(pCook[i]); //or should I leave it in CooksList ?
				CooksList.Remove(pCook[i]);
				break;
			}
		}
	}

	
	int nInj;
	Cook** InjCook = InjCooksList.toArray(nInj);
	 
	if (check == 0) //There is no busy cook
	{
		for (int i = 0; i < nInj; i++)//Updating Injured Cooks
		{
			if (InjCook[i]->GetCurOrder()->GetFinishTime() == currentTimeStep)//Check if Cook finished currOrder
			{
				InjCook[i]->SetRTS(currentTimeStep);
				InjCook[i]->SetCurOrder(nullptr);
				InjCook[i]->setstatus(InRest);
			}

			if ((InjCook[i]->GetRTS() + InjCook[i]->GetRstPrd()) == currentTimeStep)//Check if cook finished rest period
			{
				InjCook[i]->setstatus(Av);
				InjCook[i]->setSpeed(InjCook[i]->getSpeed() * 2);
				InjCooksList.Remove(InjCook[i]);
				CooksList.InsertEnd(InjCook[i]);
			}
		}
	}

    if (check == 1) //There is a busy cook in cookslist
	{
		//Decreasing the speed of the cook to half
		InjCook[nInj]->setSpeed(InjCook[nInj]->getSpeed() / 2);
		
		//Changing the finish time of the current order
		InjCook[nInj]->GetCurOrder()->SetFinishTime(InjCook[nInj]->GetCurOrder()->GetServTime() + ceil(InjCook[nInj]->GetCurOrder()->Getordersize() / InjCook[nInj]->getSpeed()));

		//Updating Injured Cooks
		for (int i = 0; i < nInj - 1; i++)
		{
			if (InjCook[i]->GetCurOrder()->GetFinishTime() == currentTimeStep)//Check if Cook finished currOrde
			{
				InjCook[i]->SetRTS(currentTimeStep);
				InjCook[i]->SetCurOrder(nullptr);
				InjCook[i]->setstatus(InRest);
			}

			if ((InjCook[i]->GetRTS() + InjCook[i]->GetRstPrd()) == currentTimeStep)//Check if cook finished rest period
			{
				InjCook[i]->setstatus(Av);
				InjCook[i]->setSpeed(InjCook[i]->getSpeed() * 2);
				InjCooksList.Remove(InjCook[i]);
				numInjuredCooks--;
				CooksList.InsertEnd(InjCook[i]);
			}
		}
	}

	//Handeling urgent orders
	if (InjCooksList.isEmpty()) //Needs editing ??
		return;
	else  
	{
		for (int j = 0; j < nInj; j++)
		{
			if (InjCook[j]->getstatus() == InRest && InjCook[j]->GetCurOrder() != nullptr)
			{
				InjCook[j]->setSpeed(InjCook[j]->getSpeed() / 2);
			}

			if (InjCook[j]->Getorders() == InjCook[j]->getRequiredNoOfOrders())
			{
				InjCook[j]->setSpeed(InjCook[j]->getSpeed() * 2);
				InjCooksList.Remove(InjCook[j]);
				CooksList.InsertEnd(InjCook[j]);
			}
		}
		
	}

}

void Restaurant::AssignUrgentOrder(int TS)
{
	Cook* c1=CookToAssignNormal();
	Cook* c2 = CookToAssignVegan();
	Cook* c3 = CookToAssignVIP();
	if (CooksList.isEmpty() && c1->getstatus()==Av && c2->getstatus() == Av) {
		return;// if there are av cooks then no need for this function as VIP should be already assigned to that free cook
	}
	int UrgSize=0;
	Order** Urgent_Orders_Array = UrgOrd.toArray(UrgSize);
	for (int i = 0; i < UrgSize; i++) {

		if (Urgent_Orders_Array[i]->GetType() == TYPE_VIP && Urgent_Orders_Array[i]->getStatus() == WAIT && TS >= Urgent_Orders_Array[i]->GetVIPurg()) {
			bool dummy = false; //no available cooks
			if (!INbreakCooksList.isEmpty() && dummy==false) { //assign urgent order to cooks in inbreak
				int size = 0;
				Cook** CookinBreakArr = INbreakCooksList.toArray(size);
				for (int i = 0; i < size; i++) {
					CooksList.InsertEnd(CookinBreakArr[i]);
					INbreakCooksList.Remove(CookinBreakArr[i]);
					CookinBreakArr[i]->setstatus(Av);
					CookinBreakArr[i] = CookToAssignVIP();
					dummy = true;
				}
			}
			else if (INbreakCooksList.isEmpty() && !InjCooksList.isEmpty() && dummy==false) {//if no inbreak cooks, assign urgent order to cooks inrest
				int sizeinj = 0;
				Cook** CookinInjArr = InjCooksList.toArray(sizeinj);
				for (int i = 0; i < sizeinj; i++) {
					CooksList.InsertEnd(CookinInjArr[i]);
					INbreakCooksList.Remove(CookinInjArr[i]);
					CookinInjArr[i]->setstatus(Av);
					CookinInjArr[i] = CookToAssignVIP();
					dummy = true;
				}
			}
		}
	}
	
	
}
