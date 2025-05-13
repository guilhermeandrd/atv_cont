#ifndef SET_HPP
#define SET_HPP

#include "Node.hpp"
#include "queue"

class Set {
public:
    // Construtor: cria um conjunto vazio
    Set() {
        m_root = nullptr;
    }
    // Função publica que insere a chave
    void insert(int v) {
        m_root = _insert(m_root, v);
    }
    // Funcao publica: libera os nodos do conjunto
    void clear() {
        m_root = clear(m_root);
    }
    // Destrutor
    ~Set() {
        m_root = clear(m_root);
    }
    // Imprime o conjunto num formato amigavel
    void show() {
        std::cout << "[ ";

        bshow(m_root);

        std:: cout << "]" << std::endl;
    }

    // Funcao publica que recebe uma chave e retorna true se 
    // e somente se a chave estiver no conjunto. 
    bool contains(int k) {
        Node *aux = contains(m_root, k);
        return aux != nullptr;
    }

    // Funcao que remove uma chave do conjunto se ele existir
    void erase(int k) {
        m_root = remove(m_root, k);
    }

    int maximum(){
        return _maximo(m_root);
    }

    int minimum(){
        return _minimo(m_root);
    }

    int sucessor(int k){
        return _successor(m_root, m_root, k);
    }

    int predecessor(int k){
        return _predecessor(m_root, m_root, k);
    }

    int size(){
        return cont_no(m_root);
    }

    bool empty(){
        return size() == 0;
    }

    void unions(Set* s1,Set* s2){
        _unions(s1->m_root, s2->m_root);
    }

    void intersection(Set* s1, Set* s2){
        _intersecao(s1->m_root, s2);
    }

    void diference(Set* s1, Set* s2){
        _diferenca(s1->m_root, s2);
    }

    void swap(Set* s1){
        Node* aux = s1->m_root;
        s1->m_root = this->m_root;
        this->m_root = aux;
    }

    void intercala(Set* s1, Set* s2){
        intercala(s1, s2);
    }
private:
    // ponteiro para a raiz do conjunto
    Node* m_root;

    // Função que recebe um ponteiro para um nodo
    // e retorna a altura do nodo
    // Tempo: O(1)
    int height(Node* node) {
        if(node == nullptr) return 0;
        else return node->height;
    }

    // Recebe um nodo e retorna o fator de balanceamento
    // do nodo
    int balance(Node* node) {
        return height(node->right) - height(node->left);
    }

    // Função que recebe um nodo 
    // e faz uma rotação à direita nele
    // Retorna a raiz da nova árvore resultante da rotação
    // Tempo: O(1)
    Node* right_rotation(Node *p) {
        Node* u = p->left;
        p->left = u->right;
        u->right = p;
        p->height = 1 + std::max(height(p->left), height(p->right));
        u->height = 1 + std::max(height(u->left), height(u->right));
        return u;
    }

    // Função que recebe um nodo 
    // e faz uma rotação à esquerda nele
    // Retorna a raiz da nova árvore resultante da rotação
    // Tempo: O(1)
    Node* left_rotation(Node* p) {
        Node* u = p->right;
        p->right = u->left;
        u->left = p;
        p->height = 1 + std::max(height(p->left), height(p->right));
        u->height = 1 + std::max(height(u->left), height(u->right));
        return u;
    }

    // Funcao privada recrusiva 
    // que insere um nodo na conjuntos
    Node* _insert(Node* node, int k) {
        if (node == nullptr){ // Caso base 1: árvore vazia
            return new Node(k, 1, nullptr, nullptr);
        } 
        if (node->key == k) { // Caso base 2: achei um nó repetido
            return node;
        }
        if (k < node->key){ // Caso geral
            node->left = _insert(node->left, k);
        } else {
            node->right = _insert(node->right, k);
        }
        // código do retorna das chamadas recursivas
        node = fixup_node(node, k);
        return node;
    }

    // Função que recebe um ponteiro para a raiz de uma árvore
    // e verifica se é necessário fazer algum reblanaceamento nele.
    // Essa função também recalcula a altura do nó.
    Node* fixup_node(Node* node, int k) {
        int bal = balance(node);
        // Caso 1(a)
        if(bal == -2 && k < node->left->key) {
            return right_rotation(node);
        }
        // Caso 1(b)
        if(bal == -2 && k > node->left->key) {
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }
        // Caso 2(a)
        if(bal == 2 && k > node->right->key) {
            return left_rotation(node);
        }
        // Caso 2(b)
        if(bal == 2 && k < node->right->key) {
            node->right = right_rotation(node->right);
            return left_rotation(node);
        }
        // Caso node balanceado
        node->height = 1 + std::max(height(node->left), height(node->right));
        return node;
    }

