#include <iostream>
#include <vector>
#include "arestaGrafo.h"
#include "checarRecursos.h"
#include "conversaoEstruturas.h"

using namespace std;

int countDigitos(int n);

void showGrafoListaAdjacencia(vector<vector<edge>> &listaAdjacencia);

void showGrafoMatrizAdjacencia(vector<vector<int>> &matrizAdjacencia);

void showGrafoMatrizPesos(vector<vector<double>> &matrizPesos);

void showGrafoMatrizIncidencia(vector<vector<int>> &matrizIncidencia);

void showGrafoRepresentacaoVetorial(vector<vector<edge>> &listaAdjacencia);
