#include <iostream>
#include <vector>
#include <iomanip>
#include "arestaGrafo.h"

using namespace std; 

int countDigitos(int n){
    int ans = 1;
    while(-9 > n || n > 9){
        ans++;
        n /= 10;
    }
    return ans + (n < 0); // (n < 0) contamos o sinal de menos também
}

void showGrafoListaAdjacencia(vector<vector<edge>> &listaAdjacencia){
    cout << "\033[1;33mLista de Adjacencias:\n\033[0m";
    for(int i=1; i < (int)listaAdjacencia.size(); i++){
        cout << "\033[1;33m" << i << " -> \033[0m";
        bool isFirst = 1;
        for(auto &par: listaAdjacencia[i]){
            if(!isFirst) cout << ", ";
            cout << "{" << par.first << ", " << fixed << setprecision(2) << par.second << "}";
            isFirst = 0;
        }
        cout << "\n";
    }
}

void showGrafoMatrizAdjacencia(vector<vector<int>> &matrizAdjacencia){
    int n = matrizAdjacencia.size();
    int qtdDigitos = countDigitos(n-1);
    cout << "\033[1;33mMatriz de Adjacencias:\n\033[0m";
    for(int i=1; i<n; i++){
        if(i == 1)
            // um espaço para colocar os vertices na primeira coluna
            cout << "\033[1;32m" << setw(qtdDigitos+2) << setfill(' ') << i << "\033[0m" << ' ';
        else
            cout << "\033[1;32m" << setw(qtdDigitos) << setfill(' ') << i << "\033[0m" << (i+1 == n? '\n' : ' ');
    }
    for(int i=1; i<n; i++){
        cout << "\033[1;32m" << setw(qtdDigitos) << setfill(' ') << i << "\033[0m" << ' ';
        for(int j=1; j<n; j++)
            cout << setw(qtdDigitos) << setfill(' ') << matrizAdjacencia[i][j] << (j+1 == n? '\n' : ' ');
    }
}

void showGrafoMatrizPesos(vector<vector<double>> &matrizPesos){
    int n = matrizPesos.size();
    int qtdDigitos = countDigitos(n-1);
    // vamos ver o maior pesso para formatar a saida
    for(int i=1; i<n; i++)
        for(int j=1; j<n; j++)
            qtdDigitos = max(qtdDigitos, countDigitos(matrizPesos[i][j])+ 3);
    cout << "\033[1;33mMatriz de Pesos:\n\033[0m";
    for(int i=1; i<n; i++){
        if(i == 1)
            // um espaço para colocar os vertices na primeira coluna
            cout << "\033[1;32m" << setw(qtdDigitos+2) << setfill(' ') << right << i << "\033[0m" << ' ';
        else
            cout << "\033[1;32m" << setw(qtdDigitos) << setfill(' ') << right << i << "\033[0m" << (i+1 == n? '\n' : ' ');
    }
    for(int i=1; i<n; i++){
        cout << "\033[1;32m" << setw(qtdDigitos) << setfill(' ') << left << i << "\033[0m" << ' ';
        for(int j=1; j<n; j++)
            cout << setw(qtdDigitos) << setfill(' ') << left << fixed << setprecision(2) << matrizPesos[i][j] << (j+1 == n? '\n' : ' ');
    }
}

void showGrafoMatrizIncidencia(vector<vector<int>> &matrizIncidencia){
    int n = matrizIncidencia.size(); // numero vertices
    int m = matrizIncidencia[1].size(); // numeros arestas
    // pegamos o maximo de digitos que precisamos para representar um numero, (2 devido ao -1)
    int qtdEspacos = max(2, max(countDigitos(n-1), countDigitos(m-1)));
    cout << "\033[1;33mMatriz de Incidencias:\n\033[0m";
    for(int i=0; i<m; i++){
        if(i == 0)
            // um espaço para colocar os vertices na primeira coluna
            cout << "\033[1;34m" << setw(qtdEspacos+2) << setfill(' ') << right << i << "\033[0m" << ' ';
        else
            cout << "\033[1;34m" << setw(qtdEspacos) << setfill(' ') << right << i << "\033[0m" << (i+1 == m? '\n' : ' ');
    }
    for(int i=1; i<n; i++){
        cout << setw(qtdEspacos) << setfill(' ') << left << "\033[1;34m" << i << " \033[0m";
        /*Não foi possivel usar cores diferentes para -1, 1 e 0. O uso de cores bagunçava a formatação '-' */
        for(int j=0; j<m; j++){
            cout << setw(qtdEspacos) << setfill(' ') << right << matrizIncidencia[i][j] << ((j+1 == m)? '\n' : ' ');
        }
    }
}

void showGrafoRepresentacaoVetorial(vector<vector<edge>> &listaAdjacencia){
    /*Não vamos usar os vetores em si, mas se aproveitar da lista de adjacencia,
    já que essa representação é a concatenação das listas*/
    int n = listaAdjacencia.size();
    vector<int> qtdEspacos(n, 0); // todas as posições com 0
    // vamos contabilizar os espaços necessários para formatar
    cout << "\033[1;33mRepresentacao Vetorial:\n\033[0m";
    for(int i=1; i<n; i++){
        for(auto &par: listaAdjacencia[i])
            qtdEspacos[i] += countDigitos(par.first)+1;
        qtdEspacos[i] -= 1; // retira um espaço a mais que tem
        
    }
    // 1º vetor
    for(int i=1; i < n; i++){
        if(i & 1){ // é impar
            cout << "\033[1;32m" << setw(qtdEspacos[i]) << setfill(' ') << listaAdjacencia[i].size() << "\033[0m" << (i+1 == n? '\n' : ' ');
        }
        else{
            cout << "\033[1;34m" << setw(qtdEspacos[i]) << setfill(' ') << listaAdjacencia[i].size() << "\033[0m" << (i+1 == n? '\n' : ' ');
        }
    }
    // 2º vetor
    for(int i=1; i < n; i++){
        bool isFirst = 1;
        for(auto &par: listaAdjacencia[i]){
            if(!isFirst) cout << ' ';
            if(i & 1){ // é impar
                cout << "\033[1;32m" << par.first << "\033[0m";
            }
            else{
                cout << "\033[1;34m" << par.first << "\033[0m";
            }
            isFirst = 0;
        }
        if(listaAdjacencia[i].size() == 0) cout << ' '; // corrigir espaços para vertices sem vizinhos
        cout << (i+1 == n? '\n' : ' ');
    }
}
