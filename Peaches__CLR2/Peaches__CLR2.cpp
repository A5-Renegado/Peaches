// Peaches__CLR2.cpp : main project file.

#include "stdafx.h"
#include "Peaches_Main.h"

//using namespace System;

int main(array<System::String ^> ^args)
{
    //Console::WriteLine(L"Hello World");
	Peaches_Main *peach = new Peaches_Main(true);
	int i = peach->execute(args);
    return 0;
}
