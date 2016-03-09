#include "Kinect_ImProc.h"
//#include <msclr\marshal_cppstd.h>



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
private:
	void listenToPort();
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

	

	bool open;
	int l1angle;
	int l2angle;
	bool psensors;
	bool moving;
	bool ok;
	int status;
	bool atDeposit;
	bool atPeach;
	bool thereisapeach;

	
};

void myTestFunc();