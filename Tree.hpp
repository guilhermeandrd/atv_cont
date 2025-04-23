#include "Node.hpp"
#include "iostream"

Node * rotacaodireita(Node *p){
    Node* u = p->n_left;
    p->n_left = u->n_right;
    u->n_right = p;
    return u;
}