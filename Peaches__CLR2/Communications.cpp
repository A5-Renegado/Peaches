#include "stdafx.h"
#include "Communications.h"
#using <System.dll>

void Communications::DataReceivedHandler1(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e)
{
	System::IO::Ports::SerialPort^ sp = (System::IO::Ports::SerialPort^)sender;
	System::String^ indata = sp->ReadExisting();
	
	msclr::interop::marshal_context context;
	std::string s = context.marshal_as<std::string>(indata);
	std::string::const_iterator it = s.begin();

	if (strspn(s.c_str(), "-.0123456789") == s.size())
	{
		globalfVMS->setm1c(stof(s));
	}
	else if (s.compare("M") == 0)
	{
		globalfVMS->setm1m(true);
	}
	else if (s.compare("S") == 0)
	{
		globalfVMS->setm1m(false);
	}
}

void Communications::DataReceivedHandler2(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e)
{
	System::IO::Ports::SerialPort^ sp = (System::IO::Ports::SerialPort^)sender;
	System::String^ indata = sp->ReadExisting();
	
	msclr::interop::marshal_context context;
	std::string s = context.marshal_as<std::string>(indata);
	std::string::const_iterator it = s.begin();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	if (strspn(s.c_str(), "-.0123456789") == s.size())
	{
		globalfVMS->setm2c(stof(s));
	}
	else if (s.compare("M") == 0)
	{
		globalfVMS->setm2m(true);
	}
	else if (s.compare("S") == 0)
	{
		globalfVMS->setm2m(false);
	}
}

void Communications::DataReceivedHandler3(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e)
{
	System::IO::Ports::SerialPort^ sp = (System::IO::Ports::SerialPort^)sender;
	System::String^ indata = sp->ReadExisting();
	
	msclr::interop::marshal_context context;
	std::string s = context.marshal_as<std::string>(indata);
	std::string::const_iterator it = s.begin();
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	if (strspn(s.c_str(), "-.0123456789") == s.size())
	{
		globalfVMS->setm3c(stof(s));
	}
	else if (s.compare("M") == 0)
	{
		globalfVMS->setm3m(true);
	}
	else if (s.compare("S") == 0)
	{
		globalfVMS->setm3m(false);
	}
}

void Communications::DataReceivedHandlerP(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e)
{
	System::IO::Ports::SerialPort^ sp = (System::IO::Ports::SerialPort^)sender;
	System::String^ indata = sp->ReadExisting();

	msclr::interop::marshal_context context;
	std::string s = context.marshal_as<std::string>(indata);
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	if (s.compare("O") == 0)
	{
		globalfVMS->setgo(true);
	}
	else if (s.compare("C") == 0)
	{
		globalfVMS->setgo(false);
	}
}

Communications::Communications()
{
	vFMS->setValues();
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

Communications::Communications(bool check)
{
	vFMS->setValues();
	PortM1 = gcnew System::IO::Ports::SerialPort("COM3");
	PortM1->BaudRate = 9600;
	PortM1->Parity = System::IO::Ports::Parity::None;
	PortM1->StopBits = System::IO::Ports::StopBits::One;
	PortM1->DataBits = 8;
	PortM1->Handshake = System::IO::Ports::Handshake::None;
	PortM1->RtsEnable = true;
	PortM1->Open();

	PortM2 = gcnew System::IO::Ports::SerialPort("COM4");
	PortM2->BaudRate = 9600;
	PortM2->Parity = System::IO::Ports::Parity::None;
	PortM2->StopBits = System::IO::Ports::StopBits::One;
	PortM2->DataBits = 8;
	PortM2->Handshake = System::IO::Ports::Handshake::None;
	PortM2->RtsEnable = true;
	PortM2->Open();

	PortM3 = gcnew System::IO::Ports::SerialPort("COM5");
	PortM3->BaudRate = 9600;
	PortM3->Parity = System::IO::Ports::Parity::None;
	PortM3->StopBits = System::IO::Ports::StopBits::One;
	PortM3->DataBits = 8;
	PortM3->Handshake = System::IO::Ports::Handshake::None;
	PortM3->RtsEnable = true;
	PortM3->Open();

	PortP1 = gcnew System::IO::Ports::SerialPort("COM6");
	PortP1->BaudRate = 9600;
	PortP1->Parity = System::IO::Ports::Parity::None;
	PortP1->StopBits = System::IO::Ports::StopBits::One;
	PortP1->DataBits = 8;
	PortP1->Handshake = System::IO::Ports::Handshake::None;
	PortP1->RtsEnable = true;
	PortP1->Open();
}

DataStruct * Communications::getVals()
{
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	return vFMS;
}

void Communications::listenToPort()
{
	int i = 0;
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
	else if (open && psensors && atPeach && thereisapeach)
	{
		status = commandClose();
	}
	else if (thereisapeach)
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