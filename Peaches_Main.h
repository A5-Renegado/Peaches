#include "Kinect_ImProc.h"


class Peaches_Main
{
public:
	int execute();
	void set_debug_mode(bool debug);
	bool get_debug_mode();
	Peaches_Main(bool debug);
private:
	bool debug_mode;
	int main_loop();
	int counter;
	bool execution;
	Kinect_ImProc *image_processing;
};
