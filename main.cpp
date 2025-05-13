#include <iostream>
#include <vector>
#include "Set.hpp"
#include "queue"
#include "string"
#include "sstream"

using namespace std;

void helper(){

    cout << "programa incializado com sucesso!" << endl

    << "comandos de manipulacao de conjuntos: " << endl
    << "create" << endl
    << ">>> cria um novo conjunto vazio" << endl
    << "insert indice_do_conjunto valor" << endl
    << ">>> insere valor ao conjunto correspondente ao indice" << endl
    << "erase indice_do_conjunto valor" << endl
    << ">>> remove esse valor do conjunto correspondente ao indice" << endl
    << "contains indice_do_conjunto valor" << endl
    << ">>> imprime uma resposta de acordo se o valor está no conjunto ou não" << endl
    << "size indice_do_conjunto" << endl
    << ">>> imprime o tamanho do conjunto" << endl
    << "empty indice_do_conjunto" << endl
    << ">>> imprime uma resposta dizendo se o conjunto é vazio ou não" << endl
    << "show indice_do_conjunto" << endl
    << ">>> mostra o conteudo do conjunto em formato ordenado" << endl
    << "showAll" << endl
    << ">>> mostra todos os seus conjuntos em ordem" << endl
    << "pop" << endl
    << ">>> remove o ultimo conjunto criado" << endl
    << endl

    << "comandos de operacoes de conjuntos:" << endl
    << "uniao indice_do_conjunto_1 indice_do_conjunto_2" << endl
    << ">>> mostra a uniao desses dois conjuntos e o adiciona aos seus conjuntos" << endl
    << "intersecao indice_do_conjunto_1 indice_do_conjunto_2" << endl
    << ">>> mostra a intersecao desses dois conjuntos e a adiciona aos seus conjuntos" << endl
    << "diferenca indice_do_conjunto_1 indice_do_conjunto_2" << endl
    << ">> mostra a diferenca desses dois conjuntos e a adiciona aos seus conjuntos" << endl
    << "swap indice_do_conjunto_1 indice_do_conjunto_2" << endl
    << ">> troca os conteudos dos dois conjuntos" << endl
    << endl

    << "comandos do programa:" << endl
    << "helper" << endl
    << ">>> mostra a lista de comandos e explica o que cada um faz" << endl
    << "exit" << endl
    << ">>> encerra o programa deletando seus conjuntos" << endl;
}

int main() {

    vector<Set*> conjuntos;
   
    helper();
    
    while(true) {
        string comando, token;
        getline(cin, comando);
        stringstream ss{ comando };
        ss >> token;

        cout << "$" << ss.str() << endl;

        // exit
        if(token == "exit") {
            cout << "o programa será finalizado e os conjuntos deletados" << endl;
            conjuntos.clear();
            break;
        }
        // create
        else if(token == "create") {
            Set* set = new Set();
            conjuntos.push_back(set);

            cout << "um novo conjunto de indice " << conjuntos.size()-1 << " foi criado" << endl;
        }
        else if(token == "pop"){

            conjuntos.pop_back();

            cout << "o ultimo conjunto criado foi excluido" << endl;
        }
        // size
        else if(token == "size"){
            int l;

            ss >> l;

            cout << "o tamanho do conjunto " << l << " é: " << conjuntos[l]->size() << endl;
        }
        else if(token == "uniao") {
            int l, m;

            ss >> l >> m;

            Set* set = new Set();

            cout << "a uniao do conjunto " << l << " com o conjunto " << m << " é igual a :";

            set->unions(conjuntos[l], conjuntos[m]);

            if(set->empty()){
                cout << endl;
            }

            conjuntos.push_back(set);
        }
        else if(token == "diferenca") {
            int l, m;

            ss >> l >> m;

            Set* set = new Set();

            cout << "a diferenca do conjunto " << l << " pro conjunto " << m << " é igual a :";

            set->diference(conjuntos[l], conjuntos[m]);

            if(set->empty()){
                cout << endl;
            }

            conjuntos.push_back(set);
        }
        else if(token == "intersecao") {
            int l, m;

            ss >> l >> m;

            Set* set = new Set();

            cout << "a intersecao do conjunto " << l << " com o conjunto " << m << " é igual a :";

            set->intersection(conjuntos[l], conjuntos[m]);

            if(set->empty()){
                cout << endl;
            }

            conjuntos.push_back(set);
        }else if(token == "intercala"){
            int l, m;
            ss >> l >> m;
            Set* set = new Set();

            set->intercala(conjuntos[l], conjuntos[m]);
            
        }
        else if(token == "swap"){
            int l, m;

            ss >> l >> m;

            conjuntos[l]->swap(conjuntos[m]);

            cout << "foi realizado dos conteudos dos conjuntos " << l << " e " << m << endl;
        }
        // pushfront x l
        else if(token == "insert") { //insert
            int value, l;

            ss >> l >> value;

            conjuntos[l]->insert( value);

            cout << "o valor " << value << " foi inserido no conjunto " << l << endl;
        }
        else if(token == "contains") { //contains
            int l, value;

            ss >> l >> value;

            if(conjuntos[l]->contains(value)){
                cout << "Conjunto " << l << " contém o elemento " << value << endl;
            }else{
                cout << "Conjunto " << l << " não contém o elemento " << value << endl;
            }
        }
        else if(token == "empty"){
            int l;

            ss >> l;

            if(conjuntos[l]->empty()){
                cout << "conjunto " << l << " é vazio" << endl;
            }else{
                cout << "conjunto " << l << " não é vazio" << endl;

            }
        }
        else if(token == "erase"){
            int l, value;

            ss >> l >> value;

            conjuntos[l]->erase(value);

            cout << "o valor " << value << " foi removido do conjunto " << l << endl;
        }
        else if(token == "minimo"){
            int l;

            ss >> l;

            cout << "o menor valor do conjunto " << l <<  " é " << conjuntos[l]->minimum() << endl;
        }
        else if(token == "maximo"){
            int l;

            ss >> l;

            cout << conjuntos[l]->maximum();

            cout << "o maior valor do conjunto " << l <<  " é " << conjuntos[l]->maximum() << endl;
        }
        else if(token == "sucessor"){
            int l, value;

            ss >> l >> value;

            cout << "o sucessor do valor" << value <<  " do conjunto " << l <<  " é " << conjuntos[l]->sucessor(value) << endl;
        }
        else if(token == "predecessor"){
            int l, value;

            ss >> l >> value;

            cout << "o predecessor do valor" << value <<  " do conjunto " << l <<  " é " << conjuntos[l]->predecessor(value) << endl;
        }
        else if(token == "show"){
            int l;

            ss >> l;

            cout << "conjunto: " << l << " ";

            conjuntos[l]->show();
        }
        // showAll
        else if(token == "showAll") { //print
            for(unsigned i = 0; i < conjuntos.size(); ++i) {
                cout << "conjunto " << i << ": ";
                conjuntos[i]->show();
            }	
        }
        else if(token == "helper"){
            helper();
        }
        else {
            cout << "comando inexistente" << endl;
        }
    }
     
    return 0;
}