    // Funcao recursiva privada que recebe a raiz 
    // de de um conjunto e garante que todos os descendentes 
    // dessa raiz e a propria raiz sejam liberados 
    // para a memoria.
    // Retorna nullptr indicando que o conjunto ficou vazio.
    Node* clear(Node* node) {
        if(node != nullptr) {
            node->left = clear(node->left);
            node->right = clear(node->right);
            delete node;
        }        
        return nullptr;
    }

    // Versão alternativa da funcao de liberar nodos
    void _clear(Node* node) {
        if(node != nullptr) {  
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    //funcao que imprime os valores do conjunto em ordem
    void bshow(Node *node) {
        if(node!=nullptr){
            bshow(node->left);
            std::cout << node->key  << " ";
            bshow(node->right);
        }
    }

    // Função recursiva privada que recebe a raiz de uma conjuntos,
    // e uma chave k e retorna o ponteiro para o nói que contém a
    // chave se a chave estiver na conjuntos; caso contrario, ela
    // retorna nulo.
    Node* contains(Node* node, int k) {
        // Caso de parada: achei ou não achei a chave
        if(node == nullptr || node->key == k) {
            return node;
        }
        // Caso geral: ainda nao achei 
        // e ainda tem conjuntos para percorrer
        if(k < node->key)
            return contains(node->left, k);
        else 
            return contains(node->right, k);
    }

    // Funcao privada recursiva que busca a chave a ser removida
    Node* remove ( Node * node , int key ) {
        if ( node == nullptr ) // node nao encontrado
            return nullptr ;

        if ( key < node -> key )
            node -> left = remove( node -> left , key );
        else if ( key > node -> key )
            node -> right = remove( node -> right , key );
        // encontramos no node
        else if ( node -> right == nullptr ) { // sem filho direito
            Node * child = node -> left ;
            delete node ;
            return child ;
        }
        else {// tem filho direito : troca pelo sucessor
               node -> right = remove_successor( node , node -> right ) ;
               node = fixup_deletion(node);
               return node;
        }
            

        // Atualiza a altura do node e regula o node
        node = fixup_deletion ( node ) ;
        return node ;
    }

    //função que remove o sucessor do nó passado
    //e conserta o conjunto o rebalanceando de acordo
    Node* remove_successor( Node * root , Node * node ) {

        if ( node -> left != nullptr ){
            node -> left = remove_successor( root , node -> left ) ;
            node = fixup_deletion(node);
            return node;
        }else {
            root -> key = node -> key ;
            Node * aux = node -> right ;
            delete node ;
            return aux ;
        }

        // Atualiza a altura do node e regula o node
        node = fixup_deletion(node);
        return node ;
    }


    Node* fixup_deletion ( Node * node ) {
        node -> height = 1 + std::max ( height ( node -> left ) , height ( node -> right ) ) ;
        int bal = balance ( node ) ;

        // node pode estar desregulado , ha 4 casos a considerar
        if ( bal > 1 && balance ( node -> right ) >= 0) {
            return left_rotation( node ) ;
        }else if ( bal > 1 && balance ( node -> right ) < 0) {
            node -> right = right_rotation( node -> right ) ;
            return left_rotation ( node ) ;
        }else if ( bal < -1 && balance ( node -> left ) <= 0) {
            return right_rotation( node ) ;
        }else if ( bal < -1 && balance ( node -> left ) > 0) {
            node -> left = left_rotation( node -> left ) ;
            return right_rotation( node ) ;
        }

        return node ;
    }  


    //retorna o maximo do conjunto ou uma excecao
    //caso o conjunto seja vazio
    int _maximo(Node* node) {

        if (node == nullptr) {
            throw std::runtime_error("Set vazio");
        }

        while (node->right != nullptr) {
            node = node->right;
        }

        return node->key;
    }
    


    //retorna o minimo do conjunto ou uma excecao
    //caso o conjunto seja vazio
    int _minimo(Node* node){

        if (node == nullptr) {
            throw std::runtime_error("Set vazio");
        }

        while(node->left!=nullptr){
            node = node->left;
        }
        
        return node->key;
    }

    //retorna o sucessor do valor passado ou uma excecao
    //caso o conjunto seja vazio ou o sucessor não exista
    int _successor(Node* root, Node* node, int k){

        if (node == nullptr || root == nullptr) {
            throw std::runtime_error("Set vazio ou sucessor inexistente");
        }

        if(root->key == k){
            if(root->right != nullptr){
                return _minimo(root->right);
            }else if(node != nullptr && node->key > root->key){
                return node->key;
            }else{
                throw std::runtime_error("Set vazio ou sucessor inexistente");
            }
        }

        if(k < root->key){
            return _successor(root->left, root, k);
        }else{
            return _successor(root->right, root, k);
        } 
    }

    //retorna o predecessor do valor passado ou uma excecao
    //caso o conjunto seja vazio ou o predecessor não exista
    int _predecessor(Node* root, Node*node, int k){

        if (node == nullptr || root == nullptr) {
            throw std::runtime_error("Set vazio ou predecessor inexistente");
        }

        if(root->key == k){
            if(root->left != nullptr){
                return _maximo(root->left);
            }else if(node!=nullptr && node->key < root->key){
                return node->key;
            }else{
                throw std::runtime_error("Set vazio ou predecessor inexistente");
            }
        }
        if(k > root->key){
            return _predecessor(root->right, root, k);
        }else{
            return _predecessor(root->left, root, k);
        } 
    }

    //conta os nós e retorna pro size para calcular tamanho
    int cont_no(Node* node){
        int n=0;

        if(node == nullptr){
            return n;
        }else{
            n++;
            n += cont_no(node->left);
            n += cont_no(node->right);

            return n++;
        }
    }

    //une dois conjuntos baseado em seus m_roots
    void _unions(Node* s1, Node* s2){

        //caso em que os dois são vazios
        if(s1==nullptr&&s2==nullptr){
            return;
        }
    
        std::queue<Node*> Q;
    
        
        //caso em que o segundo conjunto é vazio
        if(s1!=nullptr){

            Q.push(s1);

            while (!Q.empty()) {
                Node* node = Q.front();
                Q.pop();
        
                insert(node->key);  // Insere o valor do nó atual
        
                if (node->left != nullptr)
                    Q.push(node->left);
                
                if (node->right != nullptr)
                    Q.push(node->right);
            }
        }
        
        
        //caso em que o primeiro conjunto é vazio
        if(s2!=nullptr){

            Q.push(s2);

            // Reutiliza a mesma fila para a segunda árvore
            while (!Q.empty()) {
                Node* node = Q.front();
                Q.pop();
        
                insert(node->key);
        
                if (node->left != nullptr)
                    Q.push(node->left);
                
                if (node->right != nullptr)
                    Q.push(node->right);
            }
        }

        show();

    }
    

    //insere valores que estão nos dois conjuntos ao mesmo tempo
    //recebe o m_root do conjunto1 e um ponteiro para o conjunto2
    void _intersecao(Node* s1, Set* s2){

        //caso em que os dois são vazios
        //caso em que o primeiro conjunto é vazio
        //caso em que o segundo conjunto é vazio
        if(s1==nullptr||s2->m_root==nullptr){
            return;
        }


        std::queue<Node*> Q;

    
        Q.push(s1);
    
        while (!Q.empty()) {
            Node* node = Q.front();
            Q.pop();
            
            if(s2->contains(node->key)){
                insert(node->key);  // Insere o valor do nó atual
            }
    
            if (node->left != nullptr)
                Q.push(node->left);
            
            if (node->right != nullptr)
                Q.push(node->right);
        }

        show();

    }

    //insere valores que não estão nos dois conjuntos ao mesmo tempo
    //recebe o m_root do conjunto1 e um ponteiro para o conjunto2
    void _diferenca(Node* s1, Set* s2){

        //caso em que os dois são vazios
        if(s1==nullptr&&s2->m_root==nullptr){
            return;
        }

        //caso em que o primeiro conjunto é vazio
        if(s1==nullptr){
            return;
        }

        std::queue<Node*> Q;
        //caso em que o segundo conjunto é vazio
        //atribui as coisas do primeiro conjunto ao conjunto que chamou
        if(s2->m_root==nullptr){
            Q.push(s1);

            while (!Q.empty()) {
                Node* node = Q.front();
                Q.pop();
        
                insert(node->key);  // Insere o valor do nó atual
        
                if (node->left != nullptr)
                    Q.push(node->left);
                
                if (node->right != nullptr)
                    Q.push(node->right);
            }

            show();
            return;
        }
    

    
        Q.push(s1);
    
        while (!Q.empty()) {
            Node* node = Q.front();
            Q.pop();
            
            if(!s2->contains(node->key)){
                insert(node->key);  // Insere o valor do nó atual
            }
    
            if (node->left != nullptr)
                Q.push(node->left);
            
            if (node->right != nullptr)
                Q.push(node->right);
        }

        show();
    }

    void _intercala(Set* s1, Set* s2){

        if(s1->m_root==nullptr||s2->m_root==nullptr){
            return;
        }

        std::queue <Node*> Q, F;

        Q.push(s1->m_root);
        F.push(s2->m_root);

        while (!Q.empty()||!F.empty()) {
            Node* node = Q.front();
            Node* nodef = F.front();
            Q.pop();
            F.pop();
            
            insert(node->key);  // Insere o valor do nó atual
            insert(nodef->key);
        
            if (node->left != nullptr)
                Q.push(node->left);
            
            if (node->right != nullptr)
                Q.push(node->right);

            if (nodef->left != nullptr)
                F.push(nodef->left);
            
            if (nodef->right != nullptr)
                F.push(nodef->right);

        }
        //codigo em si
        show();
    }
};

#endif