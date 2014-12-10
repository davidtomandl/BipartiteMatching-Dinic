#include "BipartiteMatching.hpp"

BipartiteMatching::edgeList BipartiteMatching::MaximumMatching()
{
	if (! setPartite()) 
	{
		throw "Graph is not a bipartite graph.";
	}
	MaximumFlow mf(n_vertices_+2,n_vertices_,n_vertices_+1);

	//create flow network
	for (size_t i = 0; i < n_vertices_; i++)
		for (size_t j = i+1; j < n_vertices_; j++)
			if (graph_.at(i,j)!=0)			
				if (partite_[i]==0)
					mf.addEdge(i,j,1);
				else
					mf.addEdge(j,i,1);

	for (size_t i = 0; i < n_vertices_; i++)		
		if (partite_[i]==0) 
			mf.addEdge(n_vertices_,i,1); //source->i, left partite
		else
			mf.addEdge(i,n_vertices_+1,1); //i->target, right partite

	//find maximum flow 
	std::vector<std::vector<Edge> > flow=mf.Dinic();
	size_t i=0;
	matching_.clear();
	for (auto it=flow.cbegin();it!=flow.cend(); ++it)
	{
		if (flow[i].size()>0)
			for (auto it1=flow[i].cbegin();it1!=flow[i].cend(); ++it1)
				if ((i!=n_vertices_) && (it1->to!=n_vertices_+1))
					if (it1->flow==1)
						matching_.push_back(vertexPair(i,it1->to));
			
		i++;
	}
	
	return matching_;

}

void BipartiteMatching::readGraphBipartite(std::istream& stream)
{
	size_t m,n;
	size_t temp;
	bool first=true;
	stream >>  m >>n;
	n_vertices_=m+n;
	init();
	

	for (size_t i = 0; i < m; i++)
	{
		for (size_t j = 0; j < n; ++j) 
		{
			stream >> temp;
			graph_.set(i,m+j,temp);
			graph_.set(m+j,i,temp);	
			if (first) partite_[m+j]=1;
		}
		partite_[i]=0;
		first=false;
	}
}
void BipartiteMatching::readGraphList(std::istream& stream)
{
	n_vertices_=-1;
	stream >>  n_vertices_;
	if (n_vertices_<0) 
		throw "Failed to read the number of vertices!";
	init();
	size_t u,v;
	while(!stream.eof())
        {
		stream >> u >> v;
		graph_.set(u,v,1);
		graph_.set(v,u,1);
	}

}
void BipartiteMatching::readGraphMatrix(std::istream& stream)
{
	n_vertices_=-1;
	stream >>  n_vertices_;
	if (n_vertices_<0)
		throw "Failed to read the number of vertices!";
	init();
	
	size_t temp;
        for (size_t i = 0; i < n_vertices_; ++i) 
		for (size_t j = 0; j < n_vertices_; ++j) 
		{
			stream >> temp;
			graph_.set(i,j,temp);
		}

}

void BipartiteMatching::init()
{
	graph_.init(n_vertices_, n_vertices_);
	partite_.clear();
	partite_.resize(n_vertices_);
	for (size_t i = 0; i < n_vertices_; i++)
		for (size_t j = 0; j < n_vertices_; j++)
		  graph_.set(i,j,0);
	for (size_t i = 0; i < n_vertices_; ++i) partite_[i]=-1; //-1 -> unused vertex
}

bool BipartiteMatching::setPartite()
{
	std::queue <size_t> q;//FIFO of vertex numbers
        q.push(0);
	partite_[0]=0;

	while (!q.empty())
        {
		size_t u = q.front();
                q.pop();
		// Find all unused adjacent vertices
        	for (size_t v = 0; v < n_vertices_; v++)
	        {
			if (graph_.at(u,v)!=0 &&  partite_[v]==-1)
        	        {                
				partite_[v] = 1 - partite_[u];//set opposite partite
                		q.push(v);
        	        }
			else if (graph_.at(u,v) && partite_[v] == partite_[u])
        			 return false;
		}
		if (q.empty())
			for (size_t i = 0; i <n_vertices_; i++)
				if (partite_[i]==-1)
				{
					q.push(i);
					partite_[i]=0;
					break;
				}
	}
	return true;
}
void BipartiteMatching::addEdge(size_t u, size_t v)
{
	graph_.set(u,v,1);
	graph_.set(v,u,1);
}

void BipartiteMatching::printMatching(std::ostream& stream)
{
	for (auto it = matching_.cbegin(); it != matching_.cend(); ++it)	
		stream<<it->first <<" "<<it->second <<std::endl;	
}
size_t BipartiteMatching::size()
{
	return matching_.size();
}
short BipartiteMatching::isPerfect()
{
	size_t l,r; l=0;r=0;
	for (size_t i = 0; i < n_vertices_; i++)
		if (partite_[i]==0) l++; else r++;
		
	l-=size();
	r-=size();
	
	if ((r==0) && (l==0)) return perfet_matching;
	else if (l==0) return left_perfet_matching;
	else if (r==0) return right_perfet_matching;
	else return 0;

}
