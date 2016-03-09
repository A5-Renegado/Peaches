#include "stdafx.h"
#include "Kinect_ImProc.h"

//Base constructor for non-debug mode. Need to adjust min/max values for lighting.
Kinect_ImProc::Kinect_ImProc()
{
	debug_mode = false;
	redmin = 0.5568627;
	redmax = 0.9568627;
	greenmin = 0.3490196;
	greenmax = 0.7647059;
	bluemin = 0.4352941;
	bluemax = 0.7882353;
	position = new ThreeDPos();
	lockPosition = false;
	comLockPosition = false;
}

//Constructor for either debug or non-debug mode. Min/Max values are good for the orange hockey ball.
Kinect_ImProc::Kinect_ImProc(bool debug)
{
	debug_mode = debug;
	//redmin = 0.5568627;
	redmin = 200.0/255.0;
	//redmax = 0.9568627;
	redmax = 1.0;
	//greenmin = 0.3490196;
	greenmin = 0.0/255.0;
	//greenmax = 0.7647059;
	greenmax = 90.0/255.0;
	//bluemin = 0.4352941;
	bluemin = 0.0/255.0;
	//bluemax = 0.7882353;
	bluemax = 200.0/255.0;
	position = new ThreeDPos();
	lockPosition = false;
	comLockPosition = false;
}

//Return whether or not the program is running in debug mode
bool Kinect_ImProc::check_debug()
{
	return debug_mode;
}

//Connect to the Kinect and prepare to enter the main loop
bool Kinect_ImProc::initKinect()
{
	int numSensors;
	if (NuiGetSensorCount(&numSensors) < 0 || numSensors < 1)
	{
		std::cout << "No Sensors" << std::endl;
		return false;
	}
	if (NuiCreateSensorByIndex(0, &sensor) < 0) return false;
	HRESULT status = sensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_DEPTH | NUI_INITIALIZE_FLAG_USES_COLOR);
	if (status < 0)
	{
		if (debug_mode)
		{
			std::string fail;
			std::cout << "Failed to initialize: " << status << std::endl;
			std::cin >> fail;
		}
		return false;
	}

	//Open stream to gather colour data
	long rgbSuccess = sensor->NuiImageStreamOpen(
		NUI_IMAGE_TYPE_COLOR,			// Depth camera or rgb camera?
		NUI_IMAGE_RESOLUTION_640x480,	// Image resolution
		0,		// Image stream flags
		1,		// Number of frames to buffer
		NULL,	//Event handle
		&rgbStream);
	//Open stream to gather depth data
	long depthSuccess = sensor->NuiImageStreamOpen(
		NUI_IMAGE_TYPE_DEPTH,			// Depth camera or rgb camera?
		NUI_IMAGE_RESOLUTION_640x480,	// Image resolution
		0,		// Image stream flags
		1,		// Number of frames to buffer
		NULL,	//Event handle
		&depthStream);
	if (debug_mode)
	{
		std::cout << sensor << std::endl << rgbSuccess << std::endl << depthSuccess << std::endl;
		std::cout << E_FAIL << " " << E_INVALIDARG << " " << E_NUI_DEVICE_NOT_READY << " " << E_OUTOFMEMORY << " " << E_POINTER << std::endl;
	}
	return sensor;
}

