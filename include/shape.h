/*
    Onur Sanır
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "triangle.h"
#include "point3f.h"

using namespace std;

struct OuterPoints{
    Point3f min;
    Point3f max;
};

class Shape{
public:
    Shape();
    Shape(string fileName);

    bool importFromASCII(string fileName);
    // TODO: Implement importFromBinary() function
    bool exportAsASCII(string fileName);
    // TODO: Implement exportAsBinary() function 

    void rotate(float x, float y, float z);
    void push(float x, float y, float z);
    void move(float x, float y);
    void move(float x, float y, float z);
    void findOuterPoints();
    void createOuterCube();
    void combine(Shape s2);

    float getDx();
    float getDy();
    float getDz();
private:
    vector<Triangle> _triangles;
    OuterPoints      _outerPoints;
    string           _name;
};