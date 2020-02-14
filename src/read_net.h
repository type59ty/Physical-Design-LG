#ifndef RNET_H
#define RNET_H
#include <bits/stdc++.h>
#include "ds.h"
using namespace std;

class ReadNet {
public:
    ReadNet();
    ReadNet(Cells *cells, Nets *nets) {
        this->cells = cells;
        this->nets = nets;
    };
    ~ReadNet();
    void read(string fname);
    string parser(string &);
    Cells *cells;
    Nets *nets;
    string net_name;
};
#endif
