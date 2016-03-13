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
		globalfVMS->upm1c(stof(s));
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
		globalfVMS->upm2c(stof(s));
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
		globalfVMS->upm3c(stof(s));
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
	ok = true;
	vFMS->setValues();
	String^ m1 = gcnew String(motor1port);
	String^ m2 = gcnew String(motor2port);
	String^ m3 = gcnew String(motor3port);
	String^ p1 = gcnew String(pumpport);

	if (m1connected)
	{
		PortM1 = gcnew System::IO::Ports::SerialPort(m1);
		PortM1->BaudRate = 9600;
		PortM1->Parity = System::IO::Ports::Parity::None;
		PortM1->StopBits = System::IO::Ports::StopBits::One;
		PortM1->DataBits = 8;
		PortM1->Handshake = System::IO::Ports::Handshake::None;
		PortM1->RtsEnable = true;
		PortM1->Open();
	}
	if (m2connected)
	{
		PortM2 = gcnew System::IO::Ports::SerialPort(m2);
		PortM2->BaudRate = 9600;
		PortM2->Parity = System::IO::Ports::Parity::None;
		PortM2->StopBits = System::IO::Ports::StopBits::One;
		PortM2->DataBits = 8;
		PortM2->Handshake = System::IO::Ports::Handshake::None;
		PortM2->RtsEnable = true;
		PortM2->Open();
	}
	if (m3connected)
	{
		PortM3 = gcnew System::IO::Ports::SerialPort(m3);
		PortM3->BaudRate = 9600;
		PortM3->Parity = System::IO::Ports::Parity::None;
		PortM3->StopBits = System::IO::Ports::StopBits::One;
		PortM3->DataBits = 8;
		PortM3->Handshake = System::IO::Ports::Handshake::None;
		PortM3->RtsEnable = true;
		PortM3->Open();
	}
	if (p1connected)
	{
		PortP1 = gcnew System::IO::Ports::SerialPort(p1);
		PortP1->BaudRate = 9600;
		PortP1->Parity = System::IO::Ports::Parity::None;
		PortP1->StopBits = System::IO::Ports::StopBits::One;
		PortP1->DataBits = 8;
		PortP1->Handshake = System::IO::Ports::Handshake::None;
		PortP1->RtsEnable = true;
		PortP1->Open();
	}
}

Communications::Communications(bool check)
{
	ok = true;
	vFMS->setValues();
	String^ m1 = gcnew String(motor1port);
	String^ m2 = gcnew String(motor2port);
	String^ m3 = gcnew String(motor3port);
	String^ p1 = gcnew String(pumpport);

	if (m1connected)
	{
		PortM1 = gcnew System::IO::Ports::SerialPort(m1);
		PortM1->BaudRate = 9600;
		PortM1->Parity = System::IO::Ports::Parity::None;
		PortM1->StopBits = System::IO::Ports::StopBits::One;
		PortM1->DataBits = 8;
		PortM1->Handshake = System::IO::Ports::Handshake::None;
		PortM1->RtsEnable = true;
		PortM1->Open();
	}
	if (m2connected)
	{
		PortM2 = gcnew System::IO::Ports::SerialPort(m2);
		PortM2->BaudRate = 9600;
		PortM2->Parity = System::IO::Ports::Parity::None;
		PortM2->StopBits = System::IO::Ports::StopBits::One;
		PortM2->DataBits = 8;
		PortM2->Handshake = System::IO::Ports::Handshake::None;
		PortM2->RtsEnable = true;
		PortM2->Open();
	}
	if (m3connected)
	{
		PortM3 = gcnew System::IO::Ports::SerialPort(m3);
		PortM3->BaudRate = 9600;
		PortM3->Parity = System::IO::Ports::Parity::None;
		PortM3->StopBits = System::IO::Ports::StopBits::One;
		PortM3->DataBits = 8;
		PortM3->Handshake = System::IO::Ports::Handshake::None;
		PortM3->RtsEnable = true;
		PortM3->Open();
	}
	if (p1connected)
	{
		PortP1 = gcnew System::IO::Ports::SerialPort(p1);
		PortP1->BaudRate = 9600;
		PortP1->Parity = System::IO::Ports::Parity::None;
		PortP1->StopBits = System::IO::Ports::StopBits::One;
		PortP1->DataBits = 8;
		PortP1->Handshake = System::IO::Ports::Handshake::None;
		PortP1->RtsEnable = true;
		PortP1->Open();
	}
}

