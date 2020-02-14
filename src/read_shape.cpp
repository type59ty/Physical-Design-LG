#include "read_shape.h"
string ReadShape::parser(string &line) {
    string token("");
    string::size_type index = 0;
    while (line.size() > 0) {
        if ((line[ index ] >= '0' && line[ index ] <= '9') ||
            (line[ index ] >= 'A' && line[ index ] <= 'Z') ||
            (line[ index ] >= 'a' && line[ index ] <= 'z') || line[ index ] == '/' ||
            line[ index ] == '_') {
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
void ReadShape::read(string fname) {
    string name(fname);
    name = name + ".shapes";
    ifstream file(name.c_str(), ios::in);
    string line("");
    while (getline(file, line, '\n')) {
        string token = parser(line); // token or cell's name
        if (token == "NumNonRectangularNodes") {
            this->NumNonRectangularNodes = atoi(parser(line).c_str());
        } else if (token != "" && token != "shapes" && token != "#") {
            NonRectangularNodes *nonRectangularNodes = new NonRectangularNodes();
            nonRectangularNodes->node_name = token;
            nonRectangularNodes->num_shape = atoi(parser(line).c_str());
            NonRectangularNodesList.push_back(nonRectangularNodes);
            ShapeMap.insert(pair<string, NonRectangularNodes *>(nonRectangularNodes->node_name,
                                                                nonRectangularNodes));
            for (int i = 0; i < nonRectangularNodes->num_shape; ++i) {
                getline(file, line, '\n');
                Shape *shape = new Shape();
                shape->shape_name = parser(line);
                shape->x = atoi(parser(line).c_str());
                shape->y = atoi(parser(line).c_str());
                shape->width = atoi(parser(line).c_str());
                shape->height = atoi(parser(line).c_str());
                NonRectangularNodesList.back()->shapeList.push_back(shape);
            }
        }
    }
}
