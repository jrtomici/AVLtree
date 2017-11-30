//
//  main.cpp
//  AVLtree
//
//  Created by John Tomici on 11/30/17.
//  Copyright © 2017 John Tomici. All rights reserved.
//


#include <iostream>
#include <queue>
using namespace std;

class AVL{
    private:
        struct Node{
            Node *leftChild, *rightChild;
            int data, balanceFactor;
        };
    public:
        AVL();
        Node *root;
        void insertNode(int);
        void __insertNode(Node*&, Node*&);
        void calcBalanceFactor(Node*);
        int height(Node*);
        void leftRotate(Node*&);
        void rightRotate(Node*&);
        void levelPrint();
};

//Constructor
AVL::AVL(){root = NULL;}

void AVL::insertNode(int value){
    //Assign value to node
    Node *nodePtr = new Node;
    nodePtr -> data = value;
    nodePtr -> leftChild = nodePtr -> rightChild = NULL;
    __insertNode(root, nodePtr);
}

void AVL::__insertNode(Node *&nodePtr, Node *&newNode){
    //Insert new node
    if (!nodePtr){
        nodePtr = newNode; return;
    }
    else if (nodePtr -> data > newNode -> data)
    __insertNode(nodePtr -> leftChild, newNode);
    else
    __insertNode(nodePtr -> rightChild, newNode);
    //Balance the tree
    calcBalanceFactor(nodePtr);
    if (nodePtr -> balanceFactor < -1){
        if (nodePtr -> rightChild -> balanceFactor < 0)
        //Right-Right case
        leftRotate(nodePtr);
        else{
            //Right-Left case
            rightRotate(nodePtr -> rightChild);
            leftRotate(nodePtr);
        }
    }
    else if (nodePtr -> balanceFactor > 1){
        if (nodePtr -> leftChild -> balanceFactor > 0)
        //Left-Left case
        rightRotate(nodePtr);
        else{
            //Left-Right case
            leftRotate(nodePtr -> leftChild);
            rightRotate(nodePtr);
        }
    }
}

void AVL::calcBalanceFactor(Node *nodePtr){
    nodePtr -> balanceFactor = height(nodePtr -> leftChild) - height(nodePtr -> rightChild);
}

int AVL::height(Node *nodePtr){
    if (!nodePtr) return 0;
    return (1 + max(height(nodePtr -> leftChild), height(nodePtr -> rightChild)));
}

void AVL::leftRotate(Node *&nodePtr){
    Node *temp = nodePtr;
    nodePtr = nodePtr -> rightChild;
    temp -> rightChild = nodePtr -> leftChild;
    nodePtr -> leftChild = temp;
}

void AVL::rightRotate(Node *&nodePtr){
    Node *temp = nodePtr;
    nodePtr = nodePtr -> leftChild;
    temp -> leftChild = nodePtr -> rightChild;
    nodePtr -> rightChild = temp;
}

void AVL::levelPrint() {
    if (!root) return;
    queue<Node*> nodesQueue;
    int nodesInCurrentLevel = 1;
    int nodesInNextLevel = 0;
    nodesQueue.push(root);
    while (!nodesQueue.empty()) {
        Node *currNode = nodesQueue.front();
        nodesQueue.pop();
        nodesInCurrentLevel--;
        if (currNode) {
            cout << currNode -> data << " ";
            nodesQueue.push(currNode -> leftChild);
            nodesQueue.push(currNode -> rightChild);
            nodesInNextLevel += 2;
        }
        if (nodesInCurrentLevel == 0) {
            cout << endl;
            nodesInCurrentLevel = nodesInNextLevel;
            nodesInNextLevel = 0;
        }
    }
}

int main(){
    AVL tree;
    tree.insertNode(1);
    tree.insertNode(2);
    tree.insertNode(3);
    tree.insertNode(4);
    tree.insertNode(5);
    tree.insertNode(6);
    tree.insertNode(7);
    tree.insertNode(8);
    tree.insertNode(9);
    tree.insertNode(10);
    tree.levelPrint();
}
