#include "abacus.h"
Abacus::Abacus(Cells *cells, ReadLegal *LegalList, ReadSCL *Scl, ReadShape *ShapeList, string out_file) {
    this->LegalList = LegalList;
    this->Scl = Scl;
    this->ShapeList = ShapeList;
    this->cells = cells;
    this->out_file = out_file;
}
int Abacus::computeHPWL(Cell *cell, SubRow *subRow) {
    int Bestcost(0);
    for (unsigned int i = 0; i < cell->NetList.size(); ++i) {
        map<string, Offset *>::iterator it =
            cell->NetList[ i ]->OffsetListmap.find(cell->node_name);
        float cell_offset_x = cell->center_x + it->second->x;
        float cell_offset_y = cell->center_y + it->second->y;
        float LeftUpX(cell_offset_x), LeftUpY(cell_offset_y), RightUpX(cell_offset_x),
            RightUpY(cell_offset_y), LeftDownX(cell_offset_x), LeftDownY(cell_offset_y),
            RightDownX(cell_offset_x), RightDownY(cell_offset_y);
        for (unsigned int j = 0; j < cell->NetList[ i ]->CellList.size(); ++j) {
            if (cell->NetList[ i ]->CellList[ j ]->node_name != cell->node_name) {
                Cell *Tmpcell = cell->NetList[ i ]->CellList[ j ];
                if ((Tmpcell->y == cell->y) && subRow->SubrowOrigin <= Tmpcell->x &&
                    (Tmpcell->x + Tmpcell->width) <= subRow->SubrowRight) {
                    for (unsigned int k = 0; k < subRow->ClusterList.size(); ++k) {
                        unsigned int l(0);
                        for (; l < subRow->ClusterList[ k ]->CellList.size(); ++l) {
                            if (subRow->ClusterList[ k ]->CellList[ l ]->node_name == Tmpcell->node_name) {
                                Tmpcell = subRow->ClusterList[ k ]->CellList[ l ];
                                break;
                            }
                        }
                        if (j != subRow->ClusterList[ k ]->CellList.size()) {
                            break;
                        }
                    }
                    map<string, Offset *>::iterator TmpCellit =
                        cell->NetList[ i ]->OffsetListmap.find(Tmpcell->node_name);
                    float offset_x(Tmpcell->center_x + TmpCellit->second->x);
                    float offset_y(Tmpcell->center_y + TmpCellit->second->y);
                    if (cell_offset_x >= offset_x) {     // Left
                        if (cell_offset_y >= offset_y) { // Down
                            if (offset_x < LeftDownX) {
                                LeftDownX = offset_x;
                            }
                            if (offset_y < LeftDownY) {
                                LeftDownY = offset_y;
                            }
                        } else { // Up
                            if (offset_x < LeftUpX) {
                                LeftUpX = offset_x;
                            }
                            if (offset_y > LeftUpY) {
                                LeftUpY = offset_y;
                            }
                        }
                    } else {                             // Right
                        if (cell_offset_y >= offset_y) { // Down
                            if (offset_x > RightDownX) {
                                RightDownX = offset_x;
                            }
                            if (offset_y < RightDownY) {
                                RightDownY = offset_y;
                            }
                        } else { // Up
                            if (offset_x > RightUpX) {
                                RightUpX = offset_x;
                            }
                            if (offset_y > RightUpY) {
                                RightUpY = offset_y;
                            }
                        }
                    }
                } else if (Tmpcell->movetype != terminal_NI) {
                    float offset_x(Tmpcell->center_x + cell->NetList[ i ]->OffsetList[ j ]->x);
                    float offset_y(Tmpcell->center_y + cell->NetList[ i ]->OffsetList[ j ]->y);
                    if (cell_offset_x >= offset_x) {     // Left
                        if (cell_offset_y >= offset_y) { // Down
                            if (offset_x < LeftDownX) {
                                LeftDownX = offset_x;
                            }
                            if (offset_y < LeftDownY) {
                                LeftDownY = offset_y;
                            }
                        } else { // Up
                            if (offset_x < LeftUpX) {
                                LeftUpX = offset_x;
                            }
                            if (offset_y > LeftUpY) {
                                LeftUpY = offset_y;
                            }
                        }
                    } else {                             // Right
                        if (cell_offset_y >= offset_y) { // Down
                            if (offset_x > RightDownX) {
                                RightDownX = offset_x;
                            }
                            if (offset_y < RightDownY) {
                                RightDownY = offset_y;
                            }
                        } else { // Up
                            if (offset_x > RightUpX) {
                                RightUpX = offset_x;
                            }
                            if (offset_y > RightUpY) {
                                RightUpY = offset_y;
                            }
                        }
                    }
                } else {                                          // terminal_NI
                    if (cell_offset_x >= Tmpcell->center_x) {     // Left
                        if (cell_offset_y >= Tmpcell->center_y) { // Down
                            if (Tmpcell->center_x < LeftDownX) {
                                LeftDownX = Tmpcell->center_x;
                            }
                            if (Tmpcell->center_y < LeftDownY) {
                                LeftDownY = Tmpcell->center_y;
                            }
                        } else { // Up
                            if (Tmpcell->center_x < LeftUpX) {
                                LeftUpX = Tmpcell->center_x;
                            }
                            if (Tmpcell->center_y > LeftUpY) {
                                LeftUpY = Tmpcell->center_y;
                            }
                        }
                    } else {                                      // Right
                        if (cell_offset_y >= Tmpcell->center_y) { // Down
                            if (Tmpcell->center_x > RightDownX) {
                                RightDownX = Tmpcell->center_x;
                            }
                            if (Tmpcell->center_y < RightDownY) {
                                RightDownY = Tmpcell->center_y;
                            }
                        } else { // Up
                            if (Tmpcell->center_x > RightUpX) {
                                RightUpX = Tmpcell->center_x;
                            }
                            if (Tmpcell->center_y > RightUpY) {
                                RightUpY = Tmpcell->center_y;
                            }
                        }
                    }
                }
            }
        }
        float LeftX, RightX, UpY, DownY;
        if (LeftUpX < LeftDownX)
            LeftX = LeftUpX;
        else
            LeftX = LeftDownX;
        if (RightUpX > RightDownX)
            RightX = RightUpX;
        else
            RightX = RightDownX;
        if (LeftUpY > RightUpY)
            UpY = LeftUpY;
        else
            UpY = RightUpY;
        if (LeftDownY < RightDownY)
            DownY = LeftDownY;
        else
            DownY = RightDownY;
        Bestcost += (int)((RightX - LeftX) + (UpY - DownY)); // LeftUp
    }
    return Bestcost;
}

