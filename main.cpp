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
#include "Node.h"
#include "Edge.h"
#include "Graph.cpp"
#include "Node.cpp"
#include "Edge.cpp"

using namespace std;

Graph *leitura(ifstream &input_file, int directed, int weightedEdge, int weightedNode)
{

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;

    //Pegando a ordem do grafo
    input_file >> order;

    //Criando objeto grafo
    Graph *graph = new Graph(order, directed, weightedEdge, weightedNode);

    //Leitura de arquivo

    if (!graph->getWeightedEdge() && !graph->getWeightedNode())
    {

        while (input_file >> idNodeSource >> idNodeTarget)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, 1);
        }
    }
    else if (graph->getWeightedEdge() && !graph->getWeightedNode())
    {

        float edgeWeight;

        while (input_file >> idNodeSource >> idNodeTarget >> edgeWeight)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
        }
    }
    else if (graph->getWeightedNode() && !graph->getWeightedEdge())
    {

        float nodeSourceWeight, nodeTargetWeight;

        while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, 1);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
        }
    }
    else if (graph->getWeightedNode() && graph->getWeightedEdge())
    {

        float nodeSourceWeight, nodeTargetWeight, edgeWeight;

        while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
        }
    }

    return graph;
}

Graph *leituraInstancia(ifstream &input_file, int directed, int weightedEdge, int weightedNode)
{

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;
    int numEdges;

    //Pegando a ordem do grafo
    input_file >> order;

    //Criando objeto grafo
    Graph *graph = new Graph(order, directed, weightedEdge, weightedNode);

    //Leitura de arquivo
    while (input_file >> idNodeSource >> idNodeTarget)
    {

        graph->insertEdge(idNodeSource, idNodeTarget, 1);
    }

    return graph;
}

int menu()
{

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] fechoTransitivoIndireto" << endl;
    cout << "[2] Fecho Transitivo Direto" << endl;
    cout << "[3] Caminho Mínimo entre dois vértices - Floyd" << endl;
    cout << "[4] Árvore Geradora Mínima de Kruskal" << endl;
    cout << "[5] Árvore Geradora Mínima de Prim" << endl;
    cout << "[6] Imprimir caminhamento em Profundidade" << endl;
    cout << "[7] Imprimir ordenacao topológica" << endl;
    cout << "[8] Caminho Mínimo entre dois vértices - Dijkstra" << endl;
    cout << "[9] Printando o Grafo " << endl;
    cout << "[10] Algoritmo Guloso Randomizado Reativo" << endl;
    cout << "[11] Algoritmo Guloso Randomizado" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
}

void selecionar(int selecao, Graph *graph, ofstream &output_file)
{

    switch (selecao)
    {
    //fechoTransitivoIndireto;
    case 1:
    {
        int x;
        cout << "Digite o id o noh a ser pesquisado: ";
        cin >> x;
        graph->fechoTransitivoIndireto(output_file, x);
        break;
    }
    //fechoTransitivoDireto;
    case 2:
    {
        int x;
        cout << "Digite o id o noh a ser pesquisado: ";
        cin >> x;
        graph->fechoTransitivoDireto(output_file, x);
        break;
    }
    case 3:
    {
        output_file << "Caminho minimo por Floyd:: " << endl;
        cout << "Digite o vertice de origem:" << endl;
        int origem;
        cin >> origem;
        cout << "Digite o vertice de destino:" << endl;
        int destino;
        cin >> destino;
        graph->floydMarshall(output_file, origem, destino);
        break;
    }

    //AGM - Kruscal;
    case 4:
    {
        Graph *novoSubGrafo = graph->agmKuskal(output_file);
        novoSubGrafo->printGraph(output_file);
        break;
    }
    //AGM Prim;
    case 5:
    {
        Graph *grafoX = graph->agmPrim(output_file);
        grafoX->printGraph(output_file);
        break;
    }
    //Imprimir caminhamento em Profundidade
    case 6:
    {
        int x;
        cout << "Digite o id o noh a por onde começara o caminhamento: ";
        cin >> x;
        Graph *novoGrafo = graph->caminhamentoDeProfundidade(x);
        novoGrafo->printGraph(output_file);
        break;
    }
    //Ordenação Topologica;
    case 7:
    {

        if (graph->getDirected())
        {

            int *ordTop = graph->topologicalSorting();
            if ((ordTop != NULL))
            {
                output_file << "Ordenação Topologica:" << endl;
                for (int i = 0; i < graph->getOrder(); i++)
                {
                    output_file << ordTop[i];
                    output_file << endl;
                }
            }
            else
            {
                output_file << "Grafo possui circuito, nao possui ordenação topologica" << endl;
            }
        }
        else
        {
            output_file << "Grafo não direcionado -  nao possui ordenação topologica" << endl;
        }

        break;
    }
    //Caminho Mínimo entre dois vértices - Dijkstra
    case 8:
    {
        int x, y;
        cout << "Digite o id Source: ";
        cin >> x;
        cout << "Digite o id Target: ";
        cin >> y;
        graph->dijkstra(output_file, x, y);
        break;
    }
    //Printa grafo
    case 9:
    {

        graph->printGraph(output_file);

        break;
    }
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
        system("cls");
        selecao = menu();

        if (output_file.is_open())
            selecionar(selecao, graph, output_file);

        else
            cout << "Unable to open the output_file" << endl;

        output_file << endl;
    }

    return 0;
}

int main(int argc, char const *argv[])
{

    //Verificação se todos os parâmetros do programa foram entrados
    if (argc != 6)
    {

        cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;
        return 1;
    }

    string program_name(argv[0]);
    string input_file_name(argv[1]);

    string instance;
    if (input_file_name.find("v") <= input_file_name.size())
    {
        string instance = input_file_name.substr(input_file_name.find("v"));
        cout << "Running " << program_name << " with instance " << instance << " ... " << endl;
    }

    //Abrindo arquivo de entrada
    ifstream input_file;
    ofstream output_file;
    input_file.open(argv[1], ios::in);
    output_file.open(argv[2], ios::out | ios::trunc);

    Graph *graph;

    if (input_file.is_open())
    {

        graph = leitura(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    }
    else
        cout << "Unable to open " << argv[1];

    mainMenu(output_file, graph);

    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();

    return 0;
}
