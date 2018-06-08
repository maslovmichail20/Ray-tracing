#include "readObj.h"
#include "../libraries/OBJ_Loader.h"
#include <iostream>

using namespace std;

void readObj(char *fileName,
             vector<double> &minCoords,
             vector<double> &maxCoords,
             vector<vector<double>> &vertices,
             vector<vector<int>> &flats,
             std::vector<std::vector<double>> &normals
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

                vertices.push_back(curV);
            }
            for (int j = 0; j < curMesh.Indices.size(); j += 3) {
                vector<int> f;
                f.push_back(curMesh.Indices[j]);
                f.push_back(curMesh.Indices[j+1]);
                f.push_back(curMesh.Indices[j+2]);
                flats.push_back(f);

                vector<double> a = vertices[f[0]];
                vector<double> b = vertices[f[1]];
                vector<double> c = vertices[f[2]];

                vector<double> n(3, 0);
                n[0] = (b[1] - a[1])*(c[2] - a[2]) - (b[2] - a[2])*(c[1] - a[1]);
                n[1] = (c[0] - a[0])*(b[2] - a[2]) - (b[0] - a[0])*(c[2] - a[2]);
                n[2] = (b[0] - a[0])*(c[1] - a[1]) - (c[0] - a[0])*(b[1] - a[1]);

                normals.push_back(n);
            }
        }
        minCoords[0] = minX; minCoords[1] = minY; minCoords[2] = minZ;
        maxCoords[0] = maxX; maxCoords[1] = maxY; maxCoords[2] = maxZ;
    } else {
        cout << "Cannot load file: " << fileName << endl;
    }
}