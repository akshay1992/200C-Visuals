#ifndef FLOAT_IMAGE
#define FLOAT_IMAGE

#include "ofImage.h"

class FloatImage
{
public:
	int xRes;
	int yRes;

	FloatImage(int xResolution, int yResolution)
	{
		xRes = xResolution;
		yRes = yResolution;
		_data = (float*) calloc(xRes*yRes, sizeof(float));
	}

	FloatImage(void){}

	void init(int xResolution, int yResolution)
	{
		xRes = xResolution;
		yRes = yResolution;
		_data = (float*) calloc(xRes*yRes, sizeof(float));
	}

	~FloatImage(void)
	{
		free(_data);
	}

	void set(int x, int y, float value)
	{
		_data[y*xRes + x] = value;
	}

	void normalize()
	{
		// Normalizes float values to 0-1 range for each pixel
		float max=0; 
		for(int index=0; index< xRes*yRes; index++)
		{
			if(_data[index]>max)
			max = _data[index];
		}

		for(int index=0; index< xRes*yRes; index++)
		{
			_data[index] /= max;
		}
	}

	void copyTo(ofImage &image)
	{
		// Normalizes and makes an integer array 0-255 with the data
		normalize();

		unsigned char* _intData = (unsigned char *) calloc(xRes*yRes, sizeof(unsigned char));
		for(int index=0; index< xRes*yRes; index++)
		{
			image.getPixelsRef()[index] = (int) 255.0f*_data[index];
		}
	}

	float operator()(int x, int y)
	{
		return _data[getIndex(x, y)];
	}

	int getIndex(int x, int y)
	{
	    return y*xRes + x;
	}

private:
	float* _data;
};



#endif