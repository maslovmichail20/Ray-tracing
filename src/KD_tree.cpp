#include "KD_tree.h"
#include "geometry.h"
#include <iostream>

Box::Box(int index, vector<double>& p1, vector<double>& p2, vector<double>& p3) {
    flatIndex = index;

    for (int i = 0 ; i < 3 ; i++) {
        min_p[i] = min_p[i] < p1[i] ? min_p[i] : p1[i];
        min_p[i] = min_p[i] < p2[i] ? min_p[i] : p2[i];
        min_p[i] = min_p[i] < p3[i] ? min_p[i] : p3[i];

        max_p[i] = max_p[i] > p1[i] ? max_p[i] : p1[i];
        max_p[i] = max_p[i] > p2[i] ? max_p[i] : p2[i];
        max_p[i] = max_p[i] > p3[i] ? max_p[i] : p3[i];

        center[i] = (p1[i] + p2[i] + p3[i]) / 3;
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


Node::Node(double min[3], double max[3]) {
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

KD_tree::KD_tree(double min[3], double max[3], vector<Box*> allBoxes) {
    root = new Node(min, max);
    root->boxes = allBoxes;
}

KD_tree::~KD_tree() {

}

void KD_tree::buildTree(Node* node) {
    int curAxis = 0;
    if (node->axis == 2) {
        curAxis = 0;
    } else curAxis = node->axis + 1;

    quick_sort(node->boxes, 0, node->boxes.size()-1, curAxis);

    double delimiter = node->boxes[node->boxes.size()/2]->max_p[curAxis];

    double left_min[3]; double left_max[3];
    double right_min[3]; double right_max[3];

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
        if (i <= node->boxes.size()/2) {
            left->addBox(curBox);
        } else {
            right->addBox(curBox);
        }
    }

    node->left = left;
    node->right = right;

    if (left->boxes.size() > 2) {
        buildTree(node->left);
    }
    if (right->boxes.size() > 2) {
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

vector<Box*> KD_tree::rayIntersectNode(
        vector<double>& rayOrigin,
        vector<double>& rayVector,
        Node* node
) {
    if (node->boxes.size() < 3) {
        return node->boxes;
    }

//    double left = rayIntersectBox(rayOrigin,
//                                  rayVector,
//                                  node->left->min_coor,
//                                  node->left->max_coor
//    );
//    double right = rayIntersectBox(rayOrigin,
//                                   rayVector,
//                                   node->right->min_coor,
//                                   node->right->max_coor
//    );

    vector<Box*> empty = vector<Box*>();

//    if (left == 0 && right == 0) {
//        return empty;
//    } else if (left == right) {
//        vector<Box*> res1 = rayIntersectNode(rayOrigin, rayVector, node->left);
//        vector<Box*> res2 = rayIntersectNode(rayOrigin, rayVector, node->right);
//        res1.insert(res1.end(), res2.begin(), res2.end());
//        return  res1;
//    } else if (right == 0 || left < right) {
//        return rayIntersectNode(rayOrigin, rayVector, node->left);
//    } else  {
//        return rayIntersectNode(rayOrigin, rayVector, node->right);
//    }


    if (left == 0 && right == 0) {
        return empty;
    } else {
        vector<Box*> res1 = rayIntersectNode(rayOrigin, rayVector, node->left);
        vector<Box*> res2 = rayIntersectNode(rayOrigin, rayVector, node->right);
        res1.insert(res1.end(), res2.begin(), res2.end());
        return  res1;
    }
}

void swap_vector(vector<Box*>& arr, int m, int n) {
    Box* temp = arr[m];
    arr[m] = arr[n];
    arr[n] = temp;
}

int partition(vector<Box*>& arr, int p, int r, int axis)
{
    double pivot = (arr[r]->min_p[axis] + arr[r]->max_p[axis])/2;
    int i = p - 1;

    for (int j = p ; j < r ; j++) {
        if ((arr[j]->min_p[axis]+arr[j]->max_p[axis])/2 <= pivot) {
            i++;
//            if ( i == j) continue;
            swap_vector(arr, i, j);
        }
    }
    swap_vector(arr, i + 1, r);
    return i + 1;
}

void quick_sort(vector<Box*>& arr, int p, int r, int axis)
{
    if (p < r) {
        int q = partition(arr, p, r, axis);
        quick_sort(arr, p, q - 1, axis);
        quick_sort(arr, q + 1, r, axis);
    }
}



