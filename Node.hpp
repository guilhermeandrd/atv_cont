#ifndef NODE_HPP
#define NODE_HPP

#include<iostream>

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    // Construtor
    Node (int k, int height, Node* l, Node* r) {
        key = k;
        this->height = height;
        left = l;
        right = r;
    } 
};

#endif