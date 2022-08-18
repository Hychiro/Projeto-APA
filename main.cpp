#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Graph.h"

using namespace std;

Graph *geraGraph()
{
    srand(time(NULL));

    // Variáveis para auxiliar na criação dos nós no Grafo
    int order = 100;
    int vAleatorio = 1 + rand() % 10;
    // int numEdges = vAleatorio * order;
    int numEdges = 10;
    // Criando objeto grafo
    Graph *graph = new Graph(order);
    int i = 0;
    // Preenchendo a matriz de adjacencia.
    int vert1 = 0;
    int vert2 = 0;
    graph->insertEdge(0, 1);
    while (i < numEdges)
    {
        vert1 = rand() % 100;
        vert2 = rand() % 100;
        if (vert1 != vert2)
        {
            if (!graph->verificaAresta(vert1, vert2))
            {
                graph->insertEdge(vert1, vert2);
                i++;
            }
        }
    }

    return graph;
}

void matrizAdj(int matrizADJ[100][100], Graph *graph)
{
    for (int j = 0; j < 100; j++)
    {
        for (int k = 0; k < 100; k++)
        {
            matrizADJ[j][k] = 0;
        }
    }

    for (Node *p = graph->getFirstNode(); p != NULL; p = p->getNextNode())
    {
        for (Edge *q = p->getFirstEdge(); q != NULL; q = q->getNextEdge())
        {
            // if (matrizADJ[p->getId()][q->getTargetId()] == 0 && matrizADJ[q->getTargetId()][p->getId()] == 0)
            // {
            matrizADJ[p->getId()][q->getTargetId()] = 1;
            // }
        }
    }
}
void vetorBin(int vet[4950], int matrizADJ[100][100])
{
    int i = 0;
    for (int o = 0; o < 4950; o++)
    {
        vet[o] = 0;
    }

    for (int j = 0; j < 100; j++)
    {
        for (int k = 0; k < 100; k++)
        {
            if (k > j)
            {
                vet[i] = matrizADJ[j][k];
                i++;
            }
        }
    }
}

void vetorCompact(int vetBin[4950], int vetCompact[], int tamanho)
{
    int contador = 0;
    for (int i = 0; i < tamanho; i++)
    {
        vetCompact[i] = 0;
    }

    for (int i = 0; i < 4950; i++)
    {
        if (vetBin[i] == 1)
        {
            vetCompact[contador] = i + 1;
            contador++;
        }
    }
}
void matrizAdjPorCompact(int vetCompact[], int tamanho, int matrizADJTriSup[100][100])
{
    for (int j = 0; j < 100; j++)
    {
        for (int k = 0; k < 100; k++)
        {
            matrizADJTriSup[j][k] = 0;
        }
    }
    int valor = 0;
    int contador = 1;

    int linha = 0;
    int coluna = 1;

    for (int i = 0; i < tamanho; i++)
    {
        valor = vetCompact[i];

        while (contador != valor)
        {
            if (coluna < 100)
            {
                coluna++;
            }
            else
            {
                linha++;
                coluna = linha;
                coluna++;
                contador--;
            }
            contador++;
        }
        matrizADJTriSup[linha][coluna] = 1;
        matrizADJTriSup[coluna][linha] = 1;
    }
}
int posicaoPorIter(int linha, int coluna)
{
    int contadorIteracao = 0;
    bool chegou = false;
    for (int i = 1; i <= 100 && !chegou; i++)
    {
        for (int j = 1; j <= 100 && !chegou; j++)
        {
            if (j > i && !chegou)
            {
                contadorIteracao++;
            }
            if (linha == i && coluna == j)
            {
                chegou = true;
            }
        }
    }
    return contadorIteracao;
}
int posicaoPorRecur(int linha, int coluna, int i, int j, int contador)
{
    if (j > i)
    {
        contador++;
    }
    if (linha == i && coluna == j)
    {
        return contador;
    }
    if (j == 100)
    {
        return posicaoPorRecur(linha, coluna, i + 1, 0, contador);
    }
    else
    {
        return posicaoPorRecur(linha, coluna, i, j + 1, contador);
    }
}

void mapeamento(ofstream &output_file)
{
    int linha, coluna;
    int n = 100;

    cout << "Inserir a linha i entre 1 e 100: ";
    cin >> linha;
    cout << "Inserir a coluna j entre 1 e 100: ";
    cin >> coluna;

    if (linha > coluna || linha < 1 || linha > 100 || coluna < 1 || coluna > 100)
    {
        cout << "Entrada invalida";
        return;
    }

    int calculo = linha * n - n - ((linha * (linha - 1)) / 2) + (coluna - linha);
    output_file << "Posicao no vetor por CALCULO: " << calculo << endl;
    output_file << "Posicao no vetor por ITERACAO: " << posicaoPorIter(linha, coluna) << endl;
    output_file << "Posicao no vetor por RECURCAO: " << posicaoPorRecur(linha, coluna, 1, 1, 0) << endl;
}
void mapeamentoInverso(ofstream &output_file, Graph *graph)
{

    int vetBin[4950];

    int matrizADJ[100][100];
    matrizAdj(matrizADJ, graph);
    vetorBin(vetBin, matrizADJ);
    int tamanho = 0;
    for (int o = 0; o < 4950; o++)
    {
        tamanho = vetBin[o] + tamanho;
    }
    int vetCompact[tamanho];
    vetorCompact(vetBin, vetCompact, tamanho);

    int indice;
    cout << "digite um valor para o indice de 0 a " << tamanho - 1 << endl;
    cin >> indice;

    int valor = vetCompact[indice];

    int contador = 1;
    int linha = 0;
    int coluna = 1;
    while (contador != valor)
    {
        if (coluna < 100)
        {
            coluna++;
        }
        else
        {
            linha++;
            coluna = linha;
            coluna++;
            contador--;
        }
        contador++;
    }

    if (matrizADJ[linha][coluna] == 1)
    {
        output_file << "Aresta encontrada na linha " << linha << " e coluna " << coluna << endl;
    }
    else
    {
        cout << "erro" << endl;
    }
}

