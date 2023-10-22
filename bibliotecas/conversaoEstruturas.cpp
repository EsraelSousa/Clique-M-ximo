#include <vector>
#include <map>
#include <set>
#include "arestaGrafo.h"
#include "checarRecursos.h"

using namespace std;

vector<vector<int>> listaAdjacencia2matrizAdjacencia(vector<vector<edge>> &listaAdjacencia){
    checkPossivelConverterMatrriz(listaAdjacencia);
    int n = listaAdjacencia.size();
    vector<vector<int>> matrizAdjacencia(n, vector<int>(n, 0)); // cria a matriz e seta com 0's
    checkAlocouMemoria(matrizAdjacencia);
    for(int i=1; i<listaAdjacencia.size(); i++){
        for(auto &par: listaAdjacencia[i])
            matrizAdjacencia[i][ par.first ] = 1;
    }
    return matrizAdjacencia;
}

vector<vector<double>> listaAdjacencia2matrizPesos(vector<vector<edge>> &listaAdjacencia){
    checkPossivelConverterMatrriz(listaAdjacencia);
    int n = listaAdjacencia.size();
    vector<vector<double>> matrizAdjacencia(n, vector<double>(n, 0)); // cria a matriz e seta com 0's
    checkAlocouMemoria(matrizAdjacencia);
    for(int i=1; i<listaAdjacencia.size(); i++){
        for(auto &par: listaAdjacencia[i])
            matrizAdjacencia[i][ par.first ] = par.second;
    }
    return matrizAdjacencia;
}

vector<vector<int>> listaAdjacencia2matrizIncidencia(vector<vector<edge>> &listaAdjacencia, bool isDirecionado){
    checkPossivelConverterMatrriz(listaAdjacencia);
    int n = listaAdjacencia.size(); // numero de vertices
    int m = 0; // numero de arestas
    int idAresta = 0;
    // contamos quantas arestas existem no grafo
    for(int i=1; i<n; i++)
        m += listaAdjacencia[i].size();
    if(isDirecionado == false) // estamos contando cada aresta duas vezes
        m /= 2;
    vector<vector<int>> matrizIncidencia(n, vector<int>(m, 0)); // as arestas serão indexadas de 0 a m-1
    checkAlocouMemoria(matrizIncidencia);
    if(isDirecionado){
        for(int i=1; i<n; i++){
            for(auto &par: listaAdjacencia[i]){
                matrizIncidencia[i][idAresta] = -1;
                matrizIncidencia[par.first][idAresta] = 1;
                idAresta++;
            }
        }
    }
    /* Se não é direcionado temos alguns problemas para a matriz de incidencia, na lista de adjacencia 
    temos as arestas repetidas e temos que diferenciar arestas paralelas. Para corrigir isso vamos 
    fazer um mapeamento das arestas */
    else{
        map<pair<int, int>, int> identificacaoAresta;
        for(int i=1; i<n; i++){
            for(auto &par: listaAdjacencia[i]){
                // temos um aresta de u para v, onde o idenficador de u <= v
                pair<int, int> aresta = make_pair(min(i, par.first), max(i, par.first));
                // checo se essa aresta não apareceu nenhuma vez, para colocar ela no mapeamento
                if(identificacaoAresta.find(aresta) == identificacaoAresta.end())
                    identificacaoAresta[aresta] = 0; // a aresta não apareceu nenhuma vez
                // aumento a quantidade de vez que a aresta apareceu
                identificacaoAresta[aresta]++;
            }
        }
        // agora vamos colocar na matriz de incidencias
        for(auto &par: identificacaoAresta){
            while(par.second){ // devido a arestas paralelas
                matrizIncidencia[ par.first.first ][idAresta] = 1;
                matrizIncidencia[ par.first.second ][idAresta] = 1;
                idAresta++;
                par.second -= 2; // -2 devido a duplicação
            }
        }
    }
    return matrizIncidencia;
}
