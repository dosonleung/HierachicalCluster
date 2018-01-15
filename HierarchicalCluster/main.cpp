//
//  main.cpp
//  HierarchicalTest
//
//  Created by DosonLeung on 9/23/17.
//  Copyright © 2017 DosonLeung. All rights reserved.
//

#include <queue>
#include <iostream>
#include "Hierarchical.hpp"

queue<HCTreeNode *> hq;

void HierarchicalTraverse(HCTreeNode *t);

int main(int argc, const char * argv[]) {
    Hierarchical *h = new Hierarchical();
    vector<vector<double>> v;
    //double data[6][2] = {{1.0,1.0},{5.0,5.0},{5.0,1.0},{6.0,1.0},{2.0,2.0},{7.0,6.0}};//see sheet1
    //double data[8][2] = {{1.0,1.0},{6.0,1.5},{5.5,2.5},{4.0,5.0},{5.0,2.0},{2.0,1.5},{3.0,6.0},{1.5,4.0}};//see sheet2
    //double data[8][2] = {{2.0,1.0},{-1.0,1.0},{-2.0,2.0},{1.0,2.0},{2.0,2.0},{3.0,2.0},{-4.0,4.0},{2,3}};//see sheet3
    //double data[6][2] = {{6.2,6.2},{1.0,1.0},{6.0,6.0},{3.0,3.0},{5.5,5.5},{4.5,4.5}};//see sheet4
    double data[8][3] = {{1.00,1.00,1.00},{5.00,5.00,0.00},{2.00,4.00,3.00},{1.00,1.00,0.00},{6.00,4.00,-1.00},{-1.00,1.00,1.00},{6.00,0.00,0.00},{7.00,0.00,0.00}};
    for (int i = 0; i < 8; i++){
        v.push_back(vector<double>(begin(data[i]),end(data[i])));
    }
    h->input(v,3);//remember the dimension for the second parameter
    HCTreeNode *root = h->output();
    HierarchicalTraverse(root);//BFS
    return 0;
}

void HierarchicalTraverse(HCTreeNode *t){
    if (t==NULL) {
        return;
    }else{
        hq.push(t);
        while (!hq.empty()) {
            HCTreeNode *h = hq.front();
            cout << "[" << *h->tag << "]" << endl;
            hq.pop();
            if (h->left) {
                hq.push(h->left);
            }
            if (h->right){
                hq.push(h->right);
            }
        }
    }
}

