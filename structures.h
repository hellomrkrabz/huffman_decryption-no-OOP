/** @file */

#include<iostream>
#include<vector>
#include<random>
#include<iomanip>
#include<ctime>
#include<fstream>
#include<sstream>
#include<string>
#include<string.h>
#include<ios>
#include<memory>
#include<cstdlib>
#include <map>
#include <queue>
#include <bitset>
#include <cmath>

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <vector> 
#include <string>

/**
 * A structure required to build a tree.
 * */
 struct treenode
{
    int frequency;
    char charac;
    treenode* point0;
    treenode* point1;
};

 /**
  * A structre used to compare values of treenodes.
  * */
struct compare {
    bool operator()(treenode *left, treenode *right) {
        return left->frequency > right->frequency;
    }
};

#endif