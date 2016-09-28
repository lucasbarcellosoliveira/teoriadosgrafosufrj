#include <fstream>
using namespace std;

class Element{ //representes an element of the linked list used in an adjacency vector
      friend class Graph;
      private:
              int v; //vertex number
              Element* next; //pointer to the next element
};

class Graph{
      public:
             Graph(char* path, bool isVector=true){ //if m_isVector is not informed, an adjacency vector is built by default
                         int a, b;
                         m_path=path;
                         m_isVector=isVector;
                         ifstream input(path);
                         input>>m_n; //number of vertices is obtained from the file's first line
                         m_degree=new int[m_n];
                         m_verticesWithDegree=new int[m_n];
                         m_ED=new float[m_n];
                         m_m=0;
                         if(!m_isVector){ //adjacency matrix creation
                                 m_matrix=new bool*[m_n];
                                 for(int i=0;i<m_n;i++){
                                         m_matrix[i]=new bool[m_n];
                                         for(int k=0;k<m_n;k++)
                                                 m_matrix[i][k]=false; //initializes the adjacency matrix
                                         m_degree[i]=0; //initializes the degree vector
                                         m_verticesWithDegree[i]=0; //initializes the verticesWithDegree vector
                                 }

                                 while(input>>a>>b){ //a and b are the two vertices related by the edge being read
                                                    m_m++; //increments the number of edges
                                                    m_matrix[a-1][b-1]=true; //turns the proper matrix's cell into true
                                                    m_matrix[b-1][a-1]=true; //since a non-directional graph is being read, the adjacency matrix is symmetric
                                                    m_degree[a]++; //increments both vertices degrees
                                                    m_degree[b]++; //increments both vertices degrees
                                 }
                         }
                         else{ //adjacency vector creation
                                m_vector=new Element*[m_n];
                                for(int i=0;i<m_n;i++){
                                        m_vector[i]=NULL;
                                        m_degree[i]=0; //initializes the degree vector; this line is repeated due to excution time's enhancements
                                        m_verticesWithDegree[i]=0; //initializes the verticesWithDegree vector; this line is repeated due to excution time's enhancements
                                }
                                Element* aux;
                                while(input>>a>>b){ //elements are inserted in the beginning of vertices' lists
                                                   m_m++;
                                                   aux=new Element();
                                                   aux->v=b;
                                                   aux->next=m_vector[a-1];
                                                   m_vector[a-1]=aux;
                                                   aux=new Element();
                                                   aux->v=a;
                                                   aux->next=m_vector[b-1];
                                                   m_vector[b-1]=aux;
                                                   m_degree[a]++; //increments both vertices degrees
                                                   m_degree[b]++; //increments both vertices degrees
                                }
                         }
                         m_AD=0;
                         for(int i=0;i<m_n;i++){
                                            m_AD+=m_degree[i]; //summing degrees of every vertex
                                            m_verticesWithDegree[m_degree[i]]++; //populating verticesWithDegree vector with each degree's number of occurences
                         }
                         m_AD/=m_n; //average degree is obtained dividing the sum of all degrees by the number of vertices in a graph
                         for(int i=0;i<m_n;i++)
                                 m_ED[i]=1.0*m_verticesWithDegree[i]/m_n; //populates empyrical distribution vector
                         input.close(); //closes ifstream after the graph is loaded
             }
             bool isVector(){
                  return m_isVector;
             }
             char* getPath(){
                    return m_path;
             }
             int getN(){
                 return m_n;
             }
             int getM(){
                 return m_m;
             }
             float getAD(){
                   return m_AD;
             }
             float getED(int d){
                   return m_ED[d];
             }
             int getDegree(int v){
                 return m_degree[v-1];
             }
             void generateSummary(char* path){
                  ofstream output(path);
                  output<<"# n = "<<m_n<<"\n";
                  output<<"# m = "<<m_m<<"\n";
                  output<<"# average_degree = "<<m_AD<<"\n";
                  for(int i=0;i<m_n;i++)
                          output<<i<<" "<<m_ED[i]<<"\n";
                  output.close();
             }
             ~Graph(){ //destructor
                      if(!m_isVector){
                              for(int i=0;i<m_n;i++)
                                      delete m_matrix[i];
                              delete m_matrix;
                      }
                      else{
                           Element* aux;
                           Element* aux2;
                           for(int i=0;i<m_n;i++){
                                             aux=m_vector[i];
                                             if(aux)
                                                    while(aux->next){
                                                                     aux2=aux->next;
                                                                     delete aux;
                                                                     aux=aux2;
                                                    }
                           }
                           delete m_vector;
                      }
                      delete m_ED;
                      delete m_degree;
                      delete m_verticesWithDegree;
             }
      private:
              char* m_path; //path to a file in which a graph is stored
              bool m_isVector; //true for adjacency vector, false for adjacency matrix
              int m_n; //number of vertices
              int m_m; //number of edges
              float m_AD; //Average Degree
              float* m_ED; //Empyrical Distribution
              bool** m_matrix; //pointer to adjacency matrix
              Element** m_vector; //pointer to adjacency vector
              int* m_degree; //m_degree[x] contains vertex x+1's degree
              int* m_verticesWithDegree; //m_verticesWithDegree[x] returns how many vertices have degree x
};
