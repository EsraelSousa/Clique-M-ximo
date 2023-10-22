#include <iostream>
#include <vector>
#include "cliqueMaximo.h"
#include "arestaGrafo.h"
#include "checarRecursos.h"
#include "conversaoEstruturas.h"

using namespace std;

void showCliquesMaximo(vector<vector<edge>> &listaAdjacencia){
    vector<vector<int>> matrizAdjacencia = listaAdjacencia2matrizAdjacencia(listaAdjacencia);
    set<set<int>> cliquesMaximo = pegaCliquesMaximoForcaBruta(matrizAdjacencia);
    cout << "O grafo contem " << cliquesMaximo.size() << " clique(s) maximo(s)\n";
    if(cliquesMaximo.empty()) // o grafo não tem cliques 
        return ;
    cout << "O Clique Maximo contem " << cliquesMaximo.begin()->size() << " vertices:\n";
    int i=1;
    for(auto &clique: cliquesMaximo){
        cout << "Clique " << i++ << ": "; 
        for(auto v: clique)
            cout << v << ' ';
        cout << '\n';
    }
}

void showTodosCliqueMaximo(){

}