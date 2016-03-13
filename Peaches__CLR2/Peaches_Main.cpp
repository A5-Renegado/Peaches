#include "stdafx.h"
#include "Peaches_Main.h"

//Create image processing instance
Kinect_ImProc *image_processing = new Kinect_ImProc(true);
//Communications^ test_Comms;// = gcnew Communications();

int Peaches_Main::execute(array<System::String ^> ^ argv)
{
	std::string test;
	int end = 0;
	
	//Set up GLUT loop for drawing output
	char *myargv[1];
	int myargc = 1;
	myargv[0] = strdup("Peaches__CLR2");
	glutInit(&myargc, myargv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutCreateWindow("Peaches");
	glutDisplayFunc(draw);
	glutIdleFunc(draw);

	//Set GLUT parameters
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
	
	//Connect to the Kinect. If fail, exit.
	if (!image_processing->initKinect()) return 0;

	Communications^ test_Comms;
	//Initiate Comms
	if (comms)
	{
		test_Comms = gcnew Communications();
	}
	//Start Main Loop (use Glut Main loop for pre-prepared multi-threading and image output prep)
	glutMainLoop();
	//Close port communications once they are complete
	if (m1connected)
	{
		test_Comms->PortM1->Close();
	}
	if (m2connected)
	{
		test_Comms->PortM2->Close();
	}
	if (m3connected)
	{
		test_Comms->PortM3->Close();
	}
	if (p1connected)
	{
		test_Comms->PortP1->Close();
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
	counter = 0;
	execution = true;
}

//Repeated function in GLUT Main loop
void draw()
{
	//Get data from the Kinect for analysis and display
	image_processing->getKinectData();
	//Check for peaches in the image
	bool peaches = image_processing->checkImage();
	int pix = 0;
	//Find the center of the peach
	pix = image_processing->getCenterOfPeach();
	image_processing->data[pix * 4] = static_cast<GLubyte>(0.f);
	image_processing->data[pix * 4 + 1] = static_cast<GLubyte>(0.f);
	image_processing->data[pix * 4 + 1] = static_cast<GLubyte>(0.f);
	std::cout << pix << std::endl;
	if (pix >= 0)
	{
		//Store the position of the peach
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
	//Write image to screen
	glBindTexture(GL_TEXTURE_2D, image_processing->textureId);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)(image_processing->data));
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
	glutSwapBuffers();
	Communications^ test_Comms = gcnew Communications(true);
	if (globalfVMS->getm1m() || globalfVMS->getm2m() || globalfVMS->getm3m())
	{
		test_Comms->setMoving(true);
	}
	else
	{
		test_Comms->setMoving(false);
	}
	test_Comms->setOpen(globalfVMS->getgo());
	MotorManager1->update_current(globalfVMS->getandclearm1());
	MotorManager2->update_current(globalfVMS->getandclearm2());
	MotorManager3->update_current(globalfVMS->getandclearm3());
	test_Comms->setTargetAngles(image_processing->position);
	MotorManager1->set_target_value(test_Comms->gett1(), 1);
	MotorManager2->set_target_value(test_Comms->gett2(), 1);
	MotorManager3->set_target_value(test_Comms->gett3(), 1);

	//Need to set all values before this!
	test_Comms->sendCommands();
	if (m1connected)
	{
		test_Comms->PortM1->Close();
	}
	if (m2connected)
	{
		test_Comms->PortM2->Close();
	}
	if (m3connected)
	{
		test_Comms->PortM3->Close();
	}
	if (p1connected)
	{
		test_Comms->PortP1->Close();
	}
}