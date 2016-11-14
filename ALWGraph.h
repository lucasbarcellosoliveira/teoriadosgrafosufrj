#pragma once
#include "WGraph.h"
using namespace std;


class ALWGraph : public WGraph {
	friend class WGraph;
public:
	ALWGraph(char* path){
		int a, b;
        double c;
        ifstream input(path);
        input>>m_n; //number of vertices is obtained from the file's first line
        m_degree = new int[m_n];
        m_verticesWithDegree = new int[m_n];
        m_ED = new float[m_n];
        m_m = 0;
        m_Dijkstra = true;
		m_list = new Element*[m_n];
            for (int i = 0; i < m_n; i++) {
                m_list[i] = NULL;
                m_degree[i] = 0; //initializes the degree list; this line is repeated due to excution time's enhancements
                m_verticesWithDegree[i] = 0; //initializes the verticesWithDegree list; this line is repeated due to excution time's enhancements
            }
            Element* aux;
            Element* add;
            while (input >> a >> b >> c) { //elements are in ascending order
                m_m++;
                add = new Element();
                add->v = b;
                add->weight = c;
                if (!m_list[a - 1]) { //checks if a vertex's list is empty
                    add->next = m_list[a - 1];
                    m_list[a - 1] = add;
                } else {
                    if (m_list[a - 1]->v > b) { //checks if element must be inserted in the first position
                        add->next = m_list[a - 1];
                        m_list[a - 1] = add;
                    } else {
                        aux = m_list[a - 1];
                        if (aux->next)
                            while (aux->next->v < b) { //checks where in the linked list the new element must be inserted
                                aux = aux->next;
                                if (!aux->next)
                                    break;
                            }
                        add->next = aux->next;
                        aux->next = add;
                    }
                }
                add = new Element();
                add->v = a;
                add->weight = c;
                if (!m_list[b - 1]) { //checks if a vertex's list is empty
                    add->next = m_list[b - 1];
                    m_list[b - 1] = add;
                } else {
                    if (m_list[b - 1]->v > a) { //checks if element must be inserted in the first position
                        add->next = m_list[b - 1];
                        m_list[b - 1] = add;
                    } else {
                        aux = m_list[b - 1];
                        if (aux->next)
                            while (aux->next->v < a) { //checks where in the linked list the new element must be inserted
                                aux = aux->next;
                                if (!aux->next)
                                    break;
                            }
                        add->next = aux->next;
                        aux->next = add;
                    }
                }
                m_degree[a]++; //increments both vertices degrees
                m_degree[b]++; //increments both vertices degrees
                if (c < 0)
                    m_Dijkstra = false;
            }
		input.close(); //closes ifstream after the graph is loaded
	}
	
	Element* getneighbors(int vertex){
		Element* neighbors;
		neighbors = m_list[vertex-1];
		return neighbors;
	}
	
	~ALWGraph(){
		Element* aux;
        Element* aux2;
        for (int i = 0; i < m_n; i++) {
            aux = m_list[i];
            if (aux)
                while (aux->next) {
                    aux2 = aux->next;
                    delete aux;
                    aux = aux2;
                }
		}
	}

protected:
	Element** m_list; //pointer to adjacency list
};
