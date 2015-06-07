#ifndef QUATERNION_FRACTAL
#define QUATERNION_FRACTAL

#include "FloatImage.h"

#define loop(xRes, yRes) for(int x=0; x<xRes; x++)	   \
							for(int y=0; y<yRes; y++) 

//---------------------------------------
// Q U A T E R N I O N		F R A C T A L
//---------------------------------------

class QuaternionFractal
{
public:
	ofImage current_frame;
	int xRes;
	int yRes;
	bool display_values;
	int * mouseXRef;
	int * mouseYRef;
	FloatImage intermediateImage; // For conversion to int8 image and normalization. 


	void init(int xResolution, int yResolution)
	{
		xRes = xResolution;
		yRes = yResolution;
		current_frame.allocate(xRes, yRes, OF_IMAGE_GRAYSCALE);
		intermediateImage.init(xRes, yRes);
	}	

	void setMouseVars(int &mouseX, int &mouseY)
	{
		mouseXRef = &mouseX;
		mouseYRef = &mouseY;
	}

	void draw(void)
	{
		current_frame.draw(0,0);
		if (display_values)
		{
			// cout << "(" << *mouseXRef << " " << *mouseYRef << ") = " << (int)current_frame.getPixelsRef()[getIndex(*mouseXRef, *mouseYRef)] << endl;
			cout << "(" << *mouseXRef << " " << *mouseYRef << ") = " << (float)intermediateImage(*mouseXRef, *mouseYRef) << endl;
		}
	}
	
	void update(void)
	{
		loop(xRes, yRes)
		{
			float pixelValue;

			// ---- FRACTAL GENERATION ----
			int x1 = x;
			int y1 = (yRes-1)-y;

			ofVec4f q = convertXY(x1, y1);
			ofVec4f c(0.285,0.485,0,0);
			int t = 0;
			while( q.length() < 2.0 && t<100 )
			{
				q = q*q + c;
				t++;
			}
			pixelValue = t;

			//---- COLOR MANIPULATION ----
		
			intermediateImage.set(x, y, pixelValue);
		}

		intermediateImage.copyTo(current_frame);

		current_frame.update();
	}

	//--------------------------------------
	// U T I L I T Y
	//--------------------------------------
	ofVec4f convertXY(float x, float y, float Range = 5.0) 
	{
		// Maps field grid to co-ordinate system
		x = ( x * Range/(xRes - 1) ) - Range/2.0;
		y = ( y * Range/(yRes - 1) ) - Range/2.0;
		ofVec4f number(x, y, 0, 0);
		return number;
	}

	int getIndex(int x, int y)
	{
	    return y*xRes + x;
	}

};

#endif