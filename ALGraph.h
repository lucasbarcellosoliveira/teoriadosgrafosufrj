#pragma once
#include "Graph.h"
using namespace std;

class ALGraph : public Graph {
public:
	ALGraph(char* path){
		int a, b;
        ifstream input(path);
        input>>m_n; //number of vertices is obtained from the file's first line
        m_degree = new int[m_n];
        m_verticesWithDegree = new int[m_n];
        m_ED = new float[m_n];
        m_m = 0;
        m_list = new Element*[m_n];
            for (int i = 0; i < m_n; i++) {
                m_list[i] = NULL;
                m_degree[i] = 0; //initializes the degree vector; this line is repeated due to excution time's enhancements
                m_verticesWithDegree[i] = 0; //initializes the verticesWithDegree vector; this line is repeated due to excution time's enhancements
            }
            Element* aux;
            Element* add;
            while (input >> a >> b) { //elements are in ascending order
                m_m++;
                add = new Element();
                add->v = b;
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
            }
        input.close(); //closes ifstream after the graph is loaded
	}
	
	Element* getneighbors(int vertex){
		Element* neighbors;
		neighbors = m_list[vertex-1];
		return neighbors;
	}
	
	~ALGraph(){
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
        delete m_list;
        delete m_ED;
        delete m_degree;
        delete m_verticesWithDegree;
	}
	
protected:
	Element** m_list; //pointer to adjacency vector
};
