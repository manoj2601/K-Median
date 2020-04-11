#ifndef ALLCLASSES_H
#define ALLCLASSES_H

#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include "allclasses.h"
#define MAX_SIZE INT_MAX
using namespace std;



class Node
{
    public:
    int initialid; //initial id given in input file
    int weight;                     //weight of the node.
    Node* parent;                   //parent of the node(only one parent is possible)
    int post_order_number;
    vector<Node*> node_child;       //vector to store the children of the node.
    Node(int weight, Node* parent)  //constructor
    {
        this->weight = weight;
        this->parent = parent;
    }
  
    void add_child_in_node(Node* node)  //function to add the children of the node to a vector.
    {
        node_child.push_back(node);
    }
};

class Edge
{
public:
    int length;                         //length of the edge.
    Node* firstNode;                    //first node attached to the edge.
    Node* secondNode;                   //second node attached to the edge.
    
    //constructor of the class Edge
    Edge(int length, Node* firstNode ,Node* secondNode)
    {
        this->length = length;
        this->firstNode = firstNode;
        this->secondNode = secondNode;
    }
};


class Tree
{
public:
    Node* root;             //root of the tree
    vector<Node*> tree_child;   //vector to store the elements of the tree.
    
    Tree(Node* root)        //constructor
    {   
        this->root = root;
    }
    
    //function to add nodes in tree
    void add_in_tree(Node* node)
    {
        tree_child.push_back(node);
    }
};

class ObjectL1
{
public:
    Node* node;     //reference node. 
    int node_number;    
    Node* mv;       // Node mv
    Node* mv_prime; //Node mv' 

    ObjectL1(Node* node, Node* mv, Node* mv_prime, int node_number)
    {
        this->node = node;
        this->mv = mv;
        this->mv_prime = mv_prime;
        this->node_number = node_number;
        node->post_order_number = node_number;
    }

};

#endif
