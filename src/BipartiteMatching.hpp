//Author: David Tomandl

/* Manual:
*  Firt of all, you hava to initialize the graph ( call the constructor or public method init() ).
*  After then it is necessary to create in some way the bipartite graph.
*  There are more options:
		* Read graph from a stream
			* public method readGraphMatrix()
			    Method read a adjacency matrix from the given stream.
				First number has to be number of vertices in the graph.
				Then followed by individual matrix elements separated by a  space
				M_{i,j}=1 if and only if {i,j} is the edge in the graph, else M_{i,j}=0
			* public method readGrapList()
				Method read a edge list from the given stream.
				First number has to be number of vertices in the graph.
				Then followed by the vertex pair, which forms the edge.
				Vertices are labeled as a non negative  integer from 0 to n-1.
				Vertices are separated by space.
			* public method readGrapBipartite()
			    This is a special format for bipartite graphs.
				Let L be a left partite and R be a right partite.
				The first two numbers are the size of partitas. First number is the size of L.
				Then follows a matrix M, the elements are separated by a space.
				M_{i,j}=1 if and only if i is in L & j is in R & vertices have an edge.
		* use the public method addEdge(), which adds the given adge to the current graph.
* Then call public function MaximumMatching().
	Function returns a list of edges which are in the maximum matching.
	Returns std::vector<std::pair<size_t,size_t>>

* Optional public method/funcion:
	If you want to write the result to the stream use method printMatching()
	Function perfect() returns 1 -> pefect matching, 2->left-perfect matching, 3->right-perfect matching, 0->otherwise.
	The result of this function should be treated with caution. 
	Because how the program can identify which partite is the left and the right.
	It should be useful to know that a graph has perfect matching.
	Function size() returns the number of edges in the matching.
*/
#ifndef BipartiteMatching_hpp_
#define BipartiteMatching_hpp_

#include "MaximumFlow.hpp"
#include <iostream>
#include <fstream>

#define perfet_matching 1
#define left_perfet_matching 2
#define right_perfet_matching 3

//finding maximum matching in a bipartite graph
class BipartiteMatching
{
private:
	typedef std::pair<size_t,size_t> vertexPair;//Edge
	typedef std::vector<vertexPair> edgeList;
public:
	BipartiteMatching(size_t n):n_vertices_(n){init();};
	BipartiteMatching(){};
	~BipartiteMatching(){};
	
	//Adds bidirectional edge; {u,v}
	void addEdge(size_t u, size_t v); 
	//Returns maximum bipartite matching
	edgeList MaximumMatching();
	//initialization
	void init();

	//read from the stream a graph as a adjacency matrix
	//in first line have to be a number of vertices
	void readGraphMatrix(std::istream& stream);
	//reads from the stream graph as a edge list
	//in first line have to be a number of vertices
	void readGraphList(std::istream& stream);
	//reads from the stream graph as a edge list
	//in first line have to be a number of vertices
	void readGraphBipartite(std::istream& stream);
	//prints to the stream the matching as a edge list	
	void printMatching(std::ostream& stream);
	//returns the number of edges in the matching
	size_t size();
	//returns 1 -> pefect matching, 2->left-perfect matching, 3->right-perfect matching, 0->otherwise
	short isPerfect();
	void setNumberOfVertices(size_t n){n_vertices_=n;}

private:
	size_t n_vertices_;
	std::vector<short> partite_;
	Array2 graph_;
	edgeList matching_;
	//This function returns true if graph  is Bipartite, else false
	//and assigns each vertex 0/1: 0-left partite, 1-right partite
	bool setPartite();		

};


#endif /* BipartiteMatching_hpp_ */