void Abacus::Output() {
    ofstream OFS;
    OFS.open(out_file);
    for (unsigned int i = 0; i < Scl->RowList.size(); ++i) {
        for (unsigned int j = 0; j < Scl->RowList[ i ]->SubRowList.size(); ++j) {
            for (unsigned int k = 0; k < Scl->RowList[ i ]->SubRowList[ j ]->ClusterList.size(); ++k) {
                for (unsigned int l = 0; l < Scl->RowList[ i ]->SubRowList[ j ]->ClusterList[ k ]->CellList.size(); ++l) {
                    Cell *cell = Scl->RowList[ i ]->SubRowList[ j ]->ClusterList[ k ]->CellList[ l ];
                    OFS << "\t" << cell->node_name << "\t" << cell->x << "\t" << cell->y << "\t:\tN" << endl;
                }
            }
        }
    }
    // terminal && terminal_NI
    for (unsigned int i = 0; i < cells->TempArray.size(); ++i) {
        map<string, Cell *>::iterator it = cells->CellArray.find(cells->TempArray[ i ]);
        Cell *cell = it->second;
        if (cell->movetype != movable) {
            string str;
            if (cell->movetype == terminal)
                str = "FIXED";
            else
                str = "FIXED_NI";
            OFS << "\t" << cell->node_name << "\t" << cell->x << "\t" << cell->y << "\t:\tN\t/" << str << endl;
        } else {
            OFS << "\t" << cell->node_name << "\t" << cell->x << "\t" << cell->y << "\t:\tN" << endl;
        }
    }
    OFS.close();
}
void Abacus::SliceNewRow() {
    for (unsigned int i = 0; i < ShapeList->NonRectangularNodesList.size(); ++i) {
        string node_name = ShapeList->NonRectangularNodesList[ i ]->node_name;
        for (unsigned int j = 0; j < ShapeList->NonRectangularNodesList[ i ]->shapeList.size();
             ++j) {
            map<int, Row *>::iterator itRow = Scl->RowMap.find(
                ShapeList->NonRectangularNodesList[ i ]->shapeList[ j ]->y); // i'th Row
            SubRow *subrow = new SubRow();
            int x = ShapeList->NonRectangularNodesList[ i ]->shapeList[ j ]->x;
            int width = ShapeList->NonRectangularNodesList[ i ]->shapeList[ j ]->width;
            subrow->Coordinate = ShapeList->NonRectangularNodesList[ i ]->shapeList[ j ]->y;  // Y
            subrow->Height = ShapeList->NonRectangularNodesList[ i ]->shapeList[ j ]->height; // H
            subrow->SubrowOrigin = x;
            subrow->SubrowRight = x + width;
            itRow->second->priority_SubRow.push(subrow);
        }
    }
    // terminal && terminal_NI
    for (unsigned int i = 0; i < cells->TempArray.size(); ++i) {
        string node_name = cells->TempArray[ i ];
        map<string, NonRectangularNodes *>::iterator itShap = ShapeList->ShapeMap.find(node_name);
        if (itShap == ShapeList->ShapeMap.end()) {
            map<string, Cell *>::iterator itCell =
                cells->CellArray.find(node_name); // width, height
            Cell *cell = itCell->second;
            if (cell->movetype == terminal) {
                int width = cell->width;
                int height = cell->height;
                int x = cell->x;
                int y = cell->y;
                int NumRow = height / (Scl->RowList.front())->Height;
                for (int j = 0; j < NumRow; ++j) {
                    map<int, Row *>::iterator itRow = Scl->RowMap.find(y); // i'th Row
                    SubRow *subrow = new SubRow();
                    subrow->Coordinate = itRow->second->Coordinate; // Y
                    subrow->Height = itRow->second->Height;         // H
                    subrow->SubrowOrigin = x;
                    subrow->SubrowRight = x + width;
                    itRow->second->priority_SubRow.push(subrow);
                    y = y + itRow->second->Height;
                }
            }
        }
    }
    for (unsigned int i = 0; i < Scl->RowList.size(); ++i) {
        int rowOrigin = Scl->RowList[ i ]->SubrowOrigin, tmpSubrowOrigin = 0;
        while (!Scl->RowList[ i ]->priority_SubRow.empty()) {
            SubRow *top = Scl->RowList[ i ]->priority_SubRow.top();
            if (rowOrigin == top->SubrowOrigin) { // consequence
                rowOrigin = top->SubrowRight;
                Scl->RowList[ i ]->priority_SubRow.pop();
                delete top;
            } else {
                tmpSubrowOrigin = top->SubrowOrigin;
                top->SubrowOrigin = rowOrigin;
                rowOrigin = top->SubrowRight;
                top->SubrowRight = tmpSubrowOrigin;
                Scl->RowList[ i ]->SubRowList.push_back(top);
                Scl->RowList[ i ]->priority_SubRow.pop();
            }
        }
        if (rowOrigin < Scl->RowList[ i ]->SubrowRight) {
            SubRow *subrow = new SubRow();
            subrow->Coordinate = Scl->RowList[ i ]->Coordinate; // Y
            subrow->Height = Scl->RowList[ i ]->Height;         // H
            // subrow->Sitespacing = Scl->RowList[i]->Sitespacing;
            subrow->SubrowOrigin = rowOrigin;
            subrow->SubrowRight = Scl->RowList[ i ]->SubrowRight;
            Scl->RowList[ i ]->SubRowList.push_back(subrow);
        }
    }
}
void Abacus::AddCluster(Cluster *PreC, Cluster *C) {
    for (unsigned int i = 0; i < C->CellList.size(); ++i) {
        PreC->CellList.push_back(C->CellList[ i ]);
    }
    PreC->Ec = PreC->Ec + C->Ec;
    PreC->Qc = PreC->Qc + C->Qc - (C->Ec * PreC->Wc);
    PreC->Wc = PreC->Wc + C->Wc;
}
void Abacus::Collapse(Cluster *C, SubRow *Row, Cell *cell) {
    /* recursively collapsed with its predecessor
       cluster as long as the clusters are overlapping*/
    // Place cluster c:
    C->Xc = C->Qc / C->Ec;
    // Limit position between xmin and xmax − wc(c)
    if (C->Xc < Row->SubrowOrigin)
        C->Xc = Row->SubrowOrigin;
    if (C->Xc > (Row->SubrowRight - C->Wc))
        C->Xc = (Row->SubrowRight - C->Wc);
    // Overlap between c and its predecessor c'?:
    if ((C->index) > 0) {
        Cluster *PreCluster = Row->ClusterList[ (C->index) - 1 ];
        if ((PreCluster->Xc + PreCluster->Wc) > C->Xc) {
            // Merge cluster c to c':
            AddCluster(PreCluster, C);
            Row->ClusterList.pop_back(); // Remove cluster c;
            Collapse(PreCluster, Row, cell);
        }
    }
}

