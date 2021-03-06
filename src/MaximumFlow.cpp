#include "MaximumFlow.hpp"

void MaximumFlow::addEdge(size_t from, size_t to, double capacity){
	net_[from].push_back(Edge(to,capacity,0));
};


const MaximumFlow::flow_network& MaximumFlow::Dinic()
{
	//starting with zero flow, current flow f is saved in net_
	flow_network R;
	while (true)
	{
		R=net_;
		residualNetwork(R); //create the residual network base on the actual flow f.
		if (!shortestPath(R)) break; 
		layeredNetwork(R); 
		blockingFlow(R); //find the blocking flow f' on the layered network R defined by the current flow
		
	}
	return net_;
}

void MaximumFlow::blockingFlow(flow_network & fNet)
{
	bool exist_path=true; //path source_ -> target_
	size_t x;
	std::vector<size_t> path;	

	while (exist_path) 
	{
		path.clear();
		x=source_;
		path.push_back(x);

		while(true)
		{
			if (fNet[x].size()==0) //can't go forward
			{
				//try to go backward
				if (x!=source_) 
				{
					//Let (v,x) is the last edge in path.
					path.pop_back(); //remove x from path
					size_t v=path.back();
					//remove edge (v,x) from the layered network
					if (fNet[v].size()==1) 
						fNet[v].clear();
					else
					{
						edgeVector::iterator it=findEdge(v,x,fNet);
						if (it!=fNet[v].end())
							fNet[v].erase(it);
					}	
					x=v;
				}
				else //doesn't exist a path to target_ 
				{
					exist_path=false;
					break;
				}
			}
			else //go forward
			{
				size_t y=fNet[x][0].to;
				path.push_back(y);
				x=y;
				if (y==target_) //found the path from source_ to target_
				{
				   increase(fNet,path);//upgrade the current flow
				   break;              //try to find another path
				}
			}
		}
	}
	
}

//increase the current flow base on the given augmenting path
void MaximumFlow::increase(flow_network &lNet,std::vector<size_t>& path)
{
	double d=INT_MAX;
	size_t x,y;
	size_t size=path.size();
	//residual capacity; d is minimum on the path
	for (size_t i = 1; i < size; i++)
	{
		x=path[i-1];
		y=path[i];
		edgeVector::iterator it=findEdge(x,y,lNet);
		if (it->flow<d) d=it->flow;
	}
	for (size_t i = 1; i < size;i++)
	{
		x=path[i-1];
		y=path[i];		
		edgeVector::iterator it1=findEdge(x,y,lNet);
		it1->flow-=d;
		edgeVector::iterator it=findEdge(x,y,net_);
		if (it<net_[x].end())//edge (x,y)
			it->flow+=d;
		else
		{
			it=findEdge(y,x,net_); //edge (y,x)
			if (it!=net_[y].end())
				it->flow-=d;
		}
		if (it->flow==it->capacity)
		{
			//remove saturated edge from the layered network
			if (lNet[x].size()==1) 
				lNet[x].clear();
			else
			{
				//edgeVector::iterator it=findEdge(x,y,fNet);
				if (it1!=lNet[x].end())
					lNet[x].erase(it1);
			}
		}
	}
	
}

void MaximumFlow::addFlow(const flow_network & f )
{
	size_t i=0;
	for (flow_network::const_iterator it=net_.begin();it!=net_.end(); ++it)
	{
		size_t j=0;
		for (edgeVector::const_iterator it1=f[i].begin();it1!=f[i].end(); ++it1)
		{
			net_[i][j].flow=f[i][j].flow+net_[i][j].flow;			
			j++;
		}
		i++;
	}
	
}
void MaximumFlow::residualNetwork(flow_network& lNet)
{
	size_t i=0;
	size_t  size_net=net_.size();
	for (;i<size_net;i++)
	{
		size_t j=0;
		size_t k=0;
		size_t size=net_[i].size();
		for (;j<size;j++,k++)
		{
			double f=net_[i][j].flow;
			double c=net_[i][j].capacity;
			size_t v=net_[i][j].to;				
			if (lNet[i].size()>k)
				lNet[i][k].flow=c-f;
			else
				lNet[i].push_back(Edge(v,c,c-f));
			
			if (f>0) 									
				lNet[v].push_back(Edge(i,c,f));				
			if (c==f)
			{
				if (lNet[i].size()==1) 
					lNet[i].clear();
				else
				{
					edgeVector::iterator it1=findEdge(i,v,lNet);
					if (it1!=lNet[i].end())
						lNet[i].erase(it1);
				}
				k--;
			}				
		}				
	}

}
void MaximumFlow::layeredNetwork(flow_network& lNet)
{
	std::queue<size_t> fifo; 
	std::vector<short> color;//each vertex has color:0-unused,1-processing,2-used
	std::vector<size_t> layer; 	
	//sets all vetices to unused
	std::for_each(lNet.cbegin(), lNet.cend(), [&color](const edgeVector&){color.push_back(false);});
	layer.resize(color.size());
	fifo.push(source_);
	size_t u; //temp: vertex
	bool find=false;
	while (!fifo.empty()){
		u=fifo.front();
		fifo.pop();
		const edgeVector copyVector = lNet[u];
		for (edgeVector::const_iterator it=copyVector.cbegin();it!=copyVector.cend(); ++it)
		{
			int v=it->to;
			if (color[v]==0)
			{ 
				fifo.push(v);
				layer[v]=layer[u]+1; 
				color[v]=1;
			}
			else // edge in the layer or backward edge
			{
				if (!(layer[v]==layer[u]+1))
					if (lNet[u].size()==1) 
						lNet[u].clear();
					else
						lNet[u].erase(findEdge(u,v,lNet));
			}
		}		
		color[u]=2;		
	}
	
	size_t i=0;
	//remove unreachable vertices
	for (flow_network::const_iterator it=lNet.begin();it!=lNet.end(); ++it)
	{
		if (color[i]==0)
		{
			lNet[i].clear();
		}
		i++;
	}
}

bool MaximumFlow::shortestPath(const flow_network& lNet)
{
	std::queue<size_t> fifo; 
	typedef std::pair <bool,size_t> vertex;//used;distance
	std::vector<vertex> vertices; 
	//for each vertex do:  unused, distance=0
	std::for_each(lNet.cbegin(), lNet.cend(), [&vertices](const edgeVector&){vertices.push_back(vertex(false,0));});

	fifo.push(source_);
	size_t u; //vertex
	bool find=false;
		
	while (!fifo.empty()){
		u=fifo.front();
		fifo.pop();
		for (edgeVector::const_iterator it=lNet[u].begin();it!=lNet[u].end(); ++it)
		{
			size_t v=it->to;
			if (!vertices[v].first)
			{ 
				fifo.push(v);
				vertices[v].second=vertices[u].second+1; 
				if (v==target_) find=true;
			}
		}		
		if (find) break;
		vertices[u].first=true;		
	}
	return find;
}

MaximumFlow::edgeVector::iterator MaximumFlow::findEdge(size_t u,size_t v, flow_network &lNet)
{
	edgeVector::iterator it=lNet[u].begin();
	edgeVector::iterator end=lNet[u].end();
	
	while (it!=end)
	{
		if (it->to==v) break;
			++it;
	}
	return it;
}