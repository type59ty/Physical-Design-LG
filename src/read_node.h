#ifndef RNODE_H
#define RNODE_H
#include "ds.h"
#include <bits/stdc++.h>
using namespace std;

class ReadNode {
public:
    ReadNode();
    ReadNode(Cells *cells) {
        this->cells = cells;
    };
    void read(string fname);
    string parser(string &);
    Cells *cells;
};
#endif
