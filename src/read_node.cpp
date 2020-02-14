#include "read_node.h"
string ReadNode::parser(string &line) {
    string token("");
    string::size_type index = 0;
    while (line.size() > 0) {
        if ((line[ index ] >= '0' && line[ index ] <= '9') ||
            (line[ index ] >= 'A' && line[ index ] <= 'Z') ||
            (line[ index ] >= 'a' && line[ index ] <= 'z') || line[ index ] == '/') {
            token += line[ index ];
            line.erase(line.begin());
        } else if (line[ index ] == '\0' || token.size() > 0)
            return token;
        else
            line.erase(line.begin());
    }
    return token;
}

void ReadNode::read(string fname) {
    bool cellflag = false;
    string name(fname);
    name = name + ".nodes";
    ifstream file(name.c_str(), ios::in);
    string line("");
    while (getline(file, line, '\n')) {
        if (cellflag) {
            string node_name = parser(line); // cell name
            if (node_name.size() > 0) {
                Cell *cell = new Cell(); // new cell
                cell->node_name = node_name;
                cell->width = atoi(parser(line).c_str());
                cell->height = atoi(parser(line).c_str());

                string movetype = parser(line);
                if (movetype == "")
                    cell->movetype = movable;
                else if (movetype == "terminal") {
                    cell->movetype = terminal;
                    cells->TempArray.push_back(node_name);
                } else {
                    cell->movetype = terminal_NI;
                    cells->TempArray.push_back(node_name);
                }
                cells->CellArray.insert(pair<string, Cell *>(cell->node_name, cell));
            }
        } else {
            string token = parser(line);
            if (token == "NumNodes") {
                string token = parser(line);
                cells->NumNodes = atoi(token.c_str());
            } else if (token == "NumTerminals") {
                string token = parser(line);
                cells->NumTerminals = atoi(token.c_str());
                cellflag = true;
            }
        }
    }
}
