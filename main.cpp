#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <string.h>
#include <math.h>
#include <iomanip>
#include <set>
#include <map>
#include "./bibliotecas/arestaGrafo.h"
#include "./bibliotecas/checarRecursos.cpp"
#include "./bibliotecas/cliqueMaximo.cpp"
#include "./bibliotecas/conversaoEstruturas.cpp"
#include "./bibliotecas/exibirCliqueMaximo.cpp"
#include "./bibliotecas/exibirEstruturasGrafo.cpp"

using namespace std;

bool isUmaEstruturaValida(string &s){
    if(s == "-la") return 1;
    if(s == "-ma") return 1;
    if(s == "-mi") return 1;
    if(s == "-mp") return 1;
    if(s == "-rv") return 1;
    if(s == "-cm") return 1;
    return 0;
}

void showComandosEstruturas(){
    cout << "Veja os comandos validos\n";
    cout << "\033[1;34m Comando -> Estrutura\n\033[0m";
    cout << "\033[1;34m  -ma    -> matriz de adjacencias\n\033[0m";
    cout << "\033[1;34m  -mi    -> matriz de incidencias\n\033[0m";
    cout << "\033[1;34m  -la    -> lista de adjacencias\n\033[0m";
    cout << "\033[1;34m  -rv    -> representacao vetorial\n\033[0m";
    cout << "\033[1;34m  -mp    -> matriz de pesos\n\033[0m";
    cout << "\033[1;34m  -cm    -> clique maximo\n\033[0m";
}

vector<vector<edge>> readGrafo(string &nomeArquivo, bool isDirecionado){
    // Para facilitar, vamos redirecionar o buffer de entrada para o arquivo
    
    ifstream arquivoInput(nomeArquivo);
    if(arquivoInput.is_open() == false){
        cout << "Nao foi possivel abrir o arquivo\n";
        exit(1);
    }
    // Salva o estado atual da entrada padrão (cin)
    streambuf* originalCin = std::cin.rdbuf();

    // Redireciona a entrada padrão para o arquivo
    cin.rdbuf(arquivoInput.rdbuf());
    
    int n; // numero de vertices
    cin >> n;
    vector<vector<edge>> listaAdjacencia(n+1); // precizamos de +1, pois é indexado em 0.
    checkAlocouMemoria(listaAdjacencia);
    // vamos fazer a leitura do grafo
    int u, v; // vertices
    double peso;
    while(cin >> u >> v >> peso){ // enquanto não chegar no EOF
        listaAdjacencia[u].push_back(make_pair(v, peso));
        if(isDirecionado == false)
            listaAdjacencia[v].push_back(make_pair(u, peso));
    }

    // Restaura o estado original da entrada padrão
    cin.rdbuf(originalCin);

    // Fecha o arquivo após a leitura
    arquivoInput.close();

    return listaAdjacencia;
}

int main(int argc, char* argv[]){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); // faz uma otimização de leitura
    // checar se são fornecidos todos os argumentos
    if (argc < 6 || argc > 6) {
        cerr << "\033[1;31m Para executar esse programa use:\033[0m " << argv[0] <<
        " <read> <nomeTeste(inst-*)> <show> <estrutura(-[ma, mi, la, rv, mp])> <isDirecionado(0/1)>\n"; return 1;
    }
    // pegar argumentos importantes
    string nomeInput = argv[2];
    string nomeArquivo = "Instancias_teste/" + nomeInput;
    string tipoEstrutura = argv[4];
    bool isDirecionado = atoi(argv[5]);
    // checar se são comandos validos de execução
    if(strcmp(argv[1], "read") != 0){
        cerr << "\033[1;31m O comando:\033[0m " << argv[1] <<
        "\033[1;31m nao eh valido\n\033[0m"; return 1;
    }
    if(strcmp(argv[3], "show") != 0){
        cerr << "\033[1;31m O comando:\033[0m " << argv[3] <<
        "\033[1;31m nao eh valido\n\033[0m"; return 1;
    }
    if(isUmaEstruturaValida(tipoEstrutura) == false){
        cerr << "\033[1;31m O comando:\033[0m " << argv[4] <<
        "\033[1;31m nao eh valido\n\033[0m"; 
        showComandosEstruturas();
        return 1;
    }
    if(strcmp(argv[4], "-cm") && strcmp(argv[5], "0") != 0 && strcmp(argv[5], "1") != 0){
        cerr << "\033[1;31m O comando:\033[0m " << argv[5] <<
        "\033[1;31m nao eh valido\n\033[0m"; return 1;
    }
    ifstream arquivoInput(nomeArquivo);
    if(arquivoInput.is_open() == false){
        cerr << "\033[1;31m Nao foi possivel abrir o arquivo:\033[0m " << argv[2] <<
        "\033[1;33m verifique se o arquivo existe!\n\033[0m"; return 1;
    }
    // processar os comandos
    vector<vector<edge>> listaAdjacencia = readGrafo(nomeArquivo, isDirecionado);
    if(tipoEstrutura == "-la")
        showGrafoListaAdjacencia(listaAdjacencia);
    else if(tipoEstrutura == "-ma"){
        vector<vector<int>> matrizAdjacencia = listaAdjacencia2matrizAdjacencia(listaAdjacencia);
        showGrafoMatrizAdjacencia(matrizAdjacencia);
    }
    else if(tipoEstrutura == "-mi"){
        vector<vector<int>> matrizIncidencia = listaAdjacencia2matrizIncidencia(listaAdjacencia, isDirecionado);
        showGrafoMatrizIncidencia(matrizIncidencia);
    }
    else if(tipoEstrutura == "-rv"){
        showGrafoRepresentacaoVetorial(listaAdjacencia);
    }
    else if(tipoEstrutura == "-mp"){
        vector<vector<double>> matrizPesos = listaAdjacencia2matrizPesos(listaAdjacencia);
        showGrafoMatrizPesos(matrizPesos);
    }
    else if(tipoEstrutura == "-cm"){
        showCliquesMaximo(listaAdjacencia);
    }
    return 0;
}
