#ifndef ASSIGNMENT_6_ADM_KD_TREE_H
#define ASSIGNMENT_6_ADM_KD_TREE_H


#include <vector>

using namespace std;

struct Box {
    Box(int, vector<double>&, vector<double>&, vector<double>&);
    double min_p[3];
    double max_p[3];
    double center[3];
    int flatIndex;
    ~Box();
};

vector<Box*> createBoxesArray(vector<vector<double>>&, vector<vector<int>>&);

struct Node {
    Node(double[3], double[3]);
    double min_coor[3];
    double max_coor[3];
    Node* left;
    Node* right;
    int axis;
    void addBox(Box*);
    vector<Box*> boxes;
    ~Node();
};

class KD_tree {
public:
    KD_tree(double[3], double[3], vector<Box*>);
    Node* root;
    void buildTree(Node*);
    vector<Box*> rayIntersectNode(vector<double>&, vector<double>&, Node*);
    void show(Node*);
    ~KD_tree();
};


void swap_vector(vector<Box*>&, int, int);
int partition(vector<Box*>&, int, int, int);
void quick_sort(vector<Box*>& , int, int, int);




#endif //ASSIGNMENT_6_ADM_KD_TREE_H
