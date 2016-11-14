#pragma once
#include <fstream>
#include <stack>
#include <queue>
#include <iostream>
#include <vector>
using namespace std;


class Element { //represents an element of the linked list used in an adjacency vector
	friend class Graph;
	friend class WGraph;
	friend class ALGraph;
	
public:
	int v; //vertex number
	Element* next; //pointer to the next element
	float weight; //weight of the edge to vertex v
};


class PQ_Component_Element { //element representing a connected component in a priority queue
	friend class Graph;
	friend class WGraph;
	friend class Compare_PQ_Component_Element;
	
private:
	PQ_Component_Element(int comp, int lenght) {
		m_comp = comp;
		m_lenght = lenght;
	}
	int m_comp;
	int m_lenght;
};


class Compare_PQ_Component_Element {
public:
	bool operator()(PQ_Component_Element a, PQ_Component_Element b) { //compares two elements by the lenght of the connected component
		return a.m_lenght < b.m_lenght;
	}
};


class PQ_Dijkstra_Element { //element representing a vertex in a priority queue for Dijkstra's algorithm
	friend class Graph;
	friend class WGraph;
	friend class Compare_PQ_Dijkstra_Element;
	
private:
	PQ_Dijkstra_Element(int v, float weight) {
		m_v = v;
		m_weight = weight;
	}
	int m_v;
	float m_weight;
};


class Compare_PQ_Dijkstra_Element {
public:
	bool operator()(PQ_Dijkstra_Element a, PQ_Dijkstra_Element b) { //compares two elements by the distance to start vertex in Dijkstra's algorithm
		return a.m_weight > b.m_weight;
	}
};

