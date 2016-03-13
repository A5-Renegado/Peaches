#include "Kinect_ImProc.h"
//#include <msclr\marshal_cppstd.h>

static const float L2 = 1;
static const float L3 = 1;

public ref class Communications
{
public:
	Communications();
	Communications(bool check);
	~Communications() {};
	System::IO::Ports::SerialPort^ PortM1;
	System::IO::Ports::SerialPort^ PortM2;
	System::IO::Ports::SerialPort^ PortM3;
	System::IO::Ports::SerialPort^ PortP1;
	static System::Object^ m_lock = gcnew System::Object();
	static DataStruct * vFMS;
	DataStruct * getVals();
	bool getMoving() { return moving; }
	void setMoving(bool x) { moving = x; }
	void setOpen(bool x) { open = x; }
	void setPsensors(bool x) { psensors = x; }
	void setAtDeposit(bool x) { atDeposit = x; }
	void setAtPeach(bool x) { atPeach = x; }
	void setThereisapeach(bool x) { thereisapeach = x; }
	void setTargetAngles(ThreeDPos * location);
	float gett1() { return theta1target; };
	float gett2() { return theta2target; };
	float gett3() { return theta3target; };

	void sendCommands() { doActions(); }
private:
	void doActions();
	static void DataReceivedHandler1(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e);
	static void DataReceivedHandler2(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e);
	static void DataReceivedHandler3(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e);
	static void DataReceivedHandlerP(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e);

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

	
	int m1movecount;
	int m2movecount;
	int m3movecount;
	bool open;
	int l1angle;
	int l2angle;
	float theta1target;
	float theta2target;
	float theta3target;
	bool psensors;
	bool moving;
	bool ok;
	int status;
	bool atDeposit;
	bool atPeach;
	bool thereisapeach;

	
};

void myTestFunc();