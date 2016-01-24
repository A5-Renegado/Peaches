#include "stdafx.h"
#include "Peaches_Main.h"

Kinect_ImProc *image_processing = new Kinect_ImProc(true);


int Peaches_Main::execute(array<System::String ^> ^ argv)
{
	std::string test;
	int end = 0;
	if (!image_processing->initKinect()) return 0;
	glGenTextures(1, &image_processing->textureId);
	glBindTexture(GL_TEXTURE_2D, image_processing->textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)image_processing->data);
	glBindTexture(GL_TEXTURE_2D, 0);
	glClearColor(0, 0, 0, 0);
	glClearDepth(1.0f);
	glEnable(GL_TEXTURE_2D);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	char *myargv[1];
	int myargc = 1;
	myargv[0] = strdup("Peaches__CLR2");
	glutInit(&myargc, myargv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutCreateWindow("Peaches");
	glutDisplayFunc(draw);
	glutIdleFunc(draw);

	//while (execution)
	//{
		//std::cout << "In Execution Loop" << std::endl;
	//	end = main_loop();
	//	if (end!=0)
	//	{
	//		execution = false;
	//	}
	//	if (debug_mode)
	//	{
	//		std::cout << "Testing pacer, press enter to continue: ";
	//		std::cin >> test;
	//	}
	//	counter++;
	//	image_processing->setCounter(counter);
	//}

	glutMainLoop();
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
	//image_processing = new Kinect_ImProc(debug);
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

int Peaches_Main::main_pub()
{
	return main_loop();
}

void draw()
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
	if (image_processing->check_debug())
	{
		image_processing->debug_print();
	}

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)image_processing->data);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(width, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, height, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, height, 0.0f);
	glEnd();
}