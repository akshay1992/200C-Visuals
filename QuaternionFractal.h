#ifndef QUATERNION_FRACTAL
#define QUATERNION_FRACTAL

#include "FloatImage.h"
#include "COLOR_FIELD_2D.h"
#include "VEC4F.h"

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
		static COLOR_FIELD_2D field(xRes, yRes);

		static float inc = 0;
		static VEC4F z(0,0,0,0);
		loop(xRes, yRes)
		{
			VEC4F q = convertXY(x, y, 2.5) + z;
			VEC4F c (-0.450,-0.447,0.181,0.306);
			int t = 0;
			while( q.magnitude() < 2.0 && t<50 )
			{
				q = mul(q,q) + c;
				t++;
			}
			field(x, y) = t - log(q.magnitude()) / pow(2, t);


		   if ((t%2) == 0) 
			{ 
			 VEC3F color(t + 2.5 - log2(log2(q.magnitudeSq())), 0.2 * rand()/RAND_MAX, inc*t);
	//		 field(x,y) = bch2RGB(color);
			}
			else 
		     {
			 field(x, y) = 0;
		     };

		}

		z[2]= 0.5*sin(inc+=0.01);
		z[3]= 0.2*sin(inc+=0.05);
		z[1]= 0.45*sin(inc+=0.01);

		z[1] += 0.005;

		field.normalize();

		loop(xRes, yRes) 
		{
			current_frame.getPixelsRef()[getIndex(x, yRes-y)] = (int) field(x, y).r*255.0f;
		}

		current_frame.update();
	}

	//--------------------------------------
	// U T I L I T Y
	//--------------------------------------
	VEC4F convertXY(float x, float y, float Range = 5.0) 
	{
		// Maps field grid to co-ordinate system
		x = ( x * Range/(xRes - 1) ) - Range/2.0;
		y = ( (yRes-y) * Range/(yRes - 1) ) - Range/2.0;
		VEC4F number(x, y, 0, 0);
		return number;
	}

	int getIndex(int x, int y)
	{
	    return y*xRes + x;
	}
};

#endif