//
//  Hierarchical.cpp
//  CubeDetector
//
//  Created by DosonLeung on 9/22/17.
//  Copyright © 2017 Yannick Loriot. All rights reserved.
//

#include "Hierarchical.hpp"
#include <iostream>
#include <iomanip>

#define MAX_MATRIX 256
#define MAX_DIMENSION 8
#define ZERO 0.0000001
#define MAX(a,b) (a>b?a:b)

struct coordinate{
    unsigned long row;
    unsigned long column;
    unsigned long count;
};

double distance(DataNode node1 , DataNode node2 , unsigned int dimension){
    double dist = 0.00;
    for (int i = 0; i < dimension ; i++){
        dist += (node1.attributes[i] - node2.attributes[i]) * (node1.attributes[i] - node2.attributes[i]);
    }
    cout << node1.name << " " << node2.name << " : " << dist << endl;
    return dist;
}

void Hierarchical::initMatrix(){
    cout << "before initMatrix:" << endl;
    matrix = vector<vector<double>>(dataNodeList.size());
    for (int i = 0; i < dataNodeList.size() ; i++) {
        matrix[i] = vector<double>(dataNodeList.size());
        for (int j = i + 1; j < matrix.size(); j++){
            matrix[i][j] = distance(this->dataNodeList[i], this->dataNodeList[j], dimension);
        }
    }
    //cout << "after initMatrix:" << endl;
    //printMatrix();
}

Vernier Hierarchical::minDistanceInMatrix(vector<vector<double>> matrix){
    Vernier v;
    double min = __DBL_MAX__;
    for (int i = 0; i < matrix.size() ; i++){//i means row
        for (int j = i + 1; j < matrix.size() ; j++){//j means column
            if (min > matrix[i][j] && matrix[i][j] > 0.00) {
                min = matrix[i][j];
                v.column = j;
                v.row = i;
                v.distance = matrix[i][j];
            }
        }
    }
    return v;
}

void Hierarchical::cluster(){
    Vernier v;
    int i = 0;
    while (1) {
        cout << "GENERATION " << i++ << endl;
        printMatrix();
        v = minDistanceInMatrix(matrix);
        if (v.distance < ZERO) {
            break;
        }
        cout << "Combine [" << v.row << "," << v.column << "]" << endl;
        cout << "Distance:" << v.distance << endl;
        matrix[v.row][v.column] = 0.00;
        combine(v.row,v.column);
        
        coordinate R;
        coordinate C;
        int offsetR = 0;
        int offsetC = 0;
        R.count = dataNodeList.size() - 1;
        C.count = dataNodeList.size() - 1;
        
        for(int k = 0; k < MAX(R.count, C.count); k++){
            //For Row (the yellow blocks in the table)
            if (k < v.row) {
                R.row = k;
                R.column = v.row;
            }else{//When traverse to the pivot of the yellow row and column
                if (k + 1 == v.column) {//When traverse to the red block
                    offsetR = 1;
                    R.count--;
                }
                R.row = v.row;
                R.column = k + offsetR + 1;
            }
            //For Column (the green blocks in the table)
            if (k < v.column - offsetC) {
                if (k == v.row) {//When traverse to the red block
                    offsetC = 1;
                    C.count--;
                }
                if (k + offsetC >= v.column) {
                    C.row = v.column;
                    C.column = k + offsetC + 1;
                }else{
                    C.row = k + offsetC;
                    C.column = v.column;
                }
            }else{//When traverse to the pivot of the green row and column
                C.row = v.column;
                C.column = k + offsetC + 1;
            }
            if (matrix[R.row][R.column] < matrix[C.row][C.column]) {//If the yellow block less than the green block,the green block will be set at 0
                if (matrix[R.row][R.column] > ZERO) {
                    matrix[C.row][C.column] = 0.00;
                }
            }else if (matrix[R.row][R.column] > matrix[C.row][C.column]){//If the yellow block greater than the green block,the yellow block will be cover with the green block and the green block will be set at 0
                if (matrix[C.row][C.column] > ZERO) {
                    matrix[R.row][R.column] = matrix[C.row][C.column];
                    matrix[C.row][C.column] = 0.00;
                }
            }else{//If the yellow block is equal to the green one and both of them are greater than 0.The green block will be set at 0
                if (matrix[C.row][C.column] > ZERO) {
                    matrix[C.row][C.column] = 0.00;
                }
            }
        }
    }
}

//Combine the node or the node set
void Hierarchical::combine(unsigned int left,unsigned int right){
    HCTreeNode *root = (HCTreeNode *)malloc(sizeof(HCTreeNode));;
    HCTreeNode *leftNode = treeNodeList[left];
    HCTreeNode *rightNode = treeNodeList[right];
    root->left = leftNode;
    root->right = rightNode;
    root->count = leftNode->count + rightNode->count;
    root->index = left;
    root->root = NULL;
    stringstream ss;
    ss << *leftNode->tag << *rightNode->tag;
    root->tag = new string(ss.str());
    leftNode->root = root;
    rightNode->root = root;
    treeNodeList[left] = root;
}

void Hierarchical::input(vector<vector<double>> data, int dimension){
    this->dimension = dimension;
    dataNodeList = vector<DataNode>(data.size());
    treeNodeList = vector<HCTreeNode *>(data.size());
    cout << "data input:" << endl;
    for (int i = 0; i < data.size() ; i++){
        DataNode n;
        n.name = i + 65;
        n.attributes = vector<double>(data[i].size());
        cout << n.name << " : ";
        for (int j = 0; j < data[i].size(); j++) {
            n.attributes[j] = data[i][j];
            cout << data[i][j] << " ";
        }
        cout << endl;
        dataNodeList[i] = n;
    }
    for (unsigned int j = 0; j < data.size(); j++) {
        HCTreeNode *h = (HCTreeNode *)malloc(sizeof(HCTreeNode));
        stringstream ss;
        ss << dataNodeList[j].name;
        h->tag = new string(ss.str());
        h->index = j;
        h->count = 1;
        h->left = NULL;
        h->right = NULL;
        treeNodeList[j] = h;
    }
    initMatrix();
}

HCTreeNode* Hierarchical::output(){
    cluster();
    for (int i = 0; i < treeNodeList.size(); i++) {
        if (this->treeNodeList[i]->root == NULL) {
            outputTree = treeNodeList[i];
            break;
        }
    }
    return outputTree;
}

//just use for print the matrix
void Hierarchical::printMatrix(){
    cout << " ";
    for (int k = 0; k < matrix.size(); k++) {
        cout << dataNodeList[k].name << "      ";
    }
    cout << endl;
    for (int i = 0 ; i < matrix.size() ; i++){
        cout << dataNodeList[i].name;
        for (int j = 0 ; j < matrix[i].size() ; j ++){
            //zero
            if (matrix[i][j] < ZERO && matrix[i][j] > -ZERO){
                cout << "0.0000" << " ";
            }else{
                cout << setprecision(5) << left << setw(6) << matrix[i][j] << " ";
            }
        }
        cout << endl;
    }
}

