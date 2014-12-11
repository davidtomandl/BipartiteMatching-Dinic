#include "BipartiteMatching.hpp"
#include <iostream>
#include <string>

using namespace std;

//Default testing
void Test()
{
	BipartiteMatching bm;

	std::ifstream ifs1("Graphs/graph1.txt");
	bm.readGraphList(ifs1);				
	bm.MaximumMatching();				
	cout << "Matching for graph1:"<<endl;
	bm.printMatching(std::cout);
	switch (bm.isPerfect())
	{
	    	case perfet_matching: 
			cout << "Graph has perfet matching."<<endl;
			break;
		case left_perfet_matching: 
			cout << "Graph has left-perfet matching."<<endl;
			break;
		case right_perfet_matching: 
			cout << "Graph has right-perfet matching."<<endl;
			break;

	}
	cout << endl;

	std::ifstream ifs2("Graphs/graph2.txt");
	bm.readGraphBipartite(ifs2);
	bm.MaximumMatching();			
	cout << "Matching for graph2:"<<endl;
	bm.printMatching(std::cout);

	cout << endl;
	
	std::ifstream ifs3("Graphs/graph3.txt");
	bm.readGraphList(ifs3);
	bm.MaximumMatching();			
	cout << "Matching for graph3:"<<endl;
	bm.printMatching(std::cout);
	
	cout << endl;
	
	ifs1.close();
	ifs2.close();
	ifs3.close();

}

//Checks if the given file exists.
inline bool ifFileExists(const char* name) {
  ifstream f(name);
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }   
}

/*Reads command arguments.
* Expected the names of an input file with a graph.
* Format of the given file:
	* an edge list 
	* First number has to be number of vertices in the graph.
	* Then followed by the vertex pair, which forms the edge.
	* Vertices are labeled as a non negative integer from 0 to n-1.
	* Vertices are separated by space.
*
* Thare is also default testing in case one of the argument is test 
* or argument count is eqeul to 1. Then the program ends.
*/
int main(int argc, char** argv)
{
	//DEMO
	if (argc<=1)
	{
		cout << "Default testing..."<<endl;
		Test();
	}
	else
	{
		BipartiteMatching bm;
		// Process the argv
		for(int i=1; i<argc; i++) 
		{
			char* file_name=argv[i];
			if(string(file_name) == "test") {
				cout << "Default testing..."<<endl;
				Test();
				/*cout << "press enter to exit..."<<endl;//delete
				getchar();	*/
				return 0;			
			} else
			{
				
				if (!ifFileExists(file_name))
				{
					cout <<"File "<<file_name<<" doesn't exist."<<endl;
				}
				else
				{
					try{
						std::ifstream ifs(file_name);
						cout << "Matching for "<<file_name<<endl;
						bm.readGraphList(ifs);
						bm.MaximumMatching();
						bm.printMatching(std::cout);
						ifs.close();
					}catch (const exception& e){
						cout << "error: cannot read the given file "<<file_name<<endl;
						cout << e.what()<<endl;
						return 1;
					}
				}
			}
		}
	}
	/*cout << "press enter to exit..."<<endl;
	getchar();	*/
	
	return 0;
};
