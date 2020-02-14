#ifndef RSHAPE_H
#define RSHAPE_H
#include <bits/stdc++.h>
using namespace std;

class Shape {
public:
    string shape_name;
    int x;
    int y;
    int width;
    int height;
};
class NonRectangularNodes {
public:
    string node_name;
    int num_shape;
    vector<Shape *> shapeList;
};
class ReadShape {
public:
    void read(string fname);
    string parser(string &);
    int NumNonRectangularNodes;
    vector<NonRectangularNodes *> NonRectangularNodesList;
    map<string, NonRectangularNodes *> ShapeMap;
};
#endif