void Abacus::AddCell(Cluster *C, Cell *cell) {
    // iterative calculation of Ec(c), Wc(c), and Qc(c)
    C->CellList.push_back(cell); // nlast (c) ← i;
    int Ec = C->Ec;
    int Wc = C->Wc;
    int Qc = C->Qc;
    C->Ec = Ec + cell->NetList.size();
    C->Qc = Qc + cell->NetList.size() * (cell->x - Wc);
    C->Wc = Wc + cell->width;
}
void Abacus::PlaceRow(SubRow *subRow, Cell *cell) { // trial
    // determine clusters and their optimal positions Xc(c)
    int overlap = 0;
    Cluster *lastC;
    if (!subRow->ClusterList.empty()) {
        lastC = subRow->ClusterList.back();
        overlap = lastC->Xc + lastC->Wc;
    }
    if (subRow->ClusterList.empty() || overlap <= cell->x) {
        // subRow->CellRowList.push_back(tmpCell);
        Cluster *newCluster = new Cluster(); // Create new cluster c;
        newCluster->Ec = 0;                  // Init ec(c),wc(c), qc(c) to zero;
        newCluster->Wc = 0;
        newCluster->Qc = 0;
        newCluster->Xc = cell->x; // xc(c) ← x'(i);
        newCluster->index = subRow->ClusterList.size();
        AddCell(newCluster, cell);
        subRow->ClusterList.push_back(newCluster);
    } else {
        // subRow->CellRowList.push_back(cell);
        AddCell(lastC, cell);
        Collapse(lastC, subRow, cell);
    }
    for (unsigned int i = 0; i < subRow->ClusterList.size(); ++i) {
        int X = subRow->ClusterList[ i ]->Xc;
        for (unsigned int j = 0; j < subRow->ClusterList[ i ]->CellList.size(); ++j) {
            subRow->ClusterList[ i ]->CellList[ j ]->x = X;
            subRow->ClusterList[ i ]->CellList[ j ]->center_x =
                (float)subRow->ClusterList[ i ]->CellList[ j ]->x +
                ((float)subRow->ClusterList[ i ]->CellList[ j ]->width / 2);
            X = X + subRow->ClusterList[ i ]->CellList[ j ]->width;
        }
    }
}

