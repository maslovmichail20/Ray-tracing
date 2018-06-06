#include "KD_tree.h"
#include <iostream>

Box::Box(int index, vector<double>& p1, vector<double>& p2, vector<double>& p3) {
    flatIndex = index;

    vector<double> emptyMin(3, 1000);
    min_p = emptyMin;
    vector<double> emptyMax(3, -1000);
    max_p = emptyMax;

    for (int i = 0 ; i < 3 ; i++) {
        min_p[i] = min_p[i] < p1[i] ? min_p[i] : p1[i];
        min_p[i] = min_p[i] < p2[i] ? min_p[i] : p2[i];
        min_p[i] = min_p[i] < p3[i] ? min_p[i] : p3[i];

        max_p[i] = max_p[i] > p1[i] ? max_p[i] : p1[i];
        max_p[i] = max_p[i] > p2[i] ? max_p[i] : p2[i];
        max_p[i] = max_p[i] > p3[i] ? max_p[i] : p3[i];
    }
}

Box::~Box() {

}

vector<Box*> createBoxesArray(vector<vector<double>>& vertices,
                              vector<vector<int>>& flats)
{
    vector<Box*> boxes(flats.size(), nullptr);
    for (int i = 0 ; i < flats.size() ; i++) {
        boxes[i] = new Box(
                i,
                vertices[flats[i][0]],
                vertices[flats[i][1]],
                vertices[flats[i][2]]
        );
    }
    return boxes;
}


Node::Node(vector<double>& min, vector<double>& max) {
    min_coor = vector<double>(3, 0);
    max_coor = vector<double>(3, 0);

    for (int i = 0 ; i < 3 ; i++) {
        min_coor[i] = min[i];
        max_coor[i] = max[i];
    }

    left = nullptr;
    right = nullptr;

    axis = -1;
}

void Node::addBox(Box* box) {
    boxes.push_back(box);
}

Node::~Node() {

}

KD_tree::KD_tree(vector<double>& min, vector<double>& max, vector<Box*>& allBoxes) {
    root = new Node(min, max);
    root->boxes = allBoxes;
}

KD_tree::~KD_tree() {

}

void KD_tree::buildTree(Node* node) {
    int curAxis = (node->axis + 1) % 3;

    double delimiter = 0;
    for (int i = 0 ; i < node->boxes.size() ; i++) {
        delimiter += node->boxes[i]->max_p[curAxis];
    }
    delimiter /= node->boxes.size();

    vector<double> left_min(3, 0);
    vector<double> left_max(3, 0);
    vector<double> right_min(3, 0);
    vector<double> right_max(3, 0);
    for (int i = 0 ; i < 3 ; i++) {
        left_min[i] = node->min_coor[i];
        left_max[i] = node->max_coor[i];

        right_min[i] = node->min_coor[i];
        right_max[i] = node->max_coor[i];
    }

    left_max[curAxis] = delimiter;
    right_min[curAxis] = delimiter;

    Node* left = new Node (left_min, left_max);
    Node* right = new Node (right_min, right_max);

    left->axis = right->axis = curAxis;

    for (int i = 0 ; i < node->boxes.size() ; i++) {
        Box* curBox = node->boxes[i];
        if (curBox->max_p[curAxis] < delimiter) {
            left->addBox(curBox);
        } else if (curBox->min_p[curAxis] > delimiter) {
            right->addBox(curBox);
        } else {
            left->addBox(curBox);
            right->addBox(curBox);
        }
    }

    node->left = left;
    node->right = right;

    if (left->boxes.size() > 4) {
        buildTree(node->left);
    }
    if (right->boxes.size() > 4) {
        buildTree(node->right);
    }
}

void KD_tree::show(Node* node) {
    cout << node->boxes.size() << endl;
    if (node->left) {
        show(node->left);
    }
    if (node->right) {
        show(node->right);
    }
}


