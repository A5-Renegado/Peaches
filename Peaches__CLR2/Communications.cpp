#include "stdafx.h"
#include "Communications.h"
#include <algorithm>
#using <System.dll>
#define M_PI           3.14159265358979323846  /* pi */

void wait()
{
	std::string myString;
	std::cout << "Press ENTER to continue...";
	std::cin >> myString;
}

void Communications::DataReceivedHandler1(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e)
{
	System::IO::Ports::SerialPort^ sp = (System::IO::Ports::SerialPort^)sender;
	System::String^ indata = sp->ReadExisting();
	
	
	msclr::interop::marshal_context context;
	std::string s = context.marshal_as<std::string>(indata);
	s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
	std::cout << "I heard from Motor 1: " << s << std::endl;
	s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
	std::string::const_iterator it = s.begin();

	if (!s.empty() && s.find_first_not_of("-.0123456789") == std::string::npos)
	{
		globalfVMS->upm1c(stof(s));
	}
	else if (s[0] == 'm')
	{
		globalfVMS->setm1m(true);
	}
	else if (s[0] == 's')
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
	s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
	std::cout << "I heard from Motor 2: " << s << std::endl;
	s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
	std::string::const_iterator it = s.begin();

	if (!s.empty() && s.find_first_not_of("-.0123456789") == std::string::npos)
	{
		globalfVMS->upm2c(stof(s));
		std::cout << "I got an encoder change from Motor 2" << std::endl;
	}
	else if (s[0] == 'm')
	{
		globalfVMS->setm2m(true);
		std::cout << "I got moving from Motor 2" << std::endl;
	}
	else if (s[0] == 's')
	{
		globalfVMS->setm2m(false);
		std::cout << "I got stopped from Motor 2" << std::endl;
	}
}

void Communications::DataReceivedHandler3(Object^ sender, System::IO::Ports::SerialDataReceivedEventArgs^ e)
{
	System::IO::Ports::SerialPort^ sp = (System::IO::Ports::SerialPort^)sender;
	System::String^ indata = sp->ReadExisting();
	
	msclr::interop::marshal_context context;
	std::string s = context.marshal_as<std::string>(indata);
	s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
	std::cout << "I heard from Motor 3: " << s << std::endl;
	s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
	std::string::const_iterator it = s.begin();

	if (!s.empty() && s.find_first_not_of("-.0123456789") == std::string::npos)
	{
		globalfVMS->upm3c(stof(s));
	}
	else if (s[0] == 'm')
	{
		globalfVMS->setm3m(true);
	}
	else if (s[0] =='s')
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
	s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
	std::cout << "I heard from Pump: " << s << std::endl;
	std::string::const_iterator it = s.begin();
	if (s[0] == 'O')
	{
		globalfVMS->setgo(true);
		std::cout << "Set open" << std::endl;
	}
	else if (s[0] == 'C')
	{
		globalfVMS->setgo(false);
		std::cout << "Set closed" << std::endl;
	}
	else if (!s.empty() && s.find_first_not_of("-0123456789") == std::string::npos)
	{
		globalfVMS->setSensor(stoi(s));
	}
}

Communications::Communications()
{
	ok = true;
	
	String^ m1 = gcnew String(motor1port);
	String^ m2 = gcnew String(motor2port);
	String^ m3 = gcnew String(motor3port);
	String^ p1 = gcnew String(pumpport);
	if (!initiated)
	{
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
			PortM1->DataReceived += gcnew SerialDataReceivedEventHandler(DataReceivedHandler1);
			
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
			PortM2->DataReceived += gcnew SerialDataReceivedEventHandler(DataReceivedHandler2);
			MotorManager2->set_target_rotation(60.0);
			MotorManager3->apply_offset(60.0);
			status = commandSetCountsM2(MotorManager2->get_move_count());

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
			PortM3->DataReceived += gcnew SerialDataReceivedEventHandler(DataReceivedHandler3);
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
			PortP1->DataReceived += gcnew SerialDataReceivedEventHandler(DataReceivedHandlerP);
			std::cout << "Should be connected to pump port now." << std::endl;
		}
		std::cout << "Should be connected to all active ports now." << std::endl;
		wait();
	}
	initiated = true;
}

