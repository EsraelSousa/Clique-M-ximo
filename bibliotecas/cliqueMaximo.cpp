#include <iostream>
#include <vector>
#include <set>

using namespace std;

/* A constante MAXN_OPBIT representa o número máximo de vértices que podemos
usar a representação binária do número para representar os subconjuntos, se o 
número de vértices for muito grande, os subconjuntos serão gerados recursivamente.
Você pode altera-lo para 0 para gerar os subconjuntos de forma recursiva, mas seu 
valor máximo não deve passar de 60, pois estamos usando um inteiro de 64 bits para
representar os subconjuntos, e um valor maior que 60 pode gerar overflow podendo
causar imprecisão ou até mesmo loop infinito no algoritmo.
Recomenda-se usar a geração de subconjuntos usando inteiros sempre que o grafo possui 
não mais que 60 vértices, pois é mais eficiente e usa menos memória do que gerar os
subconjuntos recursivamente. */
const int MAXN_OPBIT = 60;

// algoritmo de força bruta para clique máximo

bool ehClique(vector<int> &vertices, vector<vector<int>> &matrizAdjacencia){
    int n = (int)vertices.size();
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(i != j && matrizAdjacencia[ vertices[i] ][ vertices[j] ] == 0)
                return false;
    return true;
}

void adicionaClique(vector<int> &conjunto, set<set<int>> &cliquesMaximo){
    auto it = cliquesMaximo.begin();
    if(conjunto.size() < it->size()) return ;
    set<int> aux;
    aux.insert(conjunto.begin(), conjunto.end());
    if(conjunto.size() > cliquesMaximo.begin()->size()){ // temos um clique maior
        // vamos limpar a memoria
        for(auto it: cliquesMaximo)
            it.clear();
        cliquesMaximo.clear();
        cliquesMaximo.insert(aux);
    }
    else if(conjunto.size() == cliquesMaximo.begin()->size())
        cliquesMaximo.insert(aux);
}

void geraSubconjuntosRecursio(vector<int> &conjunto, int n, int k, set<set<int>> &cliquesMaximo,
                              vector<vector<int>> &matrizAdjacencia){
    if(k > n)
        return ;
    // processa subconjunto
    if(ehClique(conjunto, matrizAdjacencia))
        adicionaClique(conjunto, cliquesMaximo);
    // gera os subconjuntos
    geraSubconjuntosRecursio(conjunto, n, k+1, cliquesMaximo, matrizAdjacencia);
    conjunto.push_back(k);
    geraSubconjuntosRecursio(conjunto, n, k+1, cliquesMaximo, matrizAdjacencia);
    conjunto.pop_back();
}

set<set<int>> pegaCliquesMaximoForcaBruta(vector<vector<int>> &matrizAdjacencia){
    vector<int> conjunto;
    set<int> aux;
    set<set<int>> cliquesMaximo;
    aux.insert(1);
    cliquesMaximo.insert(aux);
    int n = matrizAdjacencia.size();
    if(matrizAdjacencia.size() <= MAXN_OPBIT){
        for(long long i = (1LL << (n)); i>0; i--){
            // pega o subconjunto
            for(int j = 1; j<=MAXN_OPBIT; j++)
                if(i & (1LL << j))
                    conjunto.push_back(j);
            // verifica se é um clique
            if(ehClique(conjunto, matrizAdjacencia))
                adicionaClique(conjunto, cliquesMaximo);
            // limpa conjunto para a próxima iteração
            conjunto.clear();
            aux.clear();
        }
    }
    else{
        geraSubconjuntosRecursio(conjunto, n, 1, cliquesMaximo, matrizAdjacencia);
    }
    // verifica se encontrou um clique maximo 
    if(cliquesMaximo.begin()->size() == 1){ // não achou um clique, pois um clique deve ter pelo menos 2 vertices
        for(auto it: cliquesMaximo)
            it.clear();
        cliquesMaximo.clear();
    }
    return cliquesMaximo;
}

// algoritmo otimizado para encontrar o clique maximais

