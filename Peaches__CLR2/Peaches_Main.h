//#include "Kinect_ImProc.h"
//#include <thread>
#include "Communications.h"



class Peaches_Main
{
public:
	int execute(array<System::String ^> ^ argv);
	void set_debug_mode(bool debug);
	bool get_debug_mode();
	Peaches_Main(bool debug);
	int main_pub();
	
private:
	bool debug_mode;
	int main_loop();
	int counter;
	bool execution;
	//Kinect_ImProc *image_processing;
};

void draw();