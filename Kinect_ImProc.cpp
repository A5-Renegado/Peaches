#include "Kinect_ImProc.h"

Kinect_ImProc::Kinect_ImProc()
{
	debug_mode = false;
}

Kinect_ImProc::Kinect_ImProc(bool debug)
{
	debug_mode = debug;
	redmin = 0.5568627;
	redmax = 0.9568627;
	greenmin = 0.3490196;
	greenmax = 0.7647059;
	bluemin = 0.4352941;
	bluemax = 0.7882353;
}

bool Kinect_ImProc::initKinect()
{
	int numSensors;
	if (NuiGetSensorCount(&numSensors) < 0 || numSensors < 1) return false;
	if (NuiCreateSensorByIndex(0, &sensor) < 0) return false;

	if (sensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_DEPTH | NUI_INITIALIZE_FLAG_USES_COLOR) < 0)
	{
		if (debug_mode)
		{
			std::string fail;
			std::cout << "Failed to initialize" << std::endl;
			std::cin >> fail;
		}
		return false;
	}

	long rgbSuccess = sensor->NuiImageStreamOpen(
		NUI_IMAGE_TYPE_COLOR,			// Depth camera or rgb camera?
		NUI_IMAGE_RESOLUTION_640x480,	// Image resolution
		0,		// Image stream flags
		1,		// Number of frames to buffer
		NULL,	//Event handle
		&rgbStream);
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

void Kinect_ImProc::getRgbData(GLubyte* dest)
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
		const BYTE* start = (const BYTE*)LockedRect.pBits;
		float* fdest = (float*)dest;
		long* depth2rgb = (long*)depthToRgbMap;
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
				*fdest++ = pos.x / pos.w;
				*fdest++ = pos.y / pos.w;
				*fdest++ = pos.z / pos.w;
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
					);
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
	getRgbData((GLubyte*)colorarray);
}

void Kinect_ImProc::setCounter(int count)
{
	counter = count;
}

bool Kinect_ImProc::checkImage()
{
	bool peaches = false;
	for (int i = 0; i < width*height; i++)
	{
		int isPixel = checkPixel(colorarray[i * 3], colorarray[i * 3 + 1], colorarray[i * 3 + 2]);
		if (isPixel == 1)
		{
			peaches = true;
		}
		locationpeaches[i] = isPixel;
	}
	return peaches;
}

int Kinect_ImProc::checkPixel(float red, float green, float blue)
{
	if (red <= redmax && red >= redmin && green <= greenmax && green >= greenmin && blue <= bluemax && blue >= bluemin)
	{
		return 1;
	}
	return 0;
}

void Kinect_ImProc::debug_print()
{
	std::ofstream myfile;
	std::ofstream depthfile;
	std::ofstream peachfile;
	if (print)
	{
		std::string colorfilename = "SampleColorData";
		std::string depthfilename = "SampleDepthData";
		std::string peachfilename = "SamplePeachData";
		//char buffer[33];
		//char *num = _itoa(j, buffer, 10);
		colorfilename.append(std::to_string(counter));
		depthfilename.append(std::to_string(counter));
		peachfilename.append(std::to_string(counter));
		depthfilename.append(".txt");
		colorfilename.append(".txt");
		peachfilename.append(".ppm");
		myfile.open(colorfilename);
		depthfile.open(depthfilename);
		//peachfile.open(peachfilename);
		FILE *f = fopen("SamplePeachData.ppm", "wb");
		fprintf(f, "P6\n%i %i 255\n", width, height);
		for (int i = 0; i < width*height; i++)
		{
			//myfile << colorarray[i * 3] << " " << colorarray[i * 3 + 1] << " " << colorarray[i * 3 + 2] << " ";
			//depthfile << vertexarray[i*3] << " " << vertexarray[i * 3 + 1] << " " << vertexarray[i * 3 + 2] << " ";
			fputc(locationpeaches[i] * 255, f);
			fputc(locationpeaches[i] * 255, f);
			fputc(locationpeaches[i] * 255, f);
			//peachfile << locationpeaches[i];
			//if ((i + 1) % width == 0)
			//{
			//	peachfile << std::endl;
			//}
		}
		myfile.close();
		depthfile.close();
		fclose(f);
		//peachfile.close();
		//j++;
	}
}
