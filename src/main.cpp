#include "abacus.h"
#include "read_legal.h"
#include "read_net.h"
#include "read_node.h"
#include "read_scl.h"
#include "read_shape.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    string fname = argv[2];
    string out_file = argv[4];
    clock_t start, end;
    start = clock();

    cout << "--------Reading files--------" << endl;

    Cells *cells = new Cells();
    Nets *nets = new Nets();

    cout << "Reading node file..." << endl;
    ReadNode *readNode = new ReadNode(cells);
    readNode->read(fname);

    cout << "Reading net file..." << endl;
    ReadNet *readNet = new ReadNet(cells, nets);
    readNet->read(fname);

    cout << "Reading scl file..." << endl;
    ReadSCL *readSCL = new ReadSCL();
    readSCL->read(fname);

    cout << "Reading shape file..." << endl;
    ReadShape *readShape = new ReadShape();
    readShape->read(fname);

    cout << "Reading legal file..." << endl;
    ReadLegal *readLegal = new ReadLegal(cells);
    readLegal->read(fname);

    Abacus *abacus = new Abacus(cells, readLegal, readSCL, readShape, out_file);
    abacus->SliceNewRow();

    cout << "--------Legalizing--------" << endl;
    abacus->Legalizing();
    cout << "Finish!" << endl;

    end = clock();
    float sec = ((float)end - (float)start) / CLOCKS_PER_SEC;
    cout << "Runtime: " <<sec << " seconds" << endl;

    return 0;
}
