#include <iostream>
#include <vector>
#include "arestaGrafo.h"

using namespace std;

void checkPossivelConverterMatrriz(vector<vector<edge>> &listaAdjacencia){
    /* não é possivel fazer matriz nesse programa com mais de 10^6 celulas, para matriz
       vai passar um pouco, mas se o grafo for direcionado e completo não vai dar para 
       alocar espaço na memoria, pois precisa O(9 * 10^8) de memoria [(1000 * 999) * 1000] */ 
    if(listaAdjacencia.size() > 1000){
        cout << "O grafo tem muitos vertices, nao eh possivel exibir '-'\n";
        exit(1);
    }
    // se não entrou no if, continua o programa
}

template <typename T> /* isso vai deixar generico para qualquer tipo, assim não faz uma função 
                        para o tipo int e outra para o tipo double */
void checkAlocouMemoria(vector<vector< T >> &variavel){
    if(variavel.empty()){
        cout << "Nao foi possivel alocar memoria! '-'\n";
        exit(1);
    }
}
