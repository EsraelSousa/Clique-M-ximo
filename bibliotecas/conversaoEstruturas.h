#include <vector>
#include <map>
#include <set>
#include "arestaGrafo.h"
#include "checarRecursos.h"

using namespace std;

vector<vector<int>> listaAdjacencia2matrizAdjacencia(vector<vector<edge>> &listaAdjacencia);

vector<vector<double>> listaAdjacencia2matrizPesos(vector<vector<edge>> &listaAdjacencia);

vector<vector<int>> listaAdjacencia2matrizIncidencia(vector<vector<edge>> &listaAdjacencia, bool isDirecionado);
