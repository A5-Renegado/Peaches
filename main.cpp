#include "Peaches_Main.h"

int main(int argc, char* argv[])
{
	Peaches_Main *peach = new Peaches_Main(true);
	int i = peach->execute();
	return 0;
}
