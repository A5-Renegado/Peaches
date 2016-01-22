#include "stdafx.h"
#include "Peaches_Main.h"

int Peaches_Main::execute()
{
	std::string test;
	int end = 0;

	if (!image_processing->initKinect()) return 0;

	while (execution)
	{
		//std::cout << "In Execution Loop" << std::endl;
		end = main_loop();
		if (end!=0)
		{
			execution = false;
		}
		if (debug_mode)
		{
			std::cout << "Testing pacer, press enter to continue: ";
			std::cin >> test;
		}
		counter++;
		image_processing->setCounter(counter);
	}
	return 1;
}

bool Peaches_Main::get_debug_mode()
{
	return debug_mode;
}

void Peaches_Main::set_debug_mode(bool debug)
{
	debug_mode = debug;
}

Peaches_Main::Peaches_Main(bool debug)
{
	debug_mode = debug;
	image_processing = new Kinect_ImProc(debug);
	counter = 0;
	execution = true;
}

int Peaches_Main::main_loop()
{
	image_processing->getKinectData();
	bool peaches = image_processing->checkImage();
	int pix = 0;
	pix = image_processing->getCenterOfPeach();
	std::cout << pix << std::endl;
	if (pix >= 0)
	{
		image_processing->setPositionValues(pix);
	}
	else
	{
		std::cout << "No peaches" << std::endl;
	}
	if (debug_mode)
	{
		image_processing->debug_print();
	}
	return 0;
}