//Get and interpret RGB data
void Kinect_ImProc::getRgbData(GLubyte* dest, GLubyte* dest2)
{
	NUI_IMAGE_FRAME imageFrame;
	NUI_LOCKED_RECT LockedRect;
	if (sensor->NuiImageStreamGetNextFrame(rgbStream, 0, &imageFrame) < 0)
	{
		std::cout << "Could not get next frame (RGB)" << std::endl;
		print = false;
		return;
	}
	INuiFrameTexture* texture = imageFrame.pFrameTexture;
	texture->LockRect(0, &LockedRect, NULL, 0);
	if (LockedRect.Pitch != 0)
	{
		std::cout << "Doing stuff" << std::endl;
		const BYTE* curr = (const BYTE*)LockedRect.pBits;
		const BYTE* start = (const BYTE*)LockedRect.pBits;
		
		const BYTE* dataEnd = curr + (width*height) * 4;
		float* fdest = (float*)dest;
		long* depth2rgb = (long*)depthToRgbMap;
		while (curr < dataEnd)
		{
			*dest2++ = *curr++;
		} //HERE
		for (int j = 0; j < height; ++j)
		{
			for (int i = 0; i < width; ++i)
			{
				// Determine color pixel for depth pixel i,j
				long x = *depth2rgb++;
				long y = *depth2rgb++;
				// If out of bounds, then do not color this pixel
				if (x < 0 || y < 0 || x > width || y > height) {
					for (int n = 0; n < 3; ++n) *fdest++ = 0.f;
				}
				else {
					// Determine rgb color for depth pixel (i,j) from color pixel (x,y)
					const BYTE* color = start + (x + width*y) * 4;
					if (color) print = true;
					for (int n = 0; n < 3; ++n)
					{
						*fdest++ = color[2 - n] / 255.f;
					}
				}
			}
		}
		
	}
	texture->UnlockRect(0);
	sensor->NuiImageStreamReleaseFrame(rgbStream, &imageFrame);
}

//Get and interpret depth data
void Kinect_ImProc::getDepthData(GLubyte* dest)
{
	NUI_IMAGE_FRAME imageFrame;
	NUI_LOCKED_RECT LockedRect;
	if (sensor->NuiImageStreamGetNextFrame(depthStream, 0, &imageFrame) < 0)
	{
		std::cout << "Could not get next frame (Depth)" << std::endl;
		return;
	}
	INuiFrameTexture* texture = imageFrame.pFrameTexture;
	texture->LockRect(0, &LockedRect, NULL, 0);
	if (LockedRect.Pitch != 0)
	{
		const USHORT* curr = (const USHORT*)LockedRect.pBits;
		float* fdest = (float*)dest;
		long* depth2rgb = (long*)depthToRgbMap;
		for (int j = 0; j < height; ++j)
		{
			for (int i = 0; i < width; ++i)
			{
				USHORT depth = NuiDepthPixelToDepth(*curr);
				Vector4 pos = NuiTransformDepthImageToSkeleton(i, j, *curr);
				//*fdest++ = pos.x / pos.w;
				//*fdest++ = pos.y / pos.w;
				//*fdest++ = pos.z / pos.w;
				*fdest++ = depth;
				if ((pos.x / pos.w) != 0 || (pos.y / pos.w) != 0 || (pos.z / pos.w) != 0)
				{
					//end = true;
				}
				NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(
					NUI_IMAGE_RESOLUTION_640x480,
					NUI_IMAGE_RESOLUTION_640x480,
					NULL,
					i, j, *curr,
					depth2rgb, depth2rgb + 1
					); // GOHERE
				depth2rgb += 2;
				*curr++;
			}
		}
	}
	texture->UnlockRect(0);
	sensor->NuiImageStreamReleaseFrame(depthStream, &imageFrame);
}

void Kinect_ImProc::getKinectData()
{
	getDepthData((GLubyte*)vertexarray);
	getRgbData((GLubyte*)colorarray, (GLubyte*)data);
	//data = (GLubyte*)colorarray;
}

void Kinect_ImProc::setCounter(int count)
{
	counter = count;
}

//Determine if there is a peach in the image, as well as what pixels contain a peach
bool Kinect_ImProc::checkImage()
{
	bool peaches = false;
	for (int i = 0; i < width*height; i++)
	{
		int isPixel = checkPixel(colorarray[i * 3], colorarray[i * 3 + 1], colorarray[i * 3 + 2]);
		if (isPixel == 1)
		{
			peaches = true;
			thereisapeach = true;
			data[i * 4] = static_cast<GLubyte>(255.f);
			data[i * 4 + 1] = static_cast<GLubyte>(255.f);
			data[i * 4 + 2] = static_cast<GLubyte>(255.f);
		}
		locationpeaches[i] = isPixel;
	}
	return peaches;
}

