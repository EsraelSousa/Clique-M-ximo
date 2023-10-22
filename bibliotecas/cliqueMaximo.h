#include <vector>

using namespace std;

bool ehClique(vector<int> &vertices, vector<vector<int>> &matrizAdjacencia);

void geraSubconjuntosRecursio(vector<int> &conjunto, int n, int k, vector<int> &cliqueMaximo,
                              vector<vector<int>> &matrizAdjacencia);

vector<int> pegaCliqueMaximoForcaBruta(vector<vector<int>> &matrizAdjacencia);
