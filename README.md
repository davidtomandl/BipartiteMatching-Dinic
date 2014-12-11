BipartiteMatching-Dinic
=======================

Finds a maximum bipartite matching in a graph. Dinic's algorithm for computing the maximum flow in a flow network.
Everything is written in C++11.

<h2>How to use it? </h2>
Download the source files and include header files in your project.
Public methods and functions are described in the header files.
The library assumes correctly entered data.
But basic things is checked  e.g. whether the  graph  is a bipartite?
<h2>Default program.</h2>
The program reads command arguments.
Expected the names of an input file with a graph.

<UL>
Format of the given file:
	<LI>  an edge list 
 	<LI>  First number has to be number of vertices in the graph.
	<LI>  Then followed by the vertex pair, which forms the edge.
	<LI>  Vertices are labeled as a non negative integer from 0 to n-1.
	<LI> Vertices are separated by space.
</UL>

Thare is also default testing in case one of the argument is test  or argument count is eqeul to 1. The program ends.
