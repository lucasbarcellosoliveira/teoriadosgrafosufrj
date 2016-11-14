#pragma once
#include "Elements.h"
using namespace std;


class Graph {
public:

	virtual Element* getneighbors(int vertex) = 0; // get a list with vertice's neighbors

	int getN() {
        return m_n;
    }

    int getM() {
        return m_m;
    }

    float getAD() {
    	m_AD = 0;
        for (int i = 0; i < m_n; i++) {
            m_AD += m_degree[i]; //summing degrees of every vertex
            m_verticesWithDegree[m_degree[i]]++; //populating verticesWithDegree vector with each degree's number of occurences
        }
        m_AD /= m_n; //average degree is obtained dividing the sum of all degrees by the number of vertices in a graph
        return m_AD;
    }

    float getED(int d) {
    	for (int i = 0; i < m_n; i++)
            m_ED[i] = 1.0 * m_verticesWithDegree[i] / m_n; //populates empyrical distribution vector
        return m_ED[d];
    }

    int getDegree(int v) {
        return m_degree[v - 1];
    }

    void generateSummary(char* path) {
        ofstream output(path);
        output << "# n = " << m_n << endl;
        output << "# m = " << m_m << endl;
        output << "# average_degree = " << getAD() << endl;
        for (int i = 0; i < m_n; i++)
            output << i << " " << getED(i) << endl;
        output.close();
    }

	int BFS(char* pathout, int root = 1){
		if (root < 1 || root > m_n) {
			ofstream output(pathout);
			output << "VERTEX NOT FOUND" << endl;
			output.close();
			return -1;
		}
		int maxway = 0; //farther distance from the root
		bool* markingvec; //markingvec contains true if the vertice was just discovered, else false
		markingvec = new bool[m_n]; //marking list creation
		for (int i = 0; i < m_n; i++) markingvec[i] = false; //fill the marking list with false
		markingvec[root - 1] = true;
		int* level;
		level = new int[m_n]; //vertices' level's array
		for (int i = 0; i < m_n; i++) level[i] = -1;
		level[root - 1] = 0;
		int* parent;
		parent = new int[m_n]; //vertices' parent's array
		for (int i = 0; i < m_n; i++) parent[i] = -1;
		parent[root - 1] = 0;
		int u;
		queue<int>discovered; //queue of discovered vertices creation
		discovered.push(root);
		while (!discovered.empty()) { //while have elements in queue, do
			u = discovered.front();
			discovered.pop();
			for (Element* w=getneighbors(u) ; w ; w=w->next){
				if (!markingvec[w->v-1]){
					markingvec[w->v-1] = true;
					level[w->v-1] = level[u-1] + 1;
					parent[w->v-1] = u;											//	BFS PARA QUALQUER ESTRUTURA DE DADOS AQUI!!!!
					discovered.push(w->v);
					if (level[w->v - 1] > maxway){
						maxway = level[w->v - 1];
					}
				}
			}
		}
		ofstream output(pathout);
		output << "VERTEX | PARENT | LEVEL" << endl;
		for (int i = 0; i < m_n; i++)
			if (markingvec[i]) //spanning tree must be connected
				output << i + 1 << " | " << parent[i] << " | " << level[i] << endl;
		output.close();
		delete markingvec;
		delete level;
		delete parent;
		return maxway;
	}
	
