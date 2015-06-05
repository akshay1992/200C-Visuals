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

	void init(int xResolution, int yResolution)
	{
		xRes = xResolution;
		yRes = yResolution;
		current_frame.allocate(xRes, yRes, OF_IMAGE_GRAYSCALE);
	}	

	void draw(void)
	{
		current_frame.draw(0,0);
	}
	
	void update(void)
	{
		static FloatImage intermediateImage(xRes, yRes);
		
		static float inc=0;
		static ofVec4f z(0, 0, 0, 0);

		float max=0;
		loop(xRes, yRes)
		{
			float pixelValue;

			// ---- FRACTAL GENERATION ----
			ofVec4f q = convertXY(x, y, 2.5) + z;
			ofVec4f c (-0.450,-0.447,0.181,0.306);
			int t = 0;
			while( q.length() < 2.0 && t<50 )
			{
				q = q.dot(q) + c;
				t++;
			}
			
			pixelValue = t - log(q.length()) / pow(2, t);

			//---- COLOR MANIPULATION ----
			if ((t%2) == 0) 
			{ 
			 // VEC3F color(t + 2.5 - log2(log2(q.lengthSquared())), 0.2 * rand()/RAND_MAX, inc*t);
			 // field(x,y) = bch2RGB(color);
			}
			else 
			{
			 pixelValue = 0;
			}

			intermediateImage.set(x, y, pixelValue);

			// current_frame.getPixelsRef()[getIndex(x, y)] = pixelValue;
		}

		intermediateImage.copyTo(current_frame);

		z[2]= 0.5*sin(inc+=0.01);
		z[3]= 0.2*sin(inc+=0.05);
		z[1]= 0.45*sin(inc+=0.01);

		z[1] += 0.005;
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