Communications::Communications(bool check)
{
	ok = true;
	
	//vFMS->setValues();
	String^ m1 = gcnew String(motor1port);
	String^ m2 = gcnew String(motor2port);
	String^ m3 = gcnew String(motor3port);
	String^ p1 = gcnew String(pumpport);
	if (!initiated)
	{
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
			PortM1->DataReceived += gcnew SerialDataReceivedEventHandler(DataReceivedHandler1);
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
			PortM2->DataReceived += gcnew SerialDataReceivedEventHandler(DataReceivedHandler2);
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
			PortM3->DataReceived += gcnew SerialDataReceivedEventHandler(DataReceivedHandler3);
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
			PortP1->DataReceived += gcnew SerialDataReceivedEventHandler(DataReceivedHandlerP);
		}
		std::cout << "This should be connected to all available ports now." << std::endl;
		wait();
	}
	initiated = true;
}

void Communications::setTargetAngles(ThreeDPos * location)
{
	theta1target = (180.0/M_PI)*atan(location->getX() / location->getZ()) - theta1start;
	theta3target = (180.0 / M_PI)*acos((pow(L2, 2) + pow(L3, 2) - (pow(location->getY(),2) + pow(location->getZ(),2)))/(location->getZ()*L2*L3)) - theta3start;
	float beta = (180.0 / M_PI)*acos(location->getY() / location->getZ());
	float alpha = (180.0 / M_PI)*atan((pow(L2, 2) + pow(location->getY(), 2) + pow(location->getZ(), 2) - pow(L3, 2)) / (2 * L2 * sqrt(pow(location->getY(), 2) + pow(location->getZ(), 2))));
	theta2target = (float)90.0 + beta - alpha - theta2start;
	std::cout << "Theta 1: " << theta1target << std::endl;
	std::cout << "Theta 2: " << theta2target << std::endl;
	std::cout << "Beta: " << beta << std::endl;
	std::cout << "Alpha: " << alpha << std::endl;
	std::cout << "Theta 3: " << theta3target << std::endl;
	std::cout << "X: " << location->getX() << std::endl;
	std::cout << "Y: " << location->getY() << std::endl;
	std::cout << "Z: " << location->getZ() << std::endl;
}

void Communications::doActions()
{
	//std::cout << doinganything << std::endl;
	if (open)// && !doinganything)
	{
		commandClose();
		//Sleep(6000);
	}
	else if (!open)// && !doinganything)
	{
		Sleep(6000);
		//commandOpen();
	}
	else if (1)
	{
	}
	else if (!ok)
	{
		status = commandHalt();
	}
	else if (bad_coordinates)
	{
		std::cout << "The coordinates are bad" << std::endl;
	}
	else if (moving)
	{
		std::cout << "A motor is moving" << std::endl;
	}
	else if (!open && psensors && atDeposit)
	{
		status = commandOpen();
		Sleep(2000);
		MotorManager2->set_target_value(theta2start+60.0, 1);
		MotorManager3->set_target_value(theta3start-135.0, 1);
		status = commandSetCountsM3(abs(MotorManager3->get_move_count()));
		status = commandSetCountsM2(abs(MotorManager2->get_move_count()));
	}
	else if (!open && psensors)
	{
		MotorManager1->set_target_value(theta1deposit, 1);
		MotorManager2->set_target_value(theta2deposit, 1);
		MotorManager3->set_target_value(theta3deposit, 1);

		status = commandSetCountsM1(MotorManager1->get_move_count());
		status = commandSetCountsM3(MotorManager3->get_move_count());
		Sleep(2000);
		status = commandSetCountsM2(MotorManager2->get_move_count());
		Sleep(500);
	}
	else if (open && atPeach && thereisapeach)  // &&psensors?
	{
		status = commandClose();
	}
	else if (thereisapeach)
	{
		status = commandSetCountsM1(MotorManager1->get_move_count());
		status = commandSetCountsM3(MotorManager3->get_move_count());
		Sleep(2000);
		status = commandSetCountsM2(MotorManager2->get_move_count());
		Sleep(500);
	}
	else
	{
		MotorManager1->set_target_rotation(15);
		MotorManager2->set_target_rotation(0);
		MotorManager3->set_target_rotation(0);
		status = commandSetCountsM1(MotorManager1->get_move_count());
		status = commandSetCountsM3(MotorManager3->get_move_count());
		Sleep(2000);
		status = commandSetCountsM2(MotorManager2->get_move_count());
		Sleep(500);
	}
	Sleep(500);
	return;
}