int menu()
{

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] matriz adjacência binária" << endl;
    cout << "[2] vetor binario" << endl;
    cout << "[3] vetor compactado" << endl;
    cout << "[4] matriz adjacência binária a partir do vetor compactado" << endl;
    cout << "[5] busca no vetor de valores por parametro i,j" << endl;
    cout << "[6] busca inversa dos valores do vetor para posição na matriz" << endl;
    cout << "[7] Imprimir ordenacao topológica" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
}

void selecionar(int selecao, Graph *graph, ofstream &output_file, int order)
{

    switch (selecao)
    {
    // fechoTransitivoIndireto;
    case 1:
    {
        int matrizADJ[100][100];
        matrizAdj(matrizADJ, graph);
        for (int j = 0; j < order; j++)
        {
            for (int k = 0; k < order; k++)
            {
                output_file << "|" << matrizADJ[j][k];
            }
            output_file << "|" << endl;
        }
        break;
    }
    // fechoTransitivoDireto;
    case 2:
    {
        int vetBin[4950];
        int matrizADJ[100][100];
        matrizAdj(matrizADJ, graph);
        vetorBin(vetBin, matrizADJ);
        for (int o = 0; o < 4950; o++)
        {
            output_file << "|" << vetBin[o];
        }
        output_file << "|" << endl;

        break;
    }
    case 3:
    {
        int vetBin[4950];

        int matrizADJ[100][100];
        matrizAdj(matrizADJ, graph);
        vetorBin(vetBin, matrizADJ);
        int tamanho = 0;
        for (int o = 0; o < 4950; o++)
        {
            tamanho = vetBin[o] + tamanho;
        }
        int vetCompact[tamanho];
        vetorCompact(vetBin, vetCompact, tamanho);
        for (int o = 0; o < tamanho; o++)
        {
            output_file << "|" << vetCompact[o];
        }
        output_file << "|" << endl;
        break;
    }

    // AGM - Kruscal;
    case 4:
    {
        int vetBin[4950];
        int matrizADJ[100][100];
        matrizAdj(matrizADJ, graph);
        vetorBin(vetBin, matrizADJ);
        int tamanho = 0;
        for (int o = 0; o < 4950; o++)
        {
            tamanho = vetBin[o] + tamanho;
        }
        int vetCompact[tamanho];
        vetorCompact(vetBin, vetCompact, tamanho);
        int matrizADJTriSup[100][100];
        matrizAdjPorCompact(vetCompact, tamanho, matrizADJTriSup);
        for (int j = 0; j < order; j++)
        {
            for (int k = 0; k < order; k++)
            {
                output_file << "|" << matrizADJTriSup[j][k];
            }
            output_file << "|" << endl;
        }
        break;
    }
    // AGM Prim;
    case 5:
    {
        mapeamento(output_file);
        break;
    }
    // Imprimir caminhamento em Profundidade
    case 6:
    {
        mapeamentoInverso(output_file, graph);
        break;
    }
    // Ordenação Topologica;
    case 7:
    {

        break;
    }
    // Caminho Mínimo entre dois vértices - Dijkstra
    default:
    {
        cout << " Error!!! invalid option!!" << endl;
    }
    }
}

int mainMenu(ofstream &output_file, Graph *graph)
{

    int selecao = 1;

    while (selecao != 0)
    {
        // system("cls");
        selecao = menu();

        if (output_file.is_open())
            selecionar(selecao, graph, output_file, graph->getOrder());

        else
            cout << "Unable to open the output_file" << endl;

        output_file << endl;
    }

    return 0;
}

int main(int argc, char const *argv[])
{

    // Verificação se todos os parâmetros do programa foram entrados
    if (argc != 2)
    {

        cout << "ERROR: Expecting: ./<program_name> <output_file>" << endl;
        return 1;
    }

    string program_name(argv[0]);

    cout << "Running " << program_name << " ... " << endl;

    // Abrindo arquivo de entrada

    ofstream output_file;

    output_file.open(argv[1], ios::out | ios::trunc);

    Graph *graph;

    graph = geraGraph();

    mainMenu(output_file, graph);

    // Fechando arquivo de entrada

    // Fechando arquivo de saída
    output_file.close();

    return 0;
}
