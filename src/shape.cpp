#include "../include/shape.h"

Shape::Shape(){

}

Shape::Shape(string fileName){
    this->importFromASCII(fileName);
}

bool Shape::importFromASCII(string fileName){
    ifstream file;
    file.open(fileName);
    cout << "Importing " << "\"" << fileName << "\"." << endl;
    string str;
    file >> str;
    if(str == "solid"){
        file >> _name;
    }

    while( !file.eof() ){
        file >> str;    // facet
        if(str == "endsolid")
            break;
        file >> str;    // normal
        Triangle triangle;
        file >> triangle.normal.x;
        file >> triangle.normal.y;
        file >> triangle.normal.z;
        file >> str;    // outer
        file >> str;    // loop
        for(int i=0; i<3; i++){
            file >> str;    // vertices
            file >> triangle.vertices[i].x;
            file >> triangle.vertices[i].y;
            file >> triangle.vertices[i].z;
        }
        this->_triangles.push_back(triangle);
        file >> str;    // endloop
        file >> str;    // endfacet
    }
    file >> str;
    file.close();
    cout << "\"" << fileName << "\"" << " succesfully imported" << endl;

    this->findOuterPoints();
    this->move(0,0); 
    return true;
}

bool Shape::exportAsASCII(string fileName){
    ofstream file;
    file.open(fileName);

    if(!file.is_open()){
        cout << "Could not open " << "\""<< fileName << "\"" << "named file." << endl; 
        return false;
    }
    
    cout << "Exporting " << fileName << endl;
    
    file << "solid ";
    file << this->_name << endl;

    for(int i=0; i<this->_triangles.size(); i++){
        file << " facet normal ";
        file << _triangles[i].normal.x << " ";
        file << _triangles[i].normal.y << " ";
        file << _triangles[i].normal.z << " " << endl;

        file << "  outer loop" << endl;
        for(int j=0; j<3; j++){
            file << "  vertex ";
            file << _triangles[i].vertices[j].x << " ";
            file << _triangles[i].vertices[j].y << " ";
            file << _triangles[i].vertices[j].z << " " << endl;
        }
        file << "  endloop" << endl;
        file << " endfacet" << endl << endl; 
    }
    file << "endsolid " << this->_name << endl;
    file.close();
    cout << "\"" << fileName << "\"" << " succesfully exported." << endl;
    return true;
}

void Shape::rotate(float x, float y, float z){
    // TODO: Implement rotation
}

void Shape::push(float x, float y, float z){
    vector<Triangle>::iterator iter = this->_triangles.begin();
    while(iter != this->_triangles.end()){
        iter->pushX(x);
        iter->pushY(y);
        iter->pushZ(z);
        iter++;
    }
    this->_outerPoints.min.x += x;
    this->_outerPoints.max.x += x;
    this->_outerPoints.min.y += y;
    this->_outerPoints.max.y += y;
    this->_outerPoints.min.z += z;
    this->_outerPoints.max.z += z;
}

void Shape::move(float x, float y){
    float dx = this->_outerPoints.max.x - this->_outerPoints.min.x;
    float dy = this->_outerPoints.max.y - this->_outerPoints.min.y;
    //cout << "dx: " << dx << " dy: " << dy << endl;
    this->push(-(this->_outerPoints.min.x + dx/2), -(this->_outerPoints.min.y + dy/2), -this->_outerPoints.min.z);
}

void Shape::move(float x, float y, float z){
    float dx = this->_outerPoints.max.x - this->_outerPoints.min.x;
    float dy = this->_outerPoints.max.y - this->_outerPoints.min.y;
    float dz = this->_outerPoints.max.z - this->_outerPoints.min.z;
    //cout << "dx: " << dx << " dy: " << dy << " dz: " << dz << endl;
    this->push(-(this->_outerPoints.min.x + dx/2), -(this->_outerPoints.min.y + dy/2), -(this->_outerPoints.min.z + dz/2));
}

void Shape::findOuterPoints(){
    this->_outerPoints.min.x = this->_triangles[0].vertices[0].x;
    this->_outerPoints.max.x = this->_triangles[0].vertices[0].x;

    this->_outerPoints.min.y = this->_triangles[0].vertices[0].y;
    this->_outerPoints.max.y = this->_triangles[0].vertices[0].y;

    this->_outerPoints.min.z = this->_triangles[0].vertices[0].z;
    this->_outerPoints.max.z = this->_triangles[0].vertices[0].z;

    for(auto triangle : _triangles){
        for(auto vertex : triangle.vertices){
            // Min x
            if(vertex.x < this->_outerPoints.min.x){
                this->_outerPoints.min.x = vertex.x;
            }
            // Max x
            if(vertex.x > this->_outerPoints.max.x){
                this->_outerPoints.max.x = vertex.x;
            }
            // Min y
            if(vertex.y < this->_outerPoints.min.y){
                this->_outerPoints.min.y = vertex.y;
            }
            // Max y
            if(vertex.y > this->_outerPoints.max.y){
                this->_outerPoints.max.y = vertex.y;
            }
            // Min z
            if(vertex.z < this->_outerPoints.min.z){
                this->_outerPoints.min.z = vertex.z;
            }
            // Max z
            if(vertex.z > this->_outerPoints.max.z){
                this->_outerPoints.max.z = vertex.z;
            }
        }
    }
}

void Shape::createOuterCube(){
    Triangle topFace;
    topFace.normal.x = 0;
    topFace.normal.y = 0;
    topFace.normal.z = 0;

    topFace.vertices[0].x = this->_outerPoints.min.x;
    topFace.vertices[0].y = this->_outerPoints.max.y;
    topFace.vertices[0].z = this->_outerPoints.max.z; 

    topFace.vertices[1].x = this->_outerPoints.min.x;
    topFace.vertices[1].y = this->_outerPoints.min.y;
    topFace.vertices[1].z = this->_outerPoints.max.z; 

    topFace.vertices[2].x = this->_outerPoints.max.x;
    topFace.vertices[2].y = this->_outerPoints.max.y;
    topFace.vertices[2].z = this->_outerPoints.max.z; 

    this->_triangles.push_back(topFace);
    // TODO: Create other faces
}

void Shape::combine(Shape s2){
    s2.push(this->getDx()/2 + s2.getDx()/2, 0, 0);
    for(auto triangle : s2._triangles){
        this->_triangles.push_back(triangle);
    }
    this->findOuterPoints();
    this->move(0,0);
}

float Shape::getDx(){
    return this->_outerPoints.max.x - this->_outerPoints.min.x;   
}

float Shape::getDy(){
    return this->_outerPoints.max.y - this->_outerPoints.min.y;   
}

float Shape::getDz(){
    return this->_outerPoints.max.z - this->_outerPoints.min.z;   
}
