#include "CoordinatesToXYZ.h"


#define PI 3.141592654

MyPoint CoordinatesToXYZ(float lon, float lat, float Radius)
{
	MyPoint point;
	float theta = lon * PI /180;
	float phi = lat * PI / 180;
	point.x = Radius * cos(phi) * sin(theta);
	point.y = Radius * cos(phi) * cos(theta);
	point.z = Radius * sin(phi);
	return point;
}