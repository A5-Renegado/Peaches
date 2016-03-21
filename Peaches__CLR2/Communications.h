#include "Kinect_ImProc.h"
#include <cctype>
//#include <msclr\marshal_cppstd.h>

static const float L2 = 522.288;
static const float L3 = 685.8;
static bool doinganything;

public ref class Communications
{
public:
	Communications();
	Communications(bool check);
	~Communications() {};
	static System::IO::Ports::SerialPort^ PortM1;
	static System::IO::Ports::SerialPort^ PortM2;
	static System::IO::Ports::SerialPort^ PortM3;
	static System::IO::Ports::SerialPort^ PortP1;
	static System::Object^ m_lock = gcnew System::Object();
	//static DataStruct * vFMS;
	//DataStruct * getVals();
	bool getMoving() { return moving; }
	void setMoving(bool x) { moving = x; }
	void setOpen(bool x) { std::cout << "Testing setting open: " << x << std::endl; open = x; }
	void setPsensors(bool x) { psensors = x; }
	void setAtDeposit(bool x) { atDeposit = x; }
	void setAtPeach(bool x) { atPeach = x; }
	void setThereisapeach(bool x) { thereisapeach = x; }
	void setBadCoords(bool x) { bad_coordinates = x; }
	void setTargetAngles(ThreeDPos * location);
	float gett1() { return theta1target; };
	float gett2() { return theta2target; };
	float gett3() { return theta3target; };
	static bool initiated;
	void sendCommands() { doActions(); }
	void endComms();
	static bool last_moving;
private:
	void doActions();
	static void DataReceivedHandler1(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e);
	static void DataReceivedHandler2(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e);
	static void DataReceivedHandler3(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e);
	static void DataReceivedHandlerP(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e);

	int commandOpen();
	int commandClose();
	
	
	
	
	
	int commandHalt();
	int calculateMovements();

	
	static int m1movecount;
	static int m2movecount;
	static int m3movecount;
	static bool open;
	static int l1angle;
	static int l2angle;
	static float theta1target;
	static float theta2target;
	static float theta3target;
	static bool psensors;
	static bool moving;
	static bool ok;
	static int status;
	static bool atDeposit;
	static bool atPeach;
	static bool thereisapeach;
	static bool bad_coordinates;
	
	
};

void myTestFunc();
int commandSetDirectionM1(bool left);
int commandSetDirectionM2(bool left);
int commandSetDirectionM3(bool left);
int commandSetCountsM1(int numCounts);
int commandSetCountsM2(int numCounts);
int commandSetCountsM3(int numCounts);
int commandExecuteAction();