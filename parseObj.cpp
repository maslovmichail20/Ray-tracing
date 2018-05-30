#include "parseObj.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void parseObj(char* fileName,
              vector<double>* minCoords,
              vector<double>* maxCoords,
              vector<vector<double>>* vertexes,
              vector<vector<double>>* normals,
              vector<vector<int>>* figures
) {

    double minX = 100; double maxX = -100;
    double minY = 100; double maxY = -100;
    double minZ = 100; double maxZ = -100;

    ifstream input(fileName);
    if (input.is_open()) {
        string buffer;
        vector<double> emptyDouble;
        vector<int> emptyInt;

        while (getline(input, buffer)) {
            if (buffer[0] == 'v') {
                if (buffer[1] == ' ') {
                    char *ptr;
                    size_t found = buffer.find(' ');

                    double x = strtod(buffer.substr(found).c_str(), &ptr);
                    emptyDouble.push_back(x);
                    minX = minX < x ? minX : x;
                    maxX = maxX > x ? maxX : x;

                    double y = strtod(ptr, &ptr);
                    emptyDouble.push_back(y);
                    minY = minY < y ? minY : y;
                    maxY = maxY > y ? maxY : y;

                    double z = strtod(ptr, nullptr);
                    emptyDouble.push_back(z);
                    minZ = minZ < z ? minZ : z;
                    maxZ = maxZ > z ? maxZ : z;

                    vertexes->push_back(emptyDouble);
                } else if (buffer[1] == 'n') {
                    char *ptr;
                    size_t found = buffer.find(' ');

                    emptyDouble.push_back(strtod(buffer.substr(found).c_str(), &ptr));
                    emptyDouble.push_back(strtod(ptr, &ptr));
                    emptyDouble.push_back(strtod(ptr, nullptr));

                    normals->push_back(emptyDouble);
                }
                emptyDouble.clear();
            } else if (buffer[0] == 'f')  {
                size_t foundSlash = buffer.find('/');
                size_t foundSpace = 1;

                if (foundSlash == string::npos) {
                    char *ptr;
                    size_t found = buffer.find(' ');

                    emptyInt.push_back((int)strtod(buffer.substr(found).c_str(), &ptr) - 1);
                    emptyInt.push_back((int)strtod(ptr, &ptr) - 1);
                    emptyInt.push_back((int)strtod(ptr, nullptr) - 1);
                } else {
                    while (foundSpace != string::npos) {
                        emptyInt.push_back(stoi(buffer.substr(foundSpace, foundSlash)) - 1);
                        foundSpace = buffer.find(' ', foundSlash + 1);
                        foundSlash = buffer.find('/', foundSpace + 1);
                    }
                }

                figures->push_back(emptyInt);
                emptyInt.clear();
            }
        }

        minCoords->push_back(minX);
        minCoords->push_back(minY);
        minCoords->push_back(minZ);

        maxCoords->push_back(maxX);
        maxCoords->push_back(maxY);
        maxCoords->push_back(maxZ);

        input.close();
    } else {
        cout << "Cannot open file: " << fileName << endl;
    }
}