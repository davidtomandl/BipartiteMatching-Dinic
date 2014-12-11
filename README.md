BipartiteMatching-Dinic
=======================

Finds a maximum bipartite matching in a graph. Dinic's algorithm for computing the maximum flow in a flow network.
Everything is written in C++11.

<h2>How to use it? </h2>
Download the source files and include header files in your project.
Public methods and functions are described in the header files.
The library assumes correctly entered data.
But basic things is checked  e.g. whether the  graph  is a bipartite?
<h2>Default program</h2>
The program reads command arguments.
Expected the names of input files, a file contains only one graph. <br>
Format of the given file:
<UL>
	<LI>  an edge list 
 	<LI>  First number has to be number of vertices in the graph.
	<LI>  Then followed by the vertex pair, which forms the edge.
	<LI>  Vertices are labeled as a non negative integer from 0 to n-1.
	<LI> Vertices are separated by space.
</UL>

Thare is also default testing in case one of the arguments is <i> test </i> or argument count is eqeul to 1. The program ends.
<h2>Compile</h2>
<blockquote>
g++ -std=c++0x main.cpp BipartiteMatching.cpp MaximumFlow.cpp -o BipartiteMatching
</blockquote>
