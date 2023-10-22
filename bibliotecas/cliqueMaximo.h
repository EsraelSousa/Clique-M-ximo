#include <vector>

using namespace std;

bool ehClique(vector<int> &vertices, vector<vector<int>> &matrizAdjacencia);

void adicionaClique(vector<int> &conjunto, set<set<int>> &cliquesMaximo);

void geraSubconjuntosRecursio(vector<int> &conjunto, int n, int k, set<set<int>> &cliquesMaximo,
                              vector<vector<int>> &matrizAdjacencia);

set<set<int>> pegaCliquesMaximoForcaBruta(vector<vector<int>> &matrizAdjacencia);
