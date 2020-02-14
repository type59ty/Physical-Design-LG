// abacus.h
#ifndef ABACUS
#define ABACUS
#include "ds.h"
#include "read_legal.h"
#include "read_scl.h"
#include "read_shape.h"
#include <bits/stdc++.h>
using namespace std;

class Abacus {
public:
    Abacus(Cells *cells, ReadLegal *LegalList, ReadSCL *Scl, ReadShape *ShapeList, string out_file);
    void Legalizing();
    void SliceNewRow();
    int computeHPWL(Cell *cell, SubRow *subRow);
    bool start(Row *, bool, Cell *cell, int &Bestcost, int &BestRow);
    void PlaceRow(SubRow *subRow, Cell *cell);
    void AddCell(Cluster *C, Cell *cell);
    void AddCluster(Cluster *PreC, Cluster *C);
    void Collapse(Cluster *C, SubRow *Row, Cell *);
    void Output();
    ReadLegal *LegalList;
    ReadSCL *Scl;
    ReadShape *ShapeList;
    Cells *cells;
    string out_file;
};
#endif
