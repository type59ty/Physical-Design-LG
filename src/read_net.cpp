#include "read_net.h"
string ReadNet::parser(string &line) {
    string token("");
    string::size_type index = 0;
    while (line.size() > 0) {
        if ((line[ index ] >= '0' && line[ index ] <= '9') ||
            (line[ index ] >= 'A' && line[ index ] <= 'Z') ||
            (line[ index ] >= 'a' && line[ index ] <= 'z') || line[ index ] == '/' ||
            line[ index ] == '.') {
            token += line[ index ];
            line.erase(line.begin());
        } else if (line[ index ] == '\0' || token.size() > 0)
            return token;
        else
            line.erase(line.begin());
    }
    return token;
}

void ReadNet::read(string fname) {
    bool netDegree = false;
    string name(fname);
    name = name + ".nets";
    ifstream file(name.c_str(), ios::in);
    string line("");
    float offset_x(0.0);
    float offset_y(0.0);
    while (getline(file, line, '\n')) {
        if (netDegree) {
            string token = parser(line);
            if (token == "NetDegree") {
                Net *net = new Net;
                net->npins = atoi(parser(line).c_str());
                this->net_name = parser(line);
                net->net_name = this->net_name;
                nets->NetArray.insert(pair<string, Net *>(net->net_name, net));
            } else if (token.size() > 0) {
                Cell *cell = cells->CellArray[ token ]; // cell name
                parser(line);
                offset_x = atof(parser(line).c_str());
                offset_y = atof(parser(line).c_str());
                map<string, Net *>::iterator it = nets->NetArray.find(this->net_name);
                cell->NetList.push_back(it->second);
                it->second->CellList.push_back(cell);
                Offset *offset = new Offset();
                offset->x = offset_x;
                offset->y = offset_y;
                it->second->OffsetList.push_back(offset);
                it->second->OffsetListmap.insert(
                    pair<string, Offset *>(cell->node_name, offset));
            }
        } else {
            string token = parser(line);
            if (token == "NumNets") {
                string token = parser(line);
                nets->NumNets = atoi(token.c_str());
            } else if (token == "NumPins") {
                string token = parser(line);
                nets->NumPins = atoi(token.c_str());
                netDegree = true;
            }
        }
    }
}
