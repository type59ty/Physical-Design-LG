#include "read_scl.h"
string ReadSCL::parser(string &line) {
    string token("");
    string::size_type index = 0;
    while (line.size() > 0) {
        if ((line[ index ] >= '0' && line[ index ] <= '9') ||
            (line[ index ] >= 'A' && line[ index ] <= 'Z') ||
            (line[ index ] >= 'a' && line[ index ] <= 'z')) {
            token += line[ index ];
            line.erase(line.begin());
        } else if (line[ index ] == '\0' || token.size() > 0)
            return token;
        else
            line.erase(line.begin());
    }
    return token;
}
void ReadSCL::read(string fname) {
    string name(fname);
    name = name + ".scl";
    ifstream file(name.c_str(), ios::in);
    int index(0);
    string line("");
    while (getline(file, line, '\n')) {
        string token = parser(line); // token
        if (token == "NumRows") {
            token = parser(line); // NumRows
            this->NumRows = atoi(token.c_str());
        } else if (token == "CoreRow") {
            getline(file, line, '\n');
            Row *row = new Row();
            row->index = index;
            token = parser(line); // Coordinate
            row->Coordinate = atoi(parser(line).c_str());
            getline(file, line, '\n');
            token = parser(line); // Height
            row->Height = atoi(parser(line).c_str());
            getline(file, line, '\n');
            token = parser(line); // Sitewidth
            row->Sitewidth = atoi(parser(line).c_str());
            getline(file, line, '\n');
            token = parser(line); // Sitespacing
            row->Sitespacing = atoi(parser(line).c_str());
            getline(file, line, '\n');
            token = parser(line); // Siteorient
            row->Siteorient = parser(line);
            getline(file, line, '\n');
            token = parser(line); // Sitesymmetry
            row->Sitesymmetry = parser(line);
            getline(file, line, '\n');
            token = parser(line); // SubrowOrigin
            row->SubrowOrigin = atoi(parser(line).c_str());
            token = parser(line); // NumSites
            row->NumSites = atoi(parser(line).c_str());
            row->SubrowRight = row->SubrowOrigin + row->NumSites * row->Sitespacing;
            this->RowList.push_back(row);
            this->RowMap.insert(pair<int, Row *>(row->Coordinate, row));
            getline(file, line, '\n');
            parser(line); // End
            ++index;
        }
    }
}
