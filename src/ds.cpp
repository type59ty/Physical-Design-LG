#include "ds.h"
Cell::Cell() {
    node_name = "";
    width = 0;
    height = 0;
    x = 0;
    y = 0;
    center_x = 0;
    center_y = 0;
    movetype = movable;
}
Cell::~Cell() {
    for (vector<Net *>::iterator it = NetList.begin(); it != NetList.end(); ++it) {
        delete (*it);
    }
    NetList.clear();
}
Net::Net() {
    npins = 0;
    net_name = "";
}
Net::~Net() {
    for (vector<Cell *>::iterator it = CellList.begin(); it != CellList.end(); ++it) {
        delete (*it);
    }
}
