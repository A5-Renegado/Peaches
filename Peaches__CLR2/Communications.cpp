#include "stdafx.h"
#include "Communications.h"

void myTestFunc()
{
	Communications^ TestComms = gcnew Communications();
	TestComms->testFunc();
}

void Communications::operator()(Kinect_ImProc *myKinect)
{
	kinectInfo = myKinect;
	listenToPort();
	return;
}

void Communications::testFunc()
{
	//kinectInfo = myKinect;
	listenToPort();
	return;
}

void Communications::listenToPort()
{
	int i = 0;
	while (1)
	{
		if (i % 100000000 == 0)
		{
			std::cout << i << " Testing My new Thread" << std::endl;
		}
		i++;
		if (!ok)
		{
			status = commandHalt();
		}
		else if (moving)
		{

		}
		else if (!open && psensors && atDeposit)
		{
			status = commandOpen();
		}
		else if (!open && psensors)
		{
			status = commandSetDirectionM1(true);
			status = commandSetDirectionM2(true);
			status = commandSetDirectionM3(true);
			status = commandSetCountsM1(0);
			status = commandSetCountsM2(0);
			status = commandSetCountsM3(0);
			status = commandExecuteAction();
		}
		else if (open && psensors && atPeach && kinectInfo->thereisapeach)
		{
			status = commandClose();
		}
		else if (kinectInfo->thereisapeach)
		{
			status = commandSetDirectionM1(true);
			status = commandSetDirectionM2(true);
			status = commandSetDirectionM3(true);
			status = commandSetCountsM1(0);
			status = commandSetCountsM2(0);
			status = commandSetCountsM3(0);
			status = commandExecuteAction();
		}
		else
		{
			status = commandSetDirectionM1(true);
			status = commandSetDirectionM2(true);
			status = commandSetDirectionM3(true);
			status = commandSetCountsM1(0);
			status = commandSetCountsM2(0);
			status = commandSetCountsM3(0);
			status = commandExecuteAction();
		}
	}
	return;
}

int Communications::commandOpen()
{
	return 0;
}
int Communications::commandClose()
{
	return 0;
}
int Communications::commandSetDirectionM1(bool left)
{
	return 0;
}
int Communications::commandSetDirectionM2(bool left)
{
	return 0;
}
int Communications::commandSetDirectionM3(bool left)
{
	return 0;
}
int Communications::commandSetCountsM1(int numCounts)
{
	return 0;
}
int Communications::commandSetCountsM2(int numCounts)
{
	return 0;
}
int Communications::commandSetCountsM3(int numCounts)
{
	return 0;
}
int Communications::commandExecuteAction()
{
	return 0;
}
int Communications::commandHalt()
{
	return 0;
}