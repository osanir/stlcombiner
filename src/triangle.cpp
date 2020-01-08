#include "../include/triangle.h"

void Triangle::pushX(float x){
	vertices[0].x += x;
	vertices[1].x += x;
	vertices[2].x += x;
}

void Triangle::pushY(float y){
	vertices[0].y += y;
	vertices[1].y += y;
	vertices[2].y += y;
}
void Triangle::pushZ(float z){
	vertices[0].z += z;
	vertices[1].z += z;
	vertices[2].z += z;
}