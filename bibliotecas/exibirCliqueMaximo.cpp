#include <iostream>
#include <vector>
#include "cliqueMaximo.h"
#include "arestaGrafo.h"
#include "checarRecursos.h"
#include "conversaoEstruturas.h"

using namespace std;

void showCliqueMaximo(vector<vector<edge>> &listaAdjacencia){
    vector<vector<int>> matrizAdjacencia = listaAdjacencia2matrizAdjacencia(listaAdjacencia);
    vector<int> cliqueMaximo = pegaCliqueMaximoForcaBruta(matrizAdjacencia);
    cout << "O Clique Maximo contem " << cliqueMaximo.size() << " vertices:\n";
    for(auto v: cliqueMaximo)
        cout << v << ' ';
    cout << '\n';
}

void showTodosCliqueMaximo(){

}