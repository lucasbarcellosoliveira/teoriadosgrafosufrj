#pragma once
#include "WGraph.h"
using namespace std;


class AMWGraph : public WGraph {
	friend class WGraph;
public: 
	AMWGraph(char* path){
		int a, b;
		double c;
		ifstream input(path);
		input>>m_n;
		m_degree = new int[m_n];
		m_verticesWithDegree = new int[m_n];
		m_m = 0;
		m_Dijkstra = true;
		m_matrix = new double*[m_n];
		for (int i = 0; i < m_n; i++) {
			m_matrix[i] = new double[m_n]; //in the future, must implement the storage of just half o the matrix, as the graph is undirected
			for (int k = 0; k < m_n; k++)
				m_matrix[i][k] = -1; //initializes the adjacency matrix
			m_degree[i] = 0; //initializes the degree vector
			m_verticesWithDegree[i] = 0; //initializes the verticesWithDegree vector
		}
		while (input >> a >> b >> c) { //a and b are the two vertices related by the edge being read and c is the edge's weight
			m_m++; //increments the number of edges
			m_matrix[a - 1][b - 1] = c; //stores the edge's weight
			m_matrix[b - 1][a - 1] = c; //matrix is symmetric
			m_degree[a]++; //increments both vertices degrees
			m_degree[b]++; //increments both vertices degrees
			if (c < 0)
				m_Dijkstra = false;
		}
		input.close(); //closes ifstream after the graph is loaded
	}
	
	Element* getneighbors(int vertex){
		Element* neighbors = NULL;
		Element* aux;
		for (int i=m_n ; i>0 ; i-- ){
			if (m_matrix[vertex-1][i-1] != -1){
				aux = new Element;
				aux->v = i;
				aux->weight = m_matrix[vertex-1][i-1]; 
				aux->next = neighbors;
				neighbors = aux;
			}
		}
		return neighbors;
	}
	
	~AMWGraph(){
		for (int i = 0; i < m_n; i++)
            delete m_matrix[i];
        delete m_matrix;
        delete m_ED;
        delete m_degree;
        delete m_verticesWithDegree;
	}

protected:
	double** m_matrix; //pointer to adjacency matrix
};


