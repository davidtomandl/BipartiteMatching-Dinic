#include "MaximumFlow.hpp"

void MaximumFlow::addEdge(size_t from, size_t to, double capacity){
	net_[from].push_back(Edge(to,capacity,0));
};


MaximumFlow::flow_network MaximumFlow::Dinic(){
	size_t l=0;
	flow_network R=net_;
	while (true)
	{
		R=net_;
		residualNetwork(R);
		if (!shortestPath(l,R)) break;
		layeredNetwork(R);
		blockingFlow(R);
		
	}
	return net_;
}
void MaximumFlow::blockingFlow(flow_network & fNet)
{
	std::vector<size_t> path;
	init(fNet,path);
}
void MaximumFlow::init(flow_network& fNet,std::vector<size_t>& path)
{
	path.clear();
	path.push_back(source_);
	forward(fNet,path);
}

void MaximumFlow::forward(flow_network& fNet,std::vector<size_t>& path)
{
	size_t x=path.back();
	if (fNet[x].size()==0) 
		backward(fNet,path);
	else
	{
		size_t y=fNet[x][0].to;
		path.push_back(y);
		x=y;
		if (y!=target_) forward(fNet,path);
		else increase(fNet,path);
	}
}

void MaximumFlow::backward(flow_network& fNet,std::vector<size_t>& path)
{
	size_t x=path.back();
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
		forward(fNet,path);
	}
}

void MaximumFlow::increase(flow_network &fNet,std::vector<size_t>& path)
{
	double d=INT_MAX;
	size_t x,y;
	size_t size=path.size();
	//residual capacity; d is minimum on the path
	for (size_t i = 1; i < size; i++)
	{
		x=path[i-1];
		y=path[i];
		edgeVector::iterator it=findEdge(x,y,fNet/*net_*/);
		if (it->flow<d) d=it->flow;
	}
	for (size_t i = 1; i < size;i++)
	{
		x=path[i-1];
		y=path[i];		
		edgeVector::iterator it1=findEdge(x,y,fNet);
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
			if (fNet[x].size()==1) 
				fNet[x].clear();
			else
			{
				//edgeVector::iterator it=findEdge(x,y,fNet);
				if (it1!=fNet[x].end())
					fNet[x].erase(it1);
			}
		}
	}
	init(fNet,path);
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
void MaximumFlow::residualNetwork(flow_network& fNet)
{
	size_t i=0;
	for (flow_network::const_iterator it=net_.begin();it!=net_.end(); ++it)
	{
		size_t j=0;
		size_t k=0;
		if (net_[i].size()>0)
		{
			const edgeVector copyVector = net_[i];
			for (edgeVector::const_iterator it=copyVector.begin();it!=copyVector.end(); ++it)
			{
				double f=net_[i][j].flow;
				double c=net_[i][j].capacity;
				size_t v=net_[i][j].to;				
				if (fNet[i].size()>k)
					fNet[i][k].flow=c-f;
				else
					fNet[i].push_back(Edge(v,c,c-f));
				
				if (f>0) 									
					fNet[v].push_back(Edge(i,c,f));				
				if (c==f)
				{
					if (fNet[i].size()==1) 
						fNet[i].clear();
					else
					{
						edgeVector::iterator it=findEdge(i,v,fNet);
						if (it!=fNet[i].end())
							fNet[i].erase(it);
					}
					k--;
				}
				k++;		
				j++;
			}
		}
		i++;
	}


}
void MaximumFlow::layeredNetwork(flow_network& fNet)
{
	std::queue<size_t> fifo; 
	std::vector<short> color;//each vertex has color:0-unused,1-processing,2-used
	std::vector<size_t> layer; 	
	//sets all vetices to unused
	std::for_each(fNet.cbegin(), fNet.cend(), [&color](const edgeVector&){color.push_back(false);});
	layer.resize(color.size());
	fifo.push(source_);
	size_t u; //temp: vertex
	bool find=false;
	while (!fifo.empty()){
		u=fifo.front();
		fifo.pop();
		const edgeVector copyVector = fNet[u];
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
					if (fNet[u].size()==1) 
						fNet[u].clear();
					else
						fNet[u].erase(findEdge(u,v,fNet));
			}
		}		
		color[u]=2;		
	}
	
	size_t i=0;
	//remove unreachable vertices
	for (flow_network::const_iterator it=fNet.begin();it!=fNet.end(); ++it)
	{
		if (color[i]==0)
		{
			fNet[i].clear();
		}
		i++;
	}
}

bool MaximumFlow::shortestPath(size_t &length,flow_network& fNet)
{
	std::queue<size_t> fifo; 
	typedef std::pair <bool,size_t> vertex;//used;distance
	std::vector<vertex> vertices; 
	//for each vertex do:  unused, distance=0
	std::for_each(fNet.cbegin(), fNet.cend(), [&vertices](const edgeVector&){vertices.push_back(vertex(false,0));});

	fifo.push(source_);
	size_t u; //vertex
	bool find=false;
		
	while (!fifo.empty()){
		u=fifo.front();
		fifo.pop();
		for (edgeVector::const_iterator it=fNet[u].begin();it!=fNet[u].end(); ++it)
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
	length=vertices[target_].second;
	return find;
}

MaximumFlow::edgeVector::iterator MaximumFlow::findEdge(size_t u,size_t v, flow_network &fNet)
{
	edgeVector::iterator it=fNet[u].begin();
	edgeVector::iterator end=fNet[u].end();
	
	while (it!=end)
	{
		if (it->to==v) break;
			++it;
	}
	return it;
}

void MaximumFlow::setNetwork(double const* const* capacity){	
	for (size_t i = 0; i < n_vertices_; i++)
        for (size_t j = 0; j < n_vertices_; j++)
            if (capacity[i][j] != 0)
                addEdge(i, j, capacity[i][j]);
}
