#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int N = 100230;
int n,m,op,com_num,map_comp[N],in_deg[N],out_deg[N],w=0,p,C=0;
bool is_sink_present;

map<int,vector<int>>Containers;

set<array<int,2>>edge_set_1, edge_set_2, edge_set_0;
set<array<int,2>>con_edges;
set<int>s1,s2;

vector<int>g[N],g1[N],condensation[N],condensation_1[N],sources,ordered_src,sinks,ordered_sink,iso,visited_src,visited_sink;

void dfs_list(int u,vector<bool>&visited,list<int>&s)
{
	visited[u] = 1;
	for (auto v: g[u]) 
	{
		if (!visited[v]) 
		{
			edge_set_1.insert({u, v});
			dfs_list(v,visited,s);
		}
	}
	s.push_back(u);
}

void dfs_map(int u,vector<bool> &visited,int com_num)
{
	visited[u] = 1;
	map_comp[u] = com_num;
	Containers[com_num].push_back(u);
	for (auto x: g1[u])
	{
		if (!visited[x]) 
		{
			edge_set_2.insert({u, x});
			dfs_map(x, visited, com_num);
		}
	}
}

void dfs(int u, vector<bool> &visited)
{
	visited[u] = 1;
	in_deg[u] = 1;
	for (int v: g[u])
	{
		if (!visited[v]) 
		{
			out_deg[u] = 1;
			dfs(v, visited);
		}
	}
}

void search(int x) 
{
	if (!visited_src[x]) 
	{
		if (condensation[x].size() == 0)
		{
			w = x;
			is_sink_present = 0;
		}	

		visited_src[x] = 1;

		for (auto y: condensation[x]) 
		{
			if (is_sink_present) 
				search(y);
		}

	}
}

void find_scc()
{
	list<int> s;
	vector<bool>visited(n, 0);
	for (int i = 0;i<n;i++) 
	{
		if (!visited[i]) 
			dfs_list(i, visited, s);
		
	}

	vector<int>g1[n];

	for (int i=0;i<n;i++)
	{
		for (int j = 0;j<g[i].size();j++)
			g1[g[i][j]].push_back(i);
	}

	vector<bool> vis1(n, 0);
	com_num = 0;
	for (auto it=s.rbegin();it!=s.rend();it++) 
	{
		if (!vis1[*it]) 
		{
			com_num++;
			dfs_map(*it, vis1, com_num);
		}
	}

}

void condense() 
{
	for (auto x: edge_set_0)
	{
		if (map_comp[x[0]] != map_comp[x[1]])
		{
			if (con_edges.find({map_comp[x[0]], map_comp[x[1]]}) == con_edges.end()) 
			{
				
				condensation[map_comp[x[0]]].push_back(map_comp[x[1]]);
				condensation_1[map_comp[x[1]]].push_back(map_comp[x[0]]);
				con_edges.insert({map_comp[x[0]], map_comp[x[1]]});
			}
		}  
	}
}



void find_minimum_edges() 
{
	vector<bool> visited(n, false);
	for (int i = 0; i < n; ++i)
	{	if (!visited[i]) 
			dfs(i, visited);
	}

}

