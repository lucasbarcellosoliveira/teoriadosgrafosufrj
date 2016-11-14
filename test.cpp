#include <iostream>
#include "glib.h"
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <limits>
using namespace std;

ifstream& GotoLine(ifstream& file, unsigned int num){ //ifstream file jumps to line num
    file.seekg(ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    return file;
}

int main() {
    cout << "Press any key to load graph.\n";
    getchar(); //waits for a key to be pressed

    WGraph g("grafo_5.txt");

    //    cout<<g.getPath();
    //    cout<<"\n";
    //    cout<<g.getN();
    //    cout<<"\n";
    //    cout<<g.getM();
    //    cout<<"\n";
    //    cout<<g.getAD();

    cout << "\n\nGraph loaded!" << endl << "Press any key to continue.\n\n\n";
    getchar(); //waits for a key to be pressed



    double duration;
    long int finish;
    long int start;

    start = clock();



//	string temp, temp2;
//	int p1, p2;
//	string a, b;
//	bool p1found=false, p2found=false;
//	ifstream input("rede_colaboracao_vertices.txt");
//	while (getline(input,temp)){
//		string str = temp;
//		istringstream aux(str);
//		getline(aux, a, ',');
//		getline(aux, b, ',');
//		if (b == "Edsger W. Dijkstra"){
//              p1 = atoi(a.c_str());
//              p1found=true;
//        }
//		if (b == "Daniel R. Figueiredo"){
//              p2 = atoi(a.c_str());
//              p2found=true;
//        }
//        if (p1found && p2found) break;
//	}
//
//	g.Dijkstra("pathout.txt", p1, p2);
//	
//	ifstream input2("pathout.txt");
//	ofstream output("converted_pathout.txt");
//	getline(input2,temp2);
//	output<<temp2<<endl;
//	getline(input2,temp2);
//	output<<endl;
//	while(getline(input2,temp2)){
//                                GotoLine(input,atoi(temp2.c_str())); //supposing that the file is ordered
//	                            getline(input,temp);
//	                            string str = temp;
//	                            istringstream aux(str);
//		                        getline(aux, a, ','); //researcher's vertex's number
//		                        getline(aux, b, ','); //resarcher's name
//                                output<<b<<endl;
//    }
//    input.close();
//	input2.close();
//	output.close();
	
	
	
    //    g.generateSummary("dblp_Summary.txt");

    //    g.BFS("as_graph_BFS.txt");

    //    g.DFS("as_graph_DFS.txt");

    //    g.connectedcomponents("as_graph_Components.txt");

    //for (int i=1 ; i<11 ; i++){
    //		g.BFS("xpto.txt", i*1000);
    //	}
    
    //g.diameter("testpath.txt");

    //g.Dijkstra("testpath2.txt", 20, 1);
    
    //g.MST("testpath.txt");
    
    //g.AverageDistance("AD_2.txt");
    
        float sum = 0, u;
        int total = 0, i, k;
        srand(time(NULL));
        while(true){
                    i=(rand()%g.getN())+1;
                    k=(rand()%g.getN())+1;
                    u = g.Dijkstra("AD_2.txt", i, k);
                    if (u > 0) {
                       sum += u;
                       total++;
                       cout << i<< " " << k << " " << sum/total << endl;
                    }
        }
        ofstream output("AD_2.txt");
        output << "Average Distance = " << sum / total << endl;
        output.close();




    finish = clock();

    duration = (finish - start) / (double) CLOCKS_PER_SEC;
    //cout << "Duration: " << duration << endl << endl;

    cout << "Done!\n" << endl << "Press any key to exit.";
    getchar(); //waits for a key to be pressed
}