	int DFS(char* pathout, int root = 1) {
        if (root < 1 || root > m_n) {
            ofstream output(pathout);
            output << "VERTEX NOT FOUND" << endl;
            output.close();
            return -1;
        }
        int maxway = 0; //farther distance from the root
        bool* markingvec; //markingvec contains true if the vertice was just discovered, else false (Used in BFS)
        markingvec = new bool[m_n]; //marking vector creation
        for (int i = 0; i < m_n; i++) markingvec[i] = false; //fill the marking vector with false
        int* level;
        level = new int[m_n]; //vertices' level's array
        for (int i = 0; i < m_n; i++) level[i] = -1;
        level[root - 1] = 0;
        int* parent;
        parent = new int[m_n]; //vertices' parent's array
        for (int i = 0; i < m_n; i++) parent[i] = -1;
        parent[root - 1] = 0;
        int u;
        stack<int>discovered; //stack of discovered vertices creation
        discovered.push(root);
        while (!discovered.empty()) { //while have elements in queue, do
            u = discovered.top();
            discovered.pop();
            if (!markingvec[u - 1]) {
                markingvec[u - 1] = true;
                for (Element* w = getneighbors(u); w; w = w->next) {
                    if (!markingvec[w->v - 1]) {
                        discovered.push(w->v);
                        level[w->v - 1] = level[u - 1] + 1;
                        parent[w->v - 1] = u;
                        if (level[w->v - 1] > maxway)
                            maxway = level[w->v - 1];
                    }
                }
            }
        }
        ofstream output(pathout);
        output << "VERTEX | PARENT | LEVEL" << endl;
        for (int i = 0; i < m_n; i++)
            if (markingvec[i]) //spanning tree must be connected
                output << i + 1 << " | " << parent[i] << " | " << level[i] << endl;
        output.close();
        delete markingvec;
        delete level;
        delete parent;
        return maxway;
    }
    
    void connectedcomponents(char* pathout) {
        int* markingvec; //markingvec contains true if the vertice was just discovered, else false (Used in BFS)
        markingvec = new int[m_n]; //marking vector creation
        for (int i = 0; i < m_n; i++) markingvec[i] = -1; //set all vertices as unmarked
        int nextvertex = 1;
        int component = 1;
        int numberofcomponents = 0;
        int componentlenght;
        priority_queue<PQ_Component_Element, vector<PQ_Component_Element>, Compare_PQ_Component_Element>largestcomponent; //declares priority queue whose nodes are connected components
        //begin of BFS implementation
        int u;
        queue<int>discovered; //queue of discovered vertices creation
        while (nextvertex != -1) {
            numberofcomponents++;
            componentlenght = 1;
            markingvec[nextvertex - 1] = component;
            discovered.push(nextvertex);
            while (!discovered.empty()) { //while have elements in queue, do
                u = discovered.front();
                discovered.pop();
                for (Element* w = getneighbors(u); w; w = w->next) {
                    if (markingvec[w->v - 1] == -1) {
                        markingvec[w->v - 1] = component;
                        componentlenght++;
                        discovered.push(w->v);
                    }
                }
            }
            largestcomponent.push(PQ_Component_Element(component, componentlenght)); //puts component in the priority queue
            component++;
            nextvertex = -1;
            for (int i = 0; i < m_n; i++)
                if (markingvec[i] == -1) //checks if there are unvisited vertices
                    nextvertex = i + 1; //if so, the next BFS will start from the first unvisited vertex found
        }
        //end of BFS implementation
        ofstream output(pathout);
        output << numberofcomponents << " connected component(s)" << endl << endl;
        int x, y;
        for (int i = 0; i < numberofcomponents; i++) {
            x = largestcomponent.top().m_comp; //reads largest component from priority queue
            y = largestcomponent.top().m_lenght;
            largestcomponent.pop();
            output << "Component " << x << " has the following " << y << " vertices:" << endl;
            for (int k = 0; k < m_n; k++)
                if (markingvec[k] == x)
                    output << k + 1 << endl; //prints vertices thar are part of such component
            output << endl << endl;
        }
        output.close();
        delete markingvec;
    }
    
    void diameter(char* path) {
        int diameter = 0;
        for (int i = m_n; i > 0; i--) {
            cout << diameter << " | ";
            if (this->BFS(path, i) > diameter) {
                diameter = this->BFS(path, i);
            }
        }
        ofstream output(path);
        output << "Diameter = " << diameter << endl;
        output.close();
    }
	
protected:
    int m_n; //number of vertices
    int m_m; //number of edges
    float m_AD; //Average Degree
    float* m_ED; //Empyrical Distribution
    int* m_degree; //m_degree[x] contains vertex x+1's degree
    int* m_verticesWithDegree; //m_verticesWithDegree[x] returns how many vertices have degree x
};
