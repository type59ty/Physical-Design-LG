#ifndef RLEG_H
#define RLEG_H
#include "ds.h"
#include <bits/stdc++.h>
using namespace std;

struct Xcmp {
    bool operator()(Cell const *a, Cell const *b) {
        return a->x > b->x;
    }
};

class ReadLegal {
public:
    ReadLegal(Cells *cells) {
        this->cells = cells;
    };
    void read(string fname);
    string parser(string &);
    priority_queue<Cell *, vector<Cell *>, Xcmp> priority_q;
    map<string, Cell *> LegalMap;
    Cells *cells;
};
#endif
