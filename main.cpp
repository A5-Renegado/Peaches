#include "Peaches_Main.h"

int main(int argc, char* argv[])
{
	std::cout << "Start" << std::endl;
	Peaches_Main peach = Peaches_Main(true);
	int i = peach.execute();
	return 0;
}
