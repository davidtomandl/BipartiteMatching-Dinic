#include "BipartiteMatching.hpp"
#include <iostream>

using namespace std;

int main(int argc, char** argv){
	
	//DEMO
	BipartiteMatching bm;

	std::ifstream ifs1("Graphs/graph1.txt");
	bm.readGraphList(ifs1);				
	bm.MaximumMatching();				
	cout << "Matching for graph1:"<<endl;
	bm.printMatching(std::cout);
	switch (bm.perfect())
	{
	    case 1: 
			cout << "Graph has perfet matching."<<endl;
			break;
		case 2: 
			cout << "Graph has left-perfet matching."<<endl;
			break;
		case 3: 
			cout << "Graph has right-perfet matching."<<endl;
			break;

	}
	cout << endl;

	std::ifstream ifs2("Graphs/graph2.txt");
	bm.readGraphBipartite(ifs2);
	bm.MaximumMatching();			
	cout << "Matching for graph2:"<<endl;
	bm.printMatching(std::cout);
	switch (bm.perfect())
	{
	    case 1: 
			cout << "Graph has perfet matching."<<endl;
			break;
		case 2: 
			cout << "Graph has left-perfet matching."<<endl;
			break;
		case 3: 
			cout << "Graph has right-perfet matching."<<endl;
			break;

	}
	
	cout << endl;
	
	std::ifstream ifs3("Graphs/graph3.txt");
	bm.readGraphList(ifs3);
	bm.MaximumMatching();			
	cout << "Matching for graph3:"<<endl;
	bm.printMatching(std::cout);
	switch (bm.perfect())
	{
	    case 1: 
			cout << "Graph has perfet matching."<<endl;
			break;
		case 2: 
			cout << "Graph has left-perfet matching."<<endl;
			break;
		case 3: 
			cout << "Graph has right-perfet matching."<<endl;
			break;
	}
	
	cout << endl;
	
	ifs1.close();
	ifs2.close();
	ifs3.close();
	cout << "press enter to exit..."<<endl;
	getchar();	
	
	return 0;
};
