#include <iostream>
#include "glib.h"

using namespace std;

int main(){
    cout<<"Press any key to load graph.\n";
    getchar(); //waits for a key to be pressed

    Graph g("as_graph.txt");

//    cout<<g.getPath();
//    cout<<"\n";
//    cout<<g.getN();
//    cout<<"\n";
//    cout<<g.getM();
//    cout<<"\n";
//    cout<<g.getAD();

    cout<<"\n\nGraph loaded!\nPress any key to generate a summary.\n\n\n";
    getchar(); //waits for a key to be pressed

    g.generateSummary("as_graph_Summary.txt");

    cout<<"Done!\n";
    getchar(); //waits for a key to be pressed
}
