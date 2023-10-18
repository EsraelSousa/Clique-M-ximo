#include <vector>

using namespace std;

/* A constante MAXN_OPBIT representa o número máximo de vértices que podemos
usar a representação binária do número para representar os subconjuntos, se o 
número de vértices for muito grande, os subconjuntos serão gerados recursivamente.
Você pode altera-lo para 0 para gerar os subconjuntos de forma recursiva, mas seu 
valor máximo não deve passar de 60, pois estamos usando um inteiro de 64 bits para
representar os subconjuntos, e um valor maior que 60 pode gerar overflow podendo
causar imprecisão ou até mesmo loop infinito no algoritmo */
const int MAXN_OPBIT = 6;

// algoritmos de força bruta para clique máximo

bool ehClique(vector<int> &vertices, vector<vector<int>> &matrizAdjacencia){
    int n = (int)vertices.size();
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(i != j && matrizAdjacencia[i][j] == 0)
                return false;
    return true;
}

void geraSubconjuntosRecursio(vector<int> &conjunto, int n, int k, vector<int> &cliqueMaximo,
                              vector<vector<int>> &matrizAdjacencia){
    if(k > n)
        return ;
    // processa subconjunto
    if(conjunto.size() > cliqueMaximo.size() && ehClique(conjunto, matrizAdjacencia))
        cliqueMaximo = conjunto;
    // gera os subconjuntos
    geraSubconjuntosRecursio(conjunto, n, k+1, cliqueMaximo, matrizAdjacencia);
    conjunto.push_back(k);
    geraSubconjuntosRecursio(conjunto, n, k+1, cliqueMaximo, matrizAdjacencia);
    conjunto.pop_back();
}

vector<int> pegaCliqueMaximoForcaBruta(vector<vector<int>> &matrizAdjacencia){
    vector<int> cliqueMaximo, conjunto;
    int n = matrizAdjacencia.size();
    if(matrizAdjacencia.size() <= MAXN_OPBIT){
        for(long long i = (1LL << (n+1)); i>0; i--){
            // pega o subconjunto
            for(int j = 1; j<=MAXN_OPBIT; j++)
                if(i & (1LL << j))
                    conjunto.push_back(j);
            // verifica se é um clique
            if(conjunto.size() > cliqueMaximo.size() && ehClique(conjunto, matrizAdjacencia))
                cliqueMaximo = conjunto;
            // limpa conjunto para a próxima iteração
            conjunto.clear();
        }
    }
    else{
        geraSubconjuntosRecursio(conjunto, n, 1,
                                                cliqueMaximo, matrizAdjacencia);
    }
    return cliqueMaximo;
}
