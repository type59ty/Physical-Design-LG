#include "read_legal.h"
string ReadLegal::parser(string &line) {
    string token("");
    string::size_type index = 0;
    while (line.size() > 0) {
        if ((line[ index ] >= '0' && line[ index ] <= '9') ||
            (line[ index ] >= 'A' && line[ index ] <= 'Z') ||
            (line[ index ] >= 'a' && line[ index ] <= 'z') || line[ index ] == '/') {
            token += line[ index ];
            line.erase(line.begin());
        } else if (line[ index ] == '#') {
            token += line[ index ];
            line.erase(line.begin());
            return token;
        } else if (line[ index ] == '\0' || token.size() > 0)
            return token;
        else
            line.erase(line.begin());
    }
    return token;
}
void ReadLegal::read(string fname) {
    string name = fname;
    name = name + ".legal";
    ifstream file(name.c_str(), ios::in);
    string line("");
    while (getline(file, line, '\n')) {
        string token = parser(line); // token or cell's name
        if (token == "UCLA" || token == "#" || token == "")
            continue;
        map<string, Cell *>::iterator it = cells->CellArray.find(token);
        Cell *cell = it->second;
        cell->x = atoi(parser(line).c_str());
        cell->y = atoi(parser(line).c_str());
        if (cell->movetype != terminal_NI) {
            cell->center_x = (float)cell->x + ((float)cell->width / 2);
            cell->center_y = (float)cell->y + ((float)cell->height / 2);
        } else {
            cell->center_x = (float)cell->x;
            cell->center_y = (float)cell->y;
        }
        priority_q.push(cell);
        LegalMap.insert(pair<string, Cell *>(cell->node_name, cell));
    }
}
