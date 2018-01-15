//
//  Hierarchical.hpp
//  CubeDetector
//
//  Created by DosonLeung on 9/22/17.
//  Copyright © 2017 Yannick Loriot. All rights reserved.
//

#ifndef Hierarchical_hpp
#define Hierarchical_hpp
#include <vector>
#include <sstream>
//#include <string.h>

using namespace std;

//For output tree
struct HCTreeNode{
    //double weight;
    string *tag;
    unsigned int index;
    unsigned int count;
    HCTreeNode *root;
    HCTreeNode *left;
    HCTreeNode *right;
};

//Private
struct DataNode{
    char name;
    vector<double> attributes;
};

struct Vernier{
    int row = 0;//equal y
    int column = 0;//equal x
    double distance = 0.00;
};

class Hierarchical {
private:
    vector<vector<double>> matrix;//Max Length will be 16
    vector<DataNode> dataNodeList;
    vector<HCTreeNode *> treeNodeList;
    HCTreeNode *outputTree;
    int dimension;//The dimension of the node
    void initMatrix();
    Vernier minDistanceInMatrix(vector<vector<double>> matrix);
    void cluster();
    void combine(unsigned int left,unsigned int right);
    //void swap()
    
public:
    void input(vector<vector<double>> data, int dimension);
    HCTreeNode* output();
    void printMatrix();
};


#endif /* Hierarchical_hpp */