DataStruct * Communications::getVals()
{
	msclr::lock^ getLock = gcnew msclr::lock(m_lock);
	return vFMS;
}

void Communications::setTargetAngles(ThreeDPos * location)
{
	theta3target = atan(location->getX() / location->getZ());
	theta2target = acos((pow(L2, 2) + pow(L3, 2) - (pow(location->getY(),2) + pow(location->getZ(),2)))/(location->getZ()*L2*L3));
	theta1target = 90 + atan(location->getY() / location->getZ()) - acos((pow(L2,2) + pow(location->getY(),2) + pow(location->getZ(),2) - pow(L3,2))/(location->getZ() * L2 * sqrt(pow(location->getY(),2)+pow(location->getZ(),2))));
}

void Communications::doActions()
{
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
		status = commandSetDirectionM1(MotorManager1->get_direction());
		status = commandSetDirectionM2(MotorManager2->get_direction());
		status = commandSetDirectionM3(MotorManager3->get_direction());
		status = commandSetCountsM1(abs(MotorManager1->get_move_count()));
		status = commandSetCountsM2(abs(MotorManager2->get_move_count()));
		status = commandSetCountsM3(abs(MotorManager3->get_move_count()));
		status = commandExecuteAction();
	}
	else if (open && psensors && atPeach && thereisapeach)
	{
		status = commandClose();
	}
	else if (thereisapeach)
	{
		status = commandSetDirectionM1(MotorManager1->get_direction());
		status = commandSetDirectionM2(MotorManager2->get_direction());
		status = commandSetDirectionM3(MotorManager3->get_direction());
		status = commandSetCountsM1(abs(MotorManager1->get_move_count()));
		status = commandSetCountsM2(abs(MotorManager2->get_move_count()));
		status = commandSetCountsM3(abs(MotorManager3->get_move_count()));
		status = commandExecuteAction();
	}
	else
	{
		status = commandSetDirectionM1(MotorManager1->get_direction());
		status = commandSetDirectionM2(MotorManager2->get_direction());
		status = commandSetDirectionM3(MotorManager3->get_direction());
		status = commandSetCountsM1(abs(MotorManager1->get_move_count()));
		status = commandSetCountsM2(abs(MotorManager2->get_move_count()));
		status = commandSetCountsM3(abs(MotorManager3->get_move_count()));
		status = commandExecuteAction();
	}
	return;
}

int Communications::commandOpen()
{
	if (p1connected)
	{
		PortP1->Write("O");
	}
	return 0;
}
int Communications::commandClose()
{
	if (p1connected)
	{
		PortP1->Write("C");
	}
	return 0;
}
int Communications::commandSetDirectionM1(bool left)
{
	if (m1connected)
	{
		if (left)
		{
			PortM1->Write("L");
		}
		else
		{
			PortM1->Write("R");
		}
	}
	return 0;
}
int Communications::commandSetDirectionM2(bool left)
{
	if (m2connected)
	{
		if (left)
		{
			PortM2->Write("L");
		}
		else
		{
			PortM2->Write("R");
		}
	}
	return 0;
}
int Communications::commandSetDirectionM3(bool left)
{
	if (m3connected)
	{
		if (left)
		{
			PortM3->Write("L");
		}
		else
		{
			PortM3->Write("R");
		}
	}
	return 0;
}
int Communications::commandSetCountsM1(int numCounts)
{
	if (m1connected)
	{
		PortM1->Write(System::Convert::ToString(numCounts));
	}
	return 0;
}
int Communications::commandSetCountsM2(int numCounts)
{
	if (m2connected)
	{
		PortM2->Write(System::Convert::ToString(numCounts));
	}
	return 0;
}
int Communications::commandSetCountsM3(int numCounts)
{
	if (m3connected)
	{
		PortM3->Write(System::Convert::ToString(numCounts));
	}
	return 0;
}
int Communications::commandExecuteAction()
{
	if (m1connected)
	{
		PortM1->Write("G");
	}
	if (m2connected)
	{
		PortM2->Write("G");
	}
	if (m3connected)
	{
		PortM3->Write("G");
	}
	return 0;
}
int Communications::commandHalt()
{
	if (m1connected)
	{
		PortM1->Write("H");
	}
	if (m2connected)
	{
		PortM2->Write("H");
	}
	if (m3connected)
	{
		PortM3->Write("H");
	}
	return 0;
}
int Communications::calculateMovements()
{
	return 0;
}