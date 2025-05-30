#include "Node.hpp"
#include "iostream"

//atualizar
Node * rotacaodireita(Node *p){
    Node* u = p->n_left;
    p->n_left = u->n_right;
    u->n_right = p;
    return u;
}

//fazer
Node* rotacaoEsquerda(Node* algo){
    return nullptr;
}

int height(Node* node){
    if(node==nullptr){
        return 0;
    }else{
        return node->height;
    }
}

int balanco(Node* node){
    return height(node->n_right) - height(node->n_left);
};

bool ehDesbalanceada(Node* node){
    return balanco(node)==2||balanco(node)==-2;
}

//retorna nova arv modificada
Node* fixupNode(Node* p, int key){
    int bal = balanco(p);

    //caso 1(a)
    if(bal <-1 && key< p->n_left->k){
        return rotacaodireita(p);
    }

    //caso 1(b)

    if(bal <-1 && key > p->n_left->k){
        p->n_left = rotacaoEsquerda(p->n_left);
        return rotacaodireita(p);
    }

    //caso 2(a)

    if(bal > 1 && key > p->n_right->k){
        return rotacaoEsquerda(p);
    }

    //caso 2(b)
    if(bal > 1 && key > p->n_right->k){
        p->n_right = rotacaodireita(p->n_right);
        return rotacaoEsquerda(p);
    }

    p->height = max(height(p->n_left), height(p->n_right)) + 1;
    return nullptr;
}

//função add

//tentar fazer em casa