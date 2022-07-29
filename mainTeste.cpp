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

int main()
{
    ofstream output_file;
    output_file.open("C://Users//Usuario//Documents//repositorio//Trabalho-Grafos-2021-1//testes.txt");

    Graph *grafo = new Graph(6, true, true, false);
    grafo->insertEdge(1, 2, 6);
    grafo->insertEdge(2, 3, 5);
    grafo->insertEdge(3, 4, 4);
    grafo->insertEdge(4, 1, 3);
    grafo->insertEdge(5, 3, 2);
    grafo->insertEdge(6, 2, 1);
    /*grafo->insertEdge(4,6,4);
    grafo->insertEdge(3,5,5);
    grafo->insertEdge(6,7,6);
    grafo->insertEdge(8,7,7);
    grafo->insertEdge(9,8,8);
    grafo->insertEdge(10,9,9);
    grafo->insertEdge(5,15,0);
    grafo->insertEdge(15,16,0);
    grafo->insertEdge(14,15,0);
    grafo->insertEdge(12,13,0);
    grafo->insertEdge(13,11,0);
    grafo->insertEdge(11,7,0);*/

    Graph *subGrafo = grafo->agmKuskal(output_file);

    output_file << " Arvore geradora minima" << endl;
    subGrafo->printGraph(output_file);

    int order = grafo->getOrder();
    cout << "Ordem: " << order << endl;
    grafo->printGraph(output_file);
    grafo->fechoTransitivoIndireto(output_file, 1);

    int x;
    cout<<"digite: "<< endl;
    cin >> x;
    Graph *novoGrafo = grafo->caminhamentoDeProfundidade(x);

    novoGrafo->printGraph(output_file);

    Graph *grafo2 = new Graph(16, false, false, false);
    grafo2->insertEdge(1, 2, 0);
    grafo2->insertEdge(2, 3, 0);
    grafo2->insertEdge(2, 4, 0);
    grafo2->insertEdge(4, 6, 0);
    grafo2->insertEdge(3, 5, 0);
    grafo2->insertEdge(6, 7, 0);
    grafo2->insertEdge(8, 7, 0);
    grafo2->insertEdge(9, 8, 0);
    grafo2->insertEdge(10, 9, 0);
    grafo2->insertEdge(5, 15, 0);
    grafo2->insertEdge(15, 16, 0);
    grafo2->insertEdge(14, 15, 0);
    grafo2->insertEdge(12, 13, 0);
    grafo2->insertEdge(13, 11, 0);
    grafo2->insertEdge(11, 7, 0);
    cout<<"digite: "<< endl;
    cin >> x;
    grafo2->fechoTransitivoIndireto(output_file,x);
    output_file.close();

    return 0;
}