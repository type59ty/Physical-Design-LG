#ifndef CD_H
#define CD_H
#include <bits/stdc++.h>
using namespace std;

enum Movetype { movable, terminal, terminal_NI };
class Cell;
class Net;

class Offset {
public:
    float x;
    float y;
};

class Cell {
public:
    Cell();
    ~Cell();
    string node_name;
    int width;
    int height;
    int x;
    int y;
    float center_x;
    float center_y;
    Movetype movetype = movable;
    vector<Net *> NetList;
};


class Cells {
public:
    Cells() : NumNodes(0), NumTerminals(0){};
    ~Cells();
    int NumNodes;
    int NumTerminals;
    vector<string> TempArray; // store fixed node
    map<string, Cell *> CellArray;
};

class Net {
public:
    Net();
    ~Net();
    int npins;
    string net_name;
    vector<Cell *> CellList;

    vector<Offset *> OffsetList;
    map<string, Offset *> OffsetListmap;
};


class Nets {
public:
    int NumNets; // Total number of nets
    int NumPins; // Total number of pins
    map<string, Net *> NetArray;
};
#endif
