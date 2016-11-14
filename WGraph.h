#pragma once
#include "Elements.h"

using namespace std;


class WGraph { //represents a graph with weights different from 1
public:
	
	virtual Element* getneighbors(int vertex) = 0;
	
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
			m_verticesWithDegree[m_degree[i]]++; //populating verticesWithDegree list with each degree's number of occurences
		}
		m_AD /= m_n; //average degree is obtained dividing the sum of all degrees by the number of vertices in a graph
		return m_AD;
	}
	
	float getED(int d) {
		m_ED = new float[m_n];
		for (int i = 0; i < m_n; i++)
			m_ED[i] = 1.0 * m_verticesWithDegree[i] / m_n; //populates empyrical distribution list
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
	
	float Dijkstra(char* pathout, int start = 1, int finish = 0) {   //if has finish, end at finish, else return the tree
        if (start < 1 || start > m_n || finish > m_n) {
            ofstream output(pathout);
            output << "VERTEX NOT FOUND" << endl;
            output.close();
            return -1;
        }
        if (!m_Dijkstra) {
            ofstream output(pathout);
            output << "GRAPH HAS NEGATIVE WEIGHTS" << endl;
            output.close();
            return -2;
        }
        if (start==finish){
        	ofstream output(pathout);
        	output << "DSITANCE = 0" << endl << "START VERTEX IS FINISH VERTEX" << endl;
        	output.close();
        	return 0;
		}
        double* dist;
        dist = new double[m_n]; //declares distance vector
        for (int i = 0; i < m_n; i++) //initializes distance vector
            dist[i] = -1;
        dist[start - 1] = 0;
        priority_queue<PQ_Dijkstra_Element, vector<PQ_Dijkstra_Element>, Compare_PQ_Dijkstra_Element>discovered;
        discovered.push(PQ_Dijkstra_Element(start, dist[start - 1]));
        bool* markingvec; //markingvec contains true if the vertice was just discovered, else false
        markingvec = new bool[m_n]; //marking list creation
        for (int i = 0; i < m_n; i++) //initializes marking vector
            markingvec[i] = false;
        float* distances;
        distances = new float[m_n]; //vertices' distance's array
        for (int i = 0; i < m_n; i++) distances[i] = -1;
        distances[start - 1] = 0;
        int* parent;
        parent = new int[m_n]; //vertices' parent's array
        for (int i = 0; i < m_n; i++) parent[i] = -1;
        parent[start - 1] = 0;
        int u;
        while (!discovered.empty()) {
            u = discovered.top().m_v;
            discovered.pop();
            if (u == finish) {
                ofstream output(pathout);
                output << "Distance = " << dist[u - 1] << endl << endl;
                output << start << endl;
                int temp = parent[u - 1];
                while (temp != start) {
                    output << temp << endl;
                    temp = parent[temp - 1];
                }
                output << finish << endl;
                output.close();
                float ret = dist[u - 1];
                delete dist;
                delete markingvec;
                delete distances;
                delete parent;
                return ret;
            }
            if (!markingvec[u - 1]) {
                markingvec[u - 1] = true;
                for (Element* w = getneighbors(u); w; w = w->next) {
                    if (!markingvec[w->v - 1] && (dist[w->v - 1] == -1 || dist[w->v - 1] > dist[u - 1] + w->weight)) {
                        dist[w->v - 1] = dist[u - 1] + w->weight;
                        discovered.push(PQ_Dijkstra_Element(w->v, dist[w->v - 1]));
                        distances[w->v - 1] = dist[w->v - 1];
                        parent[w->v - 1] = u;
                    }
                }
            }
        }
        if (finish < 1) {
            ofstream output(pathout);
            output << "VERTEX | PARENT | DISTANCE" << endl;
            for (int i = 0; i < m_n; i++)
                if (markingvec[i])
                    output << i + 1 << " | " << parent[i] << " | " << distances[i] << endl;
            output.close();
        }
        delete dist;
        delete markingvec;
        delete distances;
        delete parent;
        return 0;
    }
	
	void MST(char* pathout, int start = 1) { //using Prim's Algorithm
        float* cost;
        cost = new float[m_n]; //declares distance vector
        for (int i = 0; i < m_n; i++) //initializes distance vector
            cost[i] = -1;
        cost[start - 1] = 0;
        priority_queue<PQ_Dijkstra_Element, vector<PQ_Dijkstra_Element>, Compare_PQ_Dijkstra_Element>discovered; //reuses PQ_Dijkstra_Element
        discovered.push(PQ_Dijkstra_Element(start, cost[start - 1]));
        bool* markingvec; //markingvec contains true if the vertice was just discovered, else false
        markingvec = new bool[m_n]; //marking list creation
        for (int i = 0; i < m_n; i++) //initializes marking vector
            markingvec[i] = false;
        int u;
        float c;
        int* neighbor;
        neighbor = new int[m_n]; //vertices' neighbor's array
        for (int i = 0; i < m_n; i++) neighbor[i] = -1;
        neighbor[start - 1] = 0;
        float totalcost = 0;
        ofstream output(pathout);
        output << "VERTEX | NEIGHBOR | DISTANCE" << endl;
        while (!discovered.empty()) {
            u = discovered.top().m_v;
            c = discovered.top().m_weight;
            discovered.pop();
            if (!markingvec[u - 1]) {
                markingvec[u - 1] = true;
                if (u != start) {
                    output << neighbor[u - 1] << " " << u << " " << c << endl;
                    totalcost += c;
                }
                for (Element* w = getneighbors(u); w; w = w->next) {
                    if (!markingvec[w->v - 1] && (cost[w->v - 1] == -1 || cost[w->v - 1] > w->weight)) {
                            cost[w->v - 1] = w->weight;
                            discovered.push(PQ_Dijkstra_Element(w->v, cost[w->v - 1]));
                            neighbor[w->v - 1] = u;
                    }
                }
            }
        }
        output << endl << "Total Cost: " << totalcost;
        output.close();
        delete cost;
        delete markingvec;
        delete neighbor;
    }
	
	void AverageDistance(char* pathout) {
        float sum = 0;
        int total = 0;
        float u;
        for (int i=1 ; i < m_n ; i++)
            for (int k=i; k < m_n; k++) {
                u = Dijkstra(pathout, i, k);
                if (u > 0) {
                    sum += u;
                    total++;
                    cout << sum / total << endl;
                }
            }
        ofstream output(pathout);
        output << "Average Distance = " << sum / total << endl;
        output.close();
    }

protected:
	int m_n; //number of vertices
	int m_m; //number of edges
	float m_AD; //Average Degree
	float* m_ED; //Empyrical Distribution
	int* m_degree; //m_degree[x] contains vertex x+1's degree
	int* m_verticesWithDegree; //m_verticesWithDegree[x] returns how many vertices have degree x
	bool m_Dijkstra;
};
