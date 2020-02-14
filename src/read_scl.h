#ifndef RSCL_H
#define RSCL_H
#include "ds.h"
#include <bits/stdc++.h>
using namespace std;

class Cluster {
public:
    ~Cluster() {
        for (vector<Cell *>::iterator it = CellList.begin(); it != CellList.end(); ++it) {
            delete (*it);
        }
        CellList.clear();
    }
    int index;
    int Ec; // Total weight
    int Wc; // Total width
    int Qc; // optimal position
    int Xc; // Optimal position (lower left corner)
    vector<Cell *> CellList;
};

class SubRow {
public:
    ~SubRow() {
        for (vector<Cluster *>::iterator it = ClusterList.begin(); it != ClusterList.end(); ++it) {
            delete (*it);
        }
        ClusterList.clear();
    }
    int Coordinate;
    int Height;
    int SubrowOrigin; // x
    int SubrowRight;  // x + width
    vector<Cluster *> ClusterList;
};

struct SubRowcmp {
    bool operator()(SubRow const *a, SubRow const *b) {
        return a->SubrowOrigin > b->SubrowOrigin;
    }
};
class Row {
public:
    int index;
    int Coordinate; // Y-coordinate of the bottom edge of the circuit row
    int Height;
    int Sitewidth;
    int Sitespacing;
    string Siteorient;
    string Sitesymmetry;
    int SubrowOrigin; // X-coordinate of the left edge of the subrow
    int NumSites;
    int SubrowRight; // SubrowOrigin + NumSites*Sitespacing
    priority_queue<SubRow *, vector<SubRow *>, SubRowcmp> priority_SubRow;
    vector<SubRow *> SubRowList;
};
class ReadSCL {
public:
    void read(string fname);
    string parser(string &);
    int NumRows;
    vector<Row *> RowList;
    map<int, Row *> RowMap;

private:
};
#endif
