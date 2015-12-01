//

using namespace System;
using namespace System::IO::Ports;

int main(array<System::String ^> ^args)
{
	SerialPort testport;
	testport.PortName = "COM10";
	testport.Open();
	testport.Write("7");
	//testport.Close();
    Console::WriteLine(L"Hello World");
	String ^ test = testport.ReadLine();
	Console::WriteLine(test);
    return 0;
}
