#ifndef ASSIGNMENT_6_ADM_GEOMETRY_H
#define ASSIGNMENT_6_ADM_GEOMETRY_H


#include <vector>

using namespace std;

vector<double> add(vector<double>&, vector<double>&);

vector<double> subtract(vector<double>&, vector<double>);

double dotProduct(vector<double>&, vector<double>&);

vector<double> crossProduct(vector<double>&, vector<double>&);

double vectorLength(vector<double>&);

vector<double> normalize(vector<double>&);

vector<double> multiply(vector<double>&, double);

double cosBetweenVectors(vector<double>&, vector<double>&);




#endif //ASSIGNMENT_6_ADM_GEOMETRY_H