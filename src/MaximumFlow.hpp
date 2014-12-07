//Author: David Tomandl

#ifndef MaximumFlow_hpp_
#define MaximumFlow_hpp_

#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

class Edge {
public:
	Edge(size_t to,double capacity,double flow):to(to),capacity(capacity),flow(flow){};
	size_t to;
    double capacity,flow; 
	
};

//Class for computing the maximum flow in a flow network using Dinic's algorithm.
class MaximumFlow
{
private:
	typedef std::vector<std::vector<Edge> > flow_network;//adjacency list
	typedef std::vector<Edge> edgeVector;
public:	
	MaximumFlow(size_t n,size_t source, size_t target):n_vertices_(n),source_(source),target_(target){net_.resize(n_vertices_);}
	MaximumFlow(){}
	~MaximumFlow(){}
	void setSource(size_t s){source_=s;}
	void setTarget(size_t t){target_=t;}
	void setNumberOfVertices(size_t n){n_vertices_=n;}
	
	void setNetwork(double const *const *capacity);

	// Adds directional edge with a capacity; from->to
	void addEdge(size_t from, size_t to, double capacity); 
	//finds the maximum flow in the given flow network
	//returns adjacency list with flow
	flow_network Dinic();

	
private:
	size_t source_,target_;
	size_t n_vertices_; 
	flow_network net_;
	//length of the shortest path in the flow network from the source to the target
	//Returns if the target is reachable from the source. 
	//Sets parameters "length" to the length of this path.
	bool shortestPath(size_t & lenght,flow_network& lNet);
	//constructs the layered network based on the given residual network
	void layeredNetwork(flow_network &);
	//constructs the residual network based on the given flow network
	void residualNetwork(flow_network &);
	//adds flow f to the current flow; (f+f')(x,y)=f(x,y)+f'(x,y)
	void addFlow(const flow_network & f);
	//finds blocking flow
	void blockingFlow(flow_network & );

	void init(flow_network& fNet,std::vector<size_t>& path);
	void forward(flow_network& fNet,std::vector<size_t>& path);
	void backward(flow_network& fNet,std::vector<size_t>& path);
	void increase(flow_network& fNet,std::vector<size_t>& path);
	
	edgeVector::iterator findEdge(size_t u,size_t v,flow_network &fNet);
};



class Array2{
 public:
   Array2(){};
   Array2(size_t rows, size_t cols){init(rows, cols);};   
   void init(size_t rows, size_t cols)
   {
	   cols_=cols;
	   rows_=rows;
	   Arr_.clear();
	   Arr_.resize(rows * cols);
   }
   size_t at(size_t i, size_t j)
   {
	   return Arr_[i*cols_+j];
   }
   void set(size_t i, size_t j,size_t val)
   {
	   Arr_[i*cols_+j]=val;
   }
   ~Array2(){};
private:
   std::vector<size_t> Arr_;
   size_t rows_;
   size_t cols_;
};

#endif /* MaximumFlow_hpp_ */