int Communications::commandOpen()
{
	if (p1connected)
	{
		doinganything = true;
		PortP1->Write("O\n");
		Sleep(500);
	}
	return 0;
}
int Communications::commandClose()
{
	if (p1connected)
	{
		doinganything = true;
		PortP1->Write("C\n");
		Sleep(500);
	}
	return 0;
}
int commandSetDirectionM1(bool left)
{
	if (m1connected)
	{
		if (!left)
		{
			std::cout << "This is before writing L" << std::endl;
			Communications::PortM1->Write("L\n");
			std::cout << "This is after writing L" << std::endl;
		}
		else
		{
			std::cout << "This is before writing R" << std::endl;
			Communications::PortM1->Write("R\n");
			std::cout << "This is after writing R" << std::endl;
		}
	}
	return 0;
}
int commandSetDirectionM2(bool left)
{
	if (m2connected)
	{
		if (left)
		{
			Communications::PortM2->Write("L\n");
		}
		else
		{
			Communications::PortM2->Write("R\n");
		}
	}
	return 0;
}
int commandSetDirectionM3(bool left)
{
	if (m3connected)
	{
		if (left)
		{
			Communications::PortM3->Write("L\n");
		}
		else
		{
			Communications::PortM3->Write("R\n");
		}
	}
	return 0;
}
int commandSetCountsM1(int numCounts)
{
	if (m1connected)
	{
		Communications::PortM1->Write(System::Convert::ToString(numCounts));
		Communications::PortM1->Write("\n");
	}
	return 0;
}
int commandSetCountsM2(int numCounts)
{
	if (m2connected)
	{
		//Communications::PortM2->Write(System::Convert::ToString(numCounts));
		Communications::PortM2->Write("6000");
		Communications::PortM2->Write("\n");
		std::cout << "I sent a value to motor 2: " << numCounts << std::endl;
	}
	std::cout << "I sent a value to motor 2: " << numCounts << std::endl;
	wait();
	return 0;
}
int commandSetCountsM3(int numCounts)
{
	if (m3connected)
	{
		Communications::PortM3->Write(System::Convert::ToString(numCounts));
		Communications::PortM3->Write("\n");
	}
	return 0;
}
int commandExecuteAction()
{
	if (m1connected)
	{
		Communications::PortM1->Write("G\n");
	}
	if (m3connected)
	{
		Communications::PortM3->Write("G\n");
	}
	Sleep(2000);
	if (m2connected)
	{
		Communications::PortM2->Write("G\n");
	}
	Sleep(500);
	return 0;
}
int Communications::commandHalt()
{
	if (m1connected)
	{
		PortM1->Write("s\n");
	}
	if (m2connected)
	{
		PortM2->Write("s\n");
	}
	if (m3connected)
	{
		PortM3->Write("s\n");
	}
	return 0;
}
int Communications::calculateMovements()
{
	return 0;
}

void Communications::endComms()
{
	std::cout << "This is a test to end comms" << std::endl;
	wait();
	commandHalt();
	if (m1connected)
	{
		PortM1->Close();
	}
	if (m2connected)
	{
		PortM2->Close();
	}
	if (m3connected)
	{
		PortM3->Close();
	}
	if (p1connected)
	{
		PortP1->Close();
	}

}