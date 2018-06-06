#ifndef ASSIGNMENT_6_ADM_KD_TREE_H
#define ASSIGNMENT_6_ADM_KD_TREE_H


#include <vector>

using namespace std;

struct Box {
    Box(int, vector<double>&, vector<double>&, vector<double>&);
    vector<double> min_p;
    vector<double> max_p;
    int flatIndex;
    ~Box();
};

vector<Box*> createBoxesArray(vector<vector<double>>&, vector<vector<int>>&);

struct Node {
    Node(vector<double>&, vector<double>&);
    vector<double> min_coor;
    vector<double> max_coor;
    Node* left;
    Node* right;
    int axis;
    void addBox(Box*);
    vector<Box*> boxes;
    ~Node();
};

class KD_tree {
public:
    KD_tree(vector<double>&, vector<double>&, vector<Box*>&);
    Node* root;
    void buildTree(Node*);
    bool rayIntersectNode();
    void show(Node*);
    ~KD_tree();
};




#endif //ASSIGNMENT_6_ADM_KD_TREE_H
