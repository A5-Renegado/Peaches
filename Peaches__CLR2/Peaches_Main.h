//#include "Kinect_ImProc.h"
//#include <thread>
#include "Communications.h"



public ref class Peaches_Main
{
public:
	int execute(array<System::String ^> ^ argv);
	void set_debug_mode(bool debug);
	bool get_debug_mode();
	Peaches_Main(bool debug);
	//Communications^ test_Comms;
	
private:
	bool debug_mode;
	int counter;
	bool execution;
	//Kinect_ImProc *image_processing;
};

void draw();