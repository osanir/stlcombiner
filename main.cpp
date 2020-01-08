#include <iostream>
#include "include/shape.h"

using namespace std;

int main(int argc, char *argv[]){
    if(argc < 4){
        cout << "Usage: \n\t program <source_1> <source_2> ... <source_n> <destination>" << endl;
        return 0;
    }
    Shape shape;
    shape.importFromASCII(argv[1]);
    for(int i=2; i<argc-1; i++){
        Shape s2(argv[i]);
        shape.combine(s2);
    }
    shape.exportAsASCII(argv[argc-1]);
    return 0;
}