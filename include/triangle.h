#include "point3f.h"

struct Triangle{
	Point3f normal;
	Point3f vertices[3];
	
	void pushX(float x);
	void pushY(float y);
	void pushZ(float z);
};

