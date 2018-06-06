#include "readObj.h"
#include "../libraries/OBJ_Loader.h"
#include <iostream>

using namespace std;

void readObj(char *fileName,
             vector<double> &minCoords,
             vector<double> &maxCoords,
             vector<vector<double>> *vertices,
             vector<vector<int>> *flats,
             std::vector<std::vector<double>> *normals
) {
    double minX = 1000, maxX = -1000;
    double minY = 1000, maxY = -1000;
    double minZ = 1000, maxZ = -1000;

    objl::Loader Loader;
    bool loadOut = Loader.LoadFile(fileName);

    if (loadOut) {
        for (int i = 0; i < Loader.LoadedMeshes.size(); i++) {
            objl::Mesh curMesh = Loader.LoadedMeshes[i];

            for (int j = 0; j < curMesh.Vertices.size(); j++) {
                vector<double> curV(3, 0);
                vector<double> curN(3, 0);

                curV[0] = curMesh.Vertices[j].Position.X;
                curV[1] = curMesh.Vertices[j].Position.Y;
                curV[2] = curMesh.Vertices[j].Position.Z;

                minX = minX < curV[0] ? minX : curV[0];
                maxX = maxX > curV[0] ? maxX : curV[0];

                minY = minY < curV[1] ? minY : curV[1];
                maxY = maxY > curV[1] ? maxY : curV[1];

                minZ = minZ < curV[2] ? minZ : curV[2];
                maxZ = maxZ > curV[2] ? maxZ : curV[2];

                curN[0] = curMesh.Vertices[j].Normal.X;
                curN[1] = curMesh.Vertices[j].Normal.Y;
                curN[2] = curMesh.Vertices[j].Normal.Z;

                vertices->push_back(curV);
                normals->push_back(curN);
            }
            for (int j = 0; j < curMesh.Indices.size(); j += 3) {
                vector<int> newIntV;
                newIntV.push_back(curMesh.Indices[j]);
                newIntV.push_back(curMesh.Indices[j+1]);
                newIntV.push_back(curMesh.Indices[j+2]);
                flats->push_back(newIntV);
            }
        }
        minCoords[0] = minX; minCoords[1] = minY; minCoords[2] = minZ;
        maxCoords[0] = maxX; maxCoords[1] = maxY; maxCoords[2] = maxZ;
    } else {
        cout << "Cannot load file: " << fileName << endl;
    }
}