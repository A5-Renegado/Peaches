#include "Kinect_ImProc.h"
public ref class Communications
{
public:
	Communications() {};
	~Communications() {};
	void operator()(Kinect_ImProc *myKinect);
	void testFunc();
private:
	Kinect_ImProc *kinectInfo;
	void listenToPort();
	System::IO::Ports::SerialPort myPort;

	int commandOpen();
	int commandClose();
	int commandSetDirectionM1(bool left);
	int commandSetDirectionM2(bool left);
	int commandSetDirectionM3(bool left);
	int commandSetCountsM1(int numCounts);
	int commandSetCountsM2(int numCounts);
	int commandSetCountsM3(int numCounts);
	int commandExecuteAction();
	int commandHalt();
	int calculateMovements();

	bool open;
	int l1angle;
	int l2angle;
	bool psensors;
	bool moving;
	bool ok;
	int status;
	bool atDeposit;
	bool atPeach;
};

void myTestFunc();