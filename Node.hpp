#ifndef NODE.HPP
#define NODE.HPP

struct Node
{
    int k;
    int height;
    Node* n_right;
    Node* n_left;

    Node(int ka, Node* n_righti, Node* n_lefti){
        k = ka;
        n_right = n_righti;
        n_left = n_lefti;
    }
    /* data */
};

#endif