int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin>>n>>m>>op;
	int u,v;
	
	for (int i =0;i<m;i++)
	 {
		cin>>u>>v;
		g[u].push_back(v);
		edge_set_0.insert({u, v});
		g1[v].push_back(u);

	} 

	if(op==0) 
	{
		find_scc();
		set<array<int,2>>temp_edge=edge_set_1;
		for (auto x: edge_set_2) 
		{
			if (temp_edge.find({x[1],x[0]})==temp_edge.end()) 
				temp_edge.insert({x[1],x[0]});
		}	

		cout<<temp_edge.size()<<endl;

		for (auto k: temp_edge)
			cout<<k[0]<<" "<<k[1]<<endl;
	}

	if(op==3)
	 {
		find_scc();

		if(com_num==1)
		{	cout<<0<<endl;
		 	goto final;
		}		  

		condense();
		int n = com_num,iso_count = 0;
		
		iso.assign(N, 0);
		visited_src.assign(N,0);
		visited_sink.assign(N,0);
		ordered_src.assign(N,0);
		ordered_sink.assign(N,0);

		for(int i=1;i<=n;i++)
		{
			if (condensation[i].size() == 0 && condensation_1[i].size() == 0) 
				iso[++iso_count]=i;  
			else if (condensation[i].size() == 0) 
				sinks.push_back(i);
			
			else if (condensation_1[i].size() == 0) 
				sources.push_back(i);
			
		}

			

		for(int i=0; i<sources.size();i++) 
		{
			if(!visited_src[sources[i]])
			 {
				int v =sources[i];
				w = 0;
				is_sink_present = 1;
				search(v);

				if(w!= 0) 
				{
					ordered_src[++C] = v; 
					s1.insert(v);
					ordered_sink[C] = w;
					s2.insert(w);
					visited_sink[w] = 1;
				}
			}
		}

		
		int temper =C;

		for(int i=0;i<sources.size();i++) 
		{
			if (s1.find(sources[i]) == s1.end()) 
			{
			
				temper++;
				ordered_src[temper] = sources[i]; 
			}
		}

		temper=C;
		for(int j=0;j<sinks.size();j++) 
		{
			if (s2.find(sinks[j]) == s2.end())
			{
				temper++;
				ordered_sink[temper] = sinks[j];
			}
		}

		int so_size=sources.size(),sk_size=sinks.size();  
		
		set<array<int,2>>s_to_sink_g;

		if(sk_size==0 && so_size==0 && iso_count!=0)
		{
			for (int i=1;i<n;i++) 
			{
				s_to_sink_g.insert({i, i + 1});
			}
			s_to_sink_g.insert({n, 1});
			goto temp_final;
		}


		if(sk_size>=so_size) 
		{
			for(int i=1;i<C;i++) 
				s_to_sink_g.insert({ordered_sink[i],ordered_src[i + 1]});
		
			for(int i=C+1; i<=so_size;i++)
				s_to_sink_g.insert({ordered_sink[i], ordered_src[i]});
		

			if(sk_size==so_size && iso_count==0) 			
				s_to_sink_g.insert({ordered_sink[C], ordered_src[1]});
			
			else if(sk_size>so_size && iso_count==0) 
			{			
				s_to_sink_g.insert({ordered_sink[C], ordered_sink[so_size + 1]});
				for(int i = so_size + 1; i < sk_size; ++i) 			
					s_to_sink_g.insert({ordered_sink[i],ordered_sink[i + 1]});
								
				s_to_sink_g.insert({ordered_sink[sk_size],ordered_src[1]});
			}

			else 
			{
				if (sk_size>so_size) 
					s_to_sink_g.insert({ordered_sink[C], ordered_sink[so_size + 1]});

				for (int i = so_size + 1; i < sk_size; ++i) 		
					s_to_sink_g.insert({ordered_sink[i], ordered_sink[i + 1]});
		
				s_to_sink_g.insert({ordered_sink[sk_size], iso[1]});

				for (int i = 1; i < iso_count; ++i) 				
					s_to_sink_g.insert({iso[i], iso[i + 1]});				
			
				s_to_sink_g.insert({iso[iso_count], ordered_src[1]});
			}

		}

		else
		{
			
			set<array<int,2>>s_to_sink_g1;

			for (int i =1;i<C;i++) 		
				s_to_sink_g1.insert({ordered_src[i],ordered_sink[i+1]});
			
			for (int i = C+1; i<=sk_size;i++) 
				s_to_sink_g1.insert({ordered_src[i],ordered_sink[i]});			

			if (iso_count==0 && sk_size==so_size)	
				s_to_sink_g1.insert({ordered_src[C],ordered_sink[1]});		

			else if (sk_size<so_size && iso_count==0) 
			{				
				s_to_sink_g1.insert({ordered_src[C], ordered_src[sk_size + 1]});

				for (int i = sk_size + 1;i<so_size;i++) 
					s_to_sink_g1.insert({ordered_src[i], ordered_src[i + 1]});
				
				s_to_sink_g1.insert({ordered_src[so_size], ordered_sink[1]});
			}

			else 
			{
				
				if (sk_size<so_size) 
					s_to_sink_g1.insert({ordered_src[C],ordered_src[sk_size + 1]});

				for (int i=sk_size+1;i<so_size;i++)	
					s_to_sink_g1.insert({ordered_src[i],ordered_src[i + 1]});
				
				
				s_to_sink_g1.insert({ordered_src[so_size],iso[1]});

				for (int i=1;i<iso_count;i++)					
					s_to_sink_g1.insert({iso[i],iso[i+1]});
								
				s_to_sink_g1.insert({iso[iso_count],ordered_sink[1]});
			}

			for (auto k:s_to_sink_g1) 
				s_to_sink_g.insert({k[1],k[0]});			

		}
		
		temp_final:
			//hello

		set<array<int,2>> final_g;
		for(auto k: s_to_sink_g) 
			final_g.insert({Containers[k[0]][0],Containers[k[1]][0]});
		

		cout<<final_g.size()<<endl;
		for(auto k: final_g) 
			cout<<k[0]<<" "<<k[1]<<endl;	
		
	}

	final:
		

	return 0;
}

