#include <iostream>
#include <vector>
#include "arestaGrafo.h"

using namespace std;

void checkPossivelConverterMatrriz(vector<vector<edge>> &listaAdjacencia);

template <typename T> /* isso vai deixar generico para qualquer tipo, assim não faz uma função 
                        para o tipo int e outra para o tipo double */
void checkAlocouMemoria(vector<vector< T >> &variavel);