bool Abacus::start(Row *tmpRow, bool trial, Cell *cell, int &Bestcost, int &BestRow) {
    unsigned int SubrowIndex = 0;
    int index = -1;
    int total = 0;
    for (; SubrowIndex < tmpRow->SubRowList.size(); ++SubrowIndex) {
        if (tmpRow->SubRowList[ SubrowIndex ]->SubrowOrigin <= cell->x &&
            (cell->x + cell->width) <= tmpRow->SubRowList[ SubrowIndex ]->SubrowRight) {
            index = SubrowIndex;
            break;
        }
    }
    if (index == -1) {
        return 0;
    }
    SubRow *subRow = tmpRow->SubRowList[ index ];
    if (!trial) {
        for (unsigned int i = 0; i < tmpRow->SubRowList[ index ]->ClusterList.size(); ++i) {
            total += tmpRow->SubRowList[ index ]->ClusterList[ i ]->Wc;
        }
        if ((total + cell->width) <= (subRow->SubrowRight - subRow->SubrowOrigin)) {
            Cell *PlaceCell = new Cell();
            PlaceCell->node_name = cell->node_name;
            PlaceCell->width = cell->width;
            PlaceCell->x = cell->x;
            PlaceCell->y = subRow->Coordinate;
            PlaceCell->center_x = cell->center_x;
            PlaceCell->center_y = (float)PlaceCell->y + ((float)cell->height / 2);
            PlaceCell->NetList = cell->NetList; // true
            int overlap(0);
            Cluster *lastC;
            if (!subRow->ClusterList.empty()) {
                lastC = subRow->ClusterList.back();
                overlap = lastC->Xc + lastC->Wc;
            }
            if (subRow->ClusterList.empty() || overlap <= cell->x) {
                Cluster *newCluster = new Cluster(); // Create new cluster c;
                newCluster->Ec = 0;                  // Init ec(c),wc(c), qc(c) to zero;
                newCluster->Wc = 0;
                newCluster->Qc = 0;
                newCluster->Xc = cell->x; // xc(c) ← x'(i);
                newCluster->index = subRow->ClusterList.size();
                AddCell(newCluster, PlaceCell);
                subRow->ClusterList.push_back(newCluster);
                int cost = computeHPWL(PlaceCell, subRow);
                if (cost < Bestcost) {
                    Bestcost = cost;
                    BestRow = tmpRow->index;
                }
                PlaceCell->NetList.clear();
                delete subRow->ClusterList.back();
                subRow->ClusterList.pop_back();
            } else {
                SubRow *tmpSubRow = new SubRow();
                tmpSubRow->Coordinate = subRow->Coordinate;
                tmpSubRow->SubrowOrigin = subRow->SubrowOrigin;
                tmpSubRow->SubrowRight = subRow->SubrowRight;
                for (unsigned int i = 0; i < subRow->ClusterList.size(); ++i) {
                    Cluster *cluster = new Cluster();
                    cluster->index = subRow->ClusterList[ i ]->index;
                    cluster->Ec = subRow->ClusterList[ i ]->Ec;
                    cluster->Wc = subRow->ClusterList[ i ]->Wc;
                    cluster->Qc = subRow->ClusterList[ i ]->Qc;
                    cluster->Xc = subRow->ClusterList[ i ]->Xc;
                    for (unsigned int j = 0; j < subRow->ClusterList[ i ]->CellList.size(); ++j) {
                        Cell *Tmpcell = new Cell();
                        Tmpcell->node_name = subRow->ClusterList[ i ]->CellList[ j ]->node_name;
                        Tmpcell->width = subRow->ClusterList[ i ]->CellList[ j ]->width;
                        Tmpcell->x = subRow->ClusterList[ i ]->CellList[ j ]->x;
                        Tmpcell->y = subRow->ClusterList[ i ]->CellList[ j ]->y;
                        Tmpcell->movetype = subRow->ClusterList[ i ]->CellList[ j ]->movetype;
                        Tmpcell->center_x = subRow->ClusterList[ i ]->CellList[ j ]->center_x;
                        Tmpcell->center_y = subRow->ClusterList[ i ]->CellList[ j ]->center_y;
                        cluster->CellList.push_back(Tmpcell);
                    }
                    tmpSubRow->ClusterList.push_back(cluster);
                }
                lastC = tmpSubRow->ClusterList.back();
                AddCell(lastC, PlaceCell);
                Collapse(lastC, tmpSubRow, PlaceCell);
                for (unsigned int i = 0; i < tmpSubRow->ClusterList.size(); ++i) {
                    int X = tmpSubRow->ClusterList[ i ]->Xc;
                    for (unsigned int j = 0; j < tmpSubRow->ClusterList[ i ]->CellList.size();
                         ++j) {
                        tmpSubRow->ClusterList[ i ]->CellList[ j ]->x = X;
                        tmpSubRow->ClusterList[ i ]->CellList[ j ]->center_x =
                            (float)tmpSubRow->ClusterList[ i ]->CellList[ j ]->x +
                            ((float)tmpSubRow->ClusterList[ i ]->CellList[ j ]->width / 2);
                        X = X + tmpSubRow->ClusterList[ i ]->CellList[ j ]->width;
                    }
                }
                int cost = computeHPWL(PlaceCell, tmpSubRow);
                if (cost < Bestcost) {
                    Bestcost = cost;
                    BestRow = tmpRow->index;
                }
                PlaceCell->NetList.clear();
                delete tmpSubRow;
            }
        } else {
            return 0;
        }
    } else { // final
        cell->y = subRow->Coordinate;
        cell->center_y = (float)cell->y + ((float)cell->height / 2);
        PlaceRow(subRow, cell);
    }
    return 1;
}

void Abacus::Legalizing() {
    while (!LegalList->priority_q.empty()) {
        Cell *cell = LegalList->priority_q.top(); // global position
        if (cell->movetype != movable) {
            LegalList->priority_q.pop();
            continue;
        }
        int Bestcost = 2147483647;
        int BestRow = 0;
        int index = 0;
        map<int, Row *>::iterator itRow = Scl->RowMap.find(cell->y); // i'th Row

        index = itRow->second->index;
        start(Scl->RowList[ index ], false, cell, Bestcost, BestRow);

        // try to place row
        bool flag(true);
        int range(1);
        while (flag == true) {
            for (unsigned int i = 0; i < 7; ++i) {
                if ((index + range) < Scl->NumRows) {
                    if (start(Scl->RowList[ index + range ], false, cell, Bestcost, BestRow)) {
                        flag = false;
                    }
                }
                if ((index - range) >= 0) {
                    if (start(Scl->RowList[ index - range ], false, cell, Bestcost, BestRow)) {
                        flag = false;
                    }
                }
                range += 4;
            }
        }
        // place best row
        start(Scl->RowList[ BestRow ], true, cell, Bestcost, BestRow); // final
        LegalList->priority_q.pop();
    }
    Output();
}
