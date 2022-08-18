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
        Graph(int order);
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
        void insertEdge(int id, int target_id);
        void removeNode(int id);
        bool searchNode(int id);
        Node* getNode(int id);
        void insertAllNodes();
        bool verificaAresta(int vert1, int vert2);
       void printGraph(ofstream &output_file);

      
    private:
        //Auxiliar methods
        

};

#endif // GRAPH_H_INCLUDED