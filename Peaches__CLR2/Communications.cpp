#include "stdafx.h"
#include "Communications.h"
#using <System.dll>

void Communications::DataReceivedHandler1(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e)
{
	System::IO::Ports::SerialPort^ sp = (System::IO::Ports::SerialPort^)sender;
	System::String^ indata = sp->ReadExisting();
	//m.lock();
	msclr::interop::marshal_context context;
	std::string s = context.marshal_as<std::string>(indata);
	std::string::const_iterator it = s.begin();
	if (strspn(s.c_str(), "-.0123456789") == s.size())
	{
		vFMS->motor1change = stof(s);
	}
	else if (s.compare("M") == 0)
	{
		vFMS->motor1moving = true;
	}
	else if (s.compare("S") == 0)
	{
		vFMS->motor1moving = false;
	}
	//m.unlock();
}

void Communications::DataReceivedHandler2(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e)
{
	System::IO::Ports::SerialPort^ sp = (System::IO::Ports::SerialPort^)sender;
	System::String^ indata = sp->ReadExisting();
	//m.lock();
	msclr::interop::marshal_context context;
	std::string s = context.marshal_as<std::string>(indata);
	std::string::const_iterator it = s.begin();
	if (strspn(s.c_str(), "-.0123456789") == s.size())
	{
		vFMS->motor2change = stof(s);
	}
	else if (s.compare("M") == 0)
	{
		vFMS->motor2moving = true;
	}
	else if (s.compare("S") == 0)
	{
		vFMS->motor2moving = false;
	}
	//m.unlock();
}

void Communications::DataReceivedHandler3(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e)
{
	System::IO::Ports::SerialPort^ sp = (System::IO::Ports::SerialPort^)sender;
	System::String^ indata = sp->ReadExisting();
	//m.lock();
	msclr::interop::marshal_context context;
	std::string s = context.marshal_as<std::string>(indata);
	std::string::const_iterator it = s.begin();
	if (strspn(s.c_str(), "-.0123456789") == s.size())
	{
		vFMS->motor3change = stof(s);
	}
	else if (s.compare("M") == 0)
	{
		vFMS->motor3moving = true;
	}
	else if (s.compare("S") == 0)
	{
		vFMS->motor3moving = false;
	}
	//m.unlock();
}

void Communications::DataReceivedHandlerP(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e)
{
	System::IO::Ports::SerialPort^ sp = (System::IO::Ports::SerialPort^)sender;
	System::String^ indata = sp->ReadExisting();
	//m.lock();

	//m.unlock();
}

Communications::Communications()
{
	PortM1 = gcnew System::IO::Ports::SerialPort("COM3");
	PortM1->BaudRate = 9600;
	PortM1->Parity = System::IO::Ports::Parity::None;
	PortM1->StopBits = System::IO::Ports::StopBits::One;
	PortM1->DataBits = 8;
	PortM1->Handshake = System::IO::Ports::Handshake::None;
	PortM1->RtsEnable = true;
	PortM1->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(DataReceivedHandler1);
	PortM1->Open();

	PortM2 = gcnew System::IO::Ports::SerialPort("COM4");
	PortM2->BaudRate = 9600;
	PortM2->Parity = System::IO::Ports::Parity::None;
	PortM2->StopBits = System::IO::Ports::StopBits::One;
	PortM2->DataBits = 8;
	PortM2->Handshake = System::IO::Ports::Handshake::None;
	PortM2->RtsEnable = true;
	PortM2->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(DataReceivedHandler2);
	PortM2->Open();

	PortM3 = gcnew System::IO::Ports::SerialPort("COM5");
	PortM3->BaudRate = 9600;
	PortM3->Parity = System::IO::Ports::Parity::None;
	PortM3->StopBits = System::IO::Ports::StopBits::One;
	PortM3->DataBits = 8;
	PortM3->Handshake = System::IO::Ports::Handshake::None;
	PortM3->RtsEnable = true;
	PortM3->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(DataReceivedHandler3);
	PortM3->Open();

	PortP1 = gcnew System::IO::Ports::SerialPort("COM6");
	PortP1->BaudRate = 9600;
	PortP1->Parity = System::IO::Ports::Parity::None;
	PortP1->StopBits = System::IO::Ports::StopBits::One;
	PortP1->DataBits = 8;
	PortP1->Handshake = System::IO::Ports::Handshake::None;
	PortP1->RtsEnable = true;
	PortP1->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(DataReceivedHandlerP);
	PortP1->Open();
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
int Communications::calculateMovements()
{
	return 0;
}