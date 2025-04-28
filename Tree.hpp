#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include "iostream"

class Tree{
    Node* m_root;
    
private:

    //atualizar
    Node * rotacaoDireita(Node *p){
        Node* u = p->n_left;
        p->n_left = u->n_right;
        u->n_right = p;


        return u;
    }

    //fazer
    Node* rotacaoEsquerda(Node* p){
        Node* u = p->n_right;
        p->n_right = u->n_left;

        p->height = 1 + std::max(p->n_left->height, p->n_right->height);
        return nullptr;
    }

    //função que retorna a altura de uma árvore
    int _height(Node* node){
        if(node==nullptr){
            return 0;
        }else{
            return node->height;
        }
    }

    //função que retorna o balanco de uma árvore
    int balanco(Node* node){
        return _height(node->n_right) - _height(node->n_left);
    };
    
    bool ehDesbalanceada(Node* node){
        return balanco(node)==2||balanco(node)==-2;
    }
    
    //retorna nova arv modificada
    Node* fixupNode(Node* p, int key){
        int bal = balanco(p);
    
        //caso 1(a)
        if(bal == -2 && key< p->n_left->k){
            return rotacaoDireita(p);
        }
    
        //caso 1(b)
    
        if(bal == -2 && key > p->n_left->k){
            p->n_left = rotacaoEsquerda(p->n_left);
            return rotacaoDireita(p);
        }
    
        //caso 2(a)
    
        if(bal == 2 && key > p->n_right->k){
            return rotacaoEsquerda(p);
        }
    
        //caso 2(b)
        if(bal == 2 && key > p->n_right->k){
            p->n_right = rotacaoDireita(p->n_right);
            return rotacaoEsquerda(p);
        }
        
        //caso node balanceado
        p->height = std::max(_height(p->n_left), _height(p->n_right)) + 1;
        return p;
    }

    //função pra inserir um nó em uma árvore
   Node* _insert(Node* node, int key){

        if(node == nullptr){
            return new Node(key, nullptr, nullptr);
        }

        if(node->k ==  key){//caso 2 : numero repetido
            return node;
        }
        
        if(key < node -> k){ //caso geral
            node->n_left = _insert(node->n_left, key);
        }else if(key > node-> k){
            node->n_right = _insert(node->n_right, key);
        }


        //código de retorno das chamadas recursivas
        node = fixupNode(node, key);
        return node;
    }

    void show(Node *node, std::string heranca) {
        if(node != nullptr && (node->n_left != nullptr || node->n_right != nullptr))
            show(node->n_right , heranca + "r");
        for(int i = 0; i < (int) heranca.size() - 1; i++)
            std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
        if(heranca != "")
            std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
        if(node == nullptr){
            std::cout << "#" << std::endl;
            return;
        }
        std::cout << node->k << std::endl;
        if(node != nullptr && (node->n_left != nullptr || node->n_right != nullptr))
            show(node->n_left, heranca + "l");
    }

public:

    Tree(){
        m_root = nullptr;
    }
    //função publica pra retornar altura de uma arvore
    int height(){
        return _height(m_root);
    }

    void insert(int k){
        m_root = _insert(m_root, k);
    }

    // Imprime a arvore num formato amigavel
    void show() {
        show(m_root, "");
    }
};


#endif

//função add

//tentar fazer em casa