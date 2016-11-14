#include <iostream>
#include "glib.h"
#include <ctime>
using namespace std;

int main() {
    cout << "Press any key to load graph.\n";
    getchar(); //waits for a key to be pressed



    ALWGraph g("rede_colaboracao.txt");	//  LOAD THE GRAPH HERE




    cout << "\n\nGraph loaded!" << endl << "Press any key to continue.\n\n\n";
    getchar(); //waits for a key to be pressed



    double duration;
    long int finish;
    long int start;
    start = clock();
    
    
//	g.AverageDistance("grafo_1_Avarege_Distance.txt");
    
//	g.MST("rede_colaboracao_MST.txt");
    
//	g.Dijkstra("grafo_2_Dijkstra.txt",50,1);
    
//	g.generateSummary("grafo_1_Summary.txt");

//	g.BFS("as_graph_BFS.txt");

//	g.DFS("as_graph_DFS.txt");

//	g.connectedcomponents("as_graph_Components.txt");

//	for (int i=1 ; i<11 ; i++){
//		g.DFS("dblp_BFS.txt", i*1000);
//	}

//	for (int i=1 ; i<11 ; i++){
//		g.BFS("dblp_BFS.txt", i*1000);
//	}

   
    finish = clock();
    duration = (finish - start) / (double) CLOCKS_PER_SEC;
    cout << "Duration: " << duration << endl << endl;



    cout << "Done!\n" << endl << "Press any key to exit.";
    getchar(); //waits for a key to be pressed
}
