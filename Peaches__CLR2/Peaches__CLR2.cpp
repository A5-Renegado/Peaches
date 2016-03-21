// Peaches__CLR2.cpp : main project file.

#include "stdafx.h"
#include "Peaches_Main.h"
#include <cstdlib>

//using namespace System;

void exiting()
{
	Communications^ myEndComms = gcnew Communications();
	myEndComms->endComms();
}

int main(array<System::String ^> ^args)
{
	std::atexit(exiting);
	//freopen("log.txt", "w", stdout);
	Peaches_Main^ peach = gcnew Peaches_Main(true);
	int i = peach->execute(args);
    return 0;
}
