#pragma once
#include "Graph.h"
using namespace std;

class AMGraph : public Graph {
	friend class Graph;
public:
	AMGraph(char* path){
		int a, b;
		ifstream input(path);
        input>>m_n; //number of vertices is obtained from the file's first line
        m_degree = new int[m_n];
        m_verticesWithDegree = new int[m_n];
        m_ED = new float[m_n];
        m_m = 0;
        m_matrix = new bool*[m_n];
            for (int i = 0; i < m_n; i++) {
                m_matrix[i] = new bool[m_n];
                for (int k = 0; k < m_n; k++)
                    m_matrix[i][k] = false; //initializes the adjacency matrix
                m_degree[i] = 0; //initializes the degree vector
                m_verticesWithDegree[i] = 0; //initializes the verticesWithDegree vector
            }

            while (input >> a >> b) { //a and b are the two vertices related by the edge being read
                m_m++; //increments the number of edges
                m_matrix[a - 1][b - 1] = true; //turns the proper matrix's cell into true
                m_matrix[b - 1][a - 1] = true; //since a non-directional graph is being read, the adjacency matrix is symmetric
                m_degree[a]++; //increments both vertices degrees
                m_degree[b]++; //increments both vertices degrees
			}
		input.close(); //closes ifstream after the graph is loaded
	}
	
	Element* getneighbors(int vertex){
		Element* neighbors = NULL;
		Element* aux;
		for (int i=m_n ; i>0 ; i-- ){
			if (m_matrix[vertex-1][i-1]){
				aux = new Element;
				aux->v = i;
				aux->next = neighbors;
				neighbors = aux;
			}
		}
		return neighbors;
	}
	
	~AMGraph(){
		for (int i = 0; i < m_n; i++)
            delete m_matrix[i];
        delete m_matrix;
        delete m_ED;
        delete m_degree;
        delete m_verticesWithDegree;
	}

protected:
	bool** m_matrix; //pointer to adjacency matrix
};