//Determines if based on 3 values whether or not that pixel is a peach
int Kinect_ImProc::checkPixel(float red, float green, float blue)
{
	if (red <= redmax && red >= redmin && green <= greenmax && green >= greenmin && blue <= bluemax && blue >= bluemin)
	{
		return 1;
	}
	return 0;
}

//Debugging routine that outputs values to files as desired - No longer needed but do not delete as it may become necessary again
void Kinect_ImProc::debug_print()
{
	//std::ofstream myfile;
	//std::ofstream depthfile;
	//std::ofstream peachfile;
	//if (print)
	//{
		//std::string colorfilename = "SampleColorData";
		//std::string depthfilename = "SampleDepthData";
		//std::string peachfilename = "SamplePeachData";
		//char buffer[33];
		//char *num = _itoa(j, buffer, 10);
		//colorfilename.append(std::to_string(counter));
		//depthfilename.append(std::to_string(counter));
		//peachfilename.append(std::to_string(counter));
		//depthfilename.append(".txt");
		//colorfilename.append(".txt");
		//peachfilename.append(".ppm");
		//myfile.open(colorfilename);
		//depthfile.open(depthfilename);
		//peachfile.open(peachfilename);
		//FILE *f = fopen("SamplePeachData.ppm", "wb");
		//fprintf(f, "P6\n%i %i 255\n", width, height);
		//for (int i = 0; i < width*height; i++)
		//{
			//myfile << colorarray[i * 3] << " " << colorarray[i * 3 + 1] << " " << colorarray[i * 3 + 2] << " ";
			//depthfile << vertexarray[i] << std::endl;
			//fputc(locationpeaches[i] * 255, f);
			//fputc(locationpeaches[i] * 255, f);
			//fputc(locationpeaches[i] * 255, f);
			//peachfile << locationpeaches[i];
			//if ((i + 1) % width == 0)
			//{
			//	peachfile << std::endl;
			//}
		//}
		//myfile.close();
		//depthfile.close();
		//fclose(f);
		//peachfile.close();
		//j++;
		//std::cout << position->getX() << " " << position->getY() << " " << position->getZ() << std::endl;
	//}
}

//Calculate width/height of a pixel using linear approximation
double Kinect_ImProc::estimatePixelSize(long distance)
{
	double size = 0;
	double y0 = 1.349375;
	double y1 = 1.825625;
	double x0 = 736.6;
	double x1 = 1016;
	size = y0 + (y1 - y0)*(distance - x0) / (x1 - x0);
	return size;
}

//Determine what pixel contains the center of the peach
int Kinect_ImProc::getCenterOfPeach()
{
	int counter = 0;
	int h = 0;
	int w = 0;
	int pix = 0;
	for (int i = 1; i <= height*width; i++)
	{
		if (locationpeaches[i-1] == 1)
		{
			counter++;
			int wz = i % 640;
			w += i%640;
			h += (i - wz)/640;

		}
	}
	if (counter != 0)
	{
		pix = 640 * (h / counter - 1) + w / counter;
	}
	else
	{
		pix = 0;
	}
	std::cout << h << " " << w << " " << counter << std::endl;
	return pix-1;
}

void Kinect_ImProc::setPositionValues(int pix)
{
	int w = (pix+1)%640;
	int h = ((pix + 1) -w)/640;
	double z = vertexarray[pix];
	double psize = estimatePixelSize(z);
	double x = psize*(h - 319.5);
	double y = psize*(w - 239.5);
	position->setX(x);
	position->setY(y);
	position->setZ(z);
	if (debug_mode)
	{
		std::cout << x << " " << y << " " << z << std::endl;
	}
}

//re-write this. Use Mutex's. This is just bad coding.
ThreeDPos * Kinect_ImProc::getPosition()
{
	while (lockPosition)
	{

	}
	return position;
}