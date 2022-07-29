/**************************************************************************************************
 * Implementation of the TAD Graph
**************************************************************************************************/
/**************************************************************************************************
 * Implementation of the TAD Graph
**************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include <fstream>
#include <stack>
#include <list>
#include <sstream>
#include<string>

using namespace std;

class Graph{

    
    //Atributes
    private:
        int order;
        int number_edges;
        bool directed;
        bool weighted_edge;
        bool weighted_node;
        bool conexGraph;
        Node* first_node;
        Node* last_node;

    public:
        //Constructor
        Graph(int order, bool directed, bool weighted_edge, bool weighted_node);
        Graph(bool directed, bool weighted_edge, bool weighted_node);
        //Destructor
        ~Graph();
        //Getters
        int getOrder();
        int getNumberEdges();
        bool getDirected();
        bool getWeightedEdge();
        bool getWeightedNode();
        Node* getFirstNode();
        Node* getLastNode();
        //Other methods
        void insertNode(int id);
        void insertEdge(int id, int target_id, float weight);
        void removeNode(int id);
        bool searchNode(int id);
        Node* getNode(int id);
        void insertAllNodes();

        void fechoTransitivoDireto(ofstream &output_file, int id);
        void fechoTransitivoIndireto(ofstream &output_file, int id);

        bool deepthFirstSearch1(int id, int start);
        void deepthFirstSearch(Graph *novoGrafo, int start);

        void auxDeepthFirstSearch1(bool verify[], Node *v);
        void auxDeepthFirstSearch(bool verify[], Graph *novoGrafo, Node *v);

        Graph* caminhamentoDeProfundidade(int x);
        int * topologicalSorting();
        bool graphtemCiclo();
        Graph *getVertexInduced(int *listIdNodes, int tam);
        
        Graph *agmKuskal(ofstream &output_file);
        void getWeithlessEdge( int *nohAresta);
        int getWeightFromEdgeNodeCombo(int idNoh, int idAresta, Graph *subGrafo);
        bool verificaSubarvore(int v1, int v2, Graph *subGrafo);

        Graph *agmPrim(ofstream &output_file);

        void floydMarshall(ofstream &output_file, int idSource, int idTarget);
        int**constroiFloyd(int tamanho, int **distancia);
        void dijkstra(ofstream &output_file,int idSource, int idTarget);
        void printGraph(ofstream &output_file);
        
        //methods phase1
        float greed();
        float greedRandom();
        float greedRactiveRandom();
    private:
        //Auxiliar methods
        

};

#endif // GRAPH_H_INCLUDED