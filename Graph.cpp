/* 
===== Tarjan's Algorithm  =====
for finding the strongly connected components (SCCs) of a directed graph
Strongly Connected Components represents a group of nodes that can reach each other through directed paths.
*/
int idTrack = 0;
void dfs(vector<vector<int>>& adj, int a, vector<int>& res, vector<int>& id, vector<bool>& inStack, stack<int>& st) {
    id[a] = res[a] = idTrack++;
    st.push(a);
    inStack[a] = true;

    for (int n : adj[a]) {
        if (id[n] == -1) {
            dfs(adj, n, res, id, inStack, st);
        }

        if (inStack[n]) {
            res[a] = min(res[a], res[n]);
        }
    }

    if (res[a] == id[a]) {
        while (true) {
            int node = st.top();
            st.pop();
            inStack[node] = false;
            res[node] = id[a];
            if (node == a) break;
        }
    }
}

// Adj is Adjecent Vector, and N is total nodes
vector<int> findScc(vector<vector<int>>& adj, int n) {
    vector<int> res(n), id(n, -1);
    vector<bool> inStack(n, false);
    stack<int> st;

    for (int i = 0; i < n; ++i) {
        if (id[i] == -1) dfs(adj, i, res, id, inStack, st);
    }

    return res;
}

/* 
===== Kosaraju's Algorithm  =====
for finding the strongly connected components (SCCs) of a directed graph
Strongly Connected Components represents a group of nodes that can reach each other through directed paths.
*/
class Kosaraju{
    public:
    int id = 1;
    int timer = 0;

    void dfsTime(vector<vector<int>>& adj, vector<pair<int, int>>& time, int a){
        time[a].first = timer; timer++;
        for(auto i : adj[a]) if(time[i].first == -1) dfsTime(adj, time, i);
        time[a].second = timer; timer++;
    }


    void dfsComponent(vector<vector<int>>& rdj, vector<int>& res, int a){
        res[a] = id;
        for(auto i : rdj[a]) if(res[i] == -1) dfsComponent(rdj, res, i);
    }

    vector<int> findScc(vector<vector<int>>& adj, vector<vector<int>>& rdj, int n){
        vector<int> res(n, -1);
        vector<pair<int, int>> time(n, {-1, -1});
        priority_queue<pair<int, int>> pq;
        stack<int> st;

        for(int i = 0 ; i < n ; i++) if(time[i].first == -1) dfsTime(adj, time, i);
        for(int i = 0 ; i < n ; i++) pq.push({time[i].second, i});

        while(!pq.empty()){
            pair<int, int> cur = pq.top();
            pq.pop();

            if(res[cur.second] == -1){
                dfsComponent(rdj, res, cur.second);
                id++;
            }
        }

        return res;
    }
};

/*
===== Disjoint Set =====
Used for union find algorithm
*/
// C++ implementation of disjoint set 

#include <bits/stdc++.h> 
using namespace std; 

class DisjSet { 
	int *rank, *parent, *size, n; 
public: 
	DisjSet(int n) 
	{ 
		rank = new int[n]; 
		parent = new int[n]; 
        size = new int[n];
		this->n = n; 
		makeSet(); 
	} 

	void makeSet() 
	{ 
		for (int i = 0; i < n; i++) parent[i] = i; 
	} 

	int find(int x) { 
		if (parent[x] != x) { 
			parent[x] = find(parent[x]); 
		} 

		return parent[x]; 
	} 

	void unionByRank(int i, int j){ 
		int iset = find(i); 
		int jset = find(j); 
		if (iset == jset) return; 

		if (rank[iset] < rank[jset]) { 
			parent[iset] = jset; 
		} else if (rank[iset] > rank[jset]) { 
			parent[jset] = iset; 
		} else { 
			parent[jset] = iset; 
			rank[iset] = rank[iset] + 1; 
		} 
	} 

    void unionBySize(int i, int j) { 
        int irep = find(i); 
        int jrep = find(j); 
        if (irep == jrep) return; 

        if (size[irep] < size[jrep]) {
            parent[irep] = jrep; 
            size[jrep] += size[irep]; 
        } else {  
            parent[jrep] = irep; 
            size[irep] += size[jrep]; 
        } 
    }
}; 


/*
===== Dijkstra Algorithm =====
V is total vertex, adj list, and S is start index (0-indexed)
*/
vector<long long> dijkstra(int V, vector<vector<pair<int, long long>>>& adj, int S) {
    vector<long long> result(V, INT_MAX);
    result[S] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, S});
    
    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();
        
        if (current_dist > result[u]) continue;

        for (auto [v, weight] : adj[u]) {
            long long new_dist = current_dist + weight;
            if (new_dist < result[v]) {
                result[v] = new_dist;
                pq.push({new_dist, v});
            }
        }
    }
    
    return result;
}

/*
===== Floyd Warshall Algorithm =====
V is total vertex, shortest path from all to all
*/
vector<vector<int>> floydWarshall(int V, vector<vector<pair<int, int>>>& adj) {
    vector<vector<int>> distance(V, vector<int>(V, INT_MAX));

    for (int u = 0; u < V; ++u) {
        distance[u][u] = 0;
        for (auto& neighbor : adj[u]) {
            int v = neighbor.first;
            if(v== u) continue;
            int weight = neighbor.second;
            distance[u][v] = weight;
        }
    }

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (distance[i][k] != INT_MAX && distance[k][j] != INT_MAX &&
                    distance[i][k] + distance[k][j] < distance[i][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }

    return distance;
}

/*
===== Bellman Ford =====
V is total vertex, S is start index, shortest past from s with negative path
*/
vector<int> bellmanFord(int V, vector<vector<pair<int, int>>>& adj, int S) {
    vector<int> distance(V, INT_MAX);
    distance[S] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (int u = 0; u < V; ++u) {
            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                }
            }
        }
    }

    for (int u = 0; u < V; ++u) {
        for (auto& neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                for(int& i : distance) i = -1;
                return distance;
            }
        }
    }

    return distance;
}


/*
===== Prim's Algorithm =====
V is total vertex, adj list, used for minimum spanning tree
*/
int prim(int V, vector<vector<pair<int, int>>>& adj){
    priority_queue<pair<int, int>> pq;
    vector<bool> explored(V, false);
    int result{};
    pq.push({0, 0});

    while(!pq.empty()){
        pair<int, int> cur = pq.top();
        pq.pop();
        if(explored[cur.second]) continue;
        explored[cur.second] = true;
        result -= cur.first;

        for(auto i : adj[cur.second]){
            if(!explored[i.first]){
                pq.push({-1*i.second, i.first});
            }
        }
    }

    return result;
}

/*
===== Kruskal's Algorithm =====
V is total vertex, edges is edge list consist of {weight, {source, destination}}
used for minimum spanning tree
*/
int findParent(vector<int>& parent, int i) { 
    if (parent[i] == i) return i;
    else {  
        int result = findParent(parent, parent[i]); 
        parent[i] = result; 
        return result; 
    } 
}

void unionSet(vector<int>& parent, int i, int j) { 
    int irep = findParent(parent, i);
    int jrep = findParent(parent, j); 
    if(jrep != irep) parent[irep] = jrep; 
}

int kruskal(int V, vector<pair<int, pair<int, int>>>& edges) {
    vector<int> parent(V, -1);
    int minCost = 0;

    for (const auto& edge : edges) {
        int weight = edge.first;
        int src = edge.second.first;
        int dest = edge.second.second;

        int x = findParent(parent, src);
        int y = findParent(parent, dest);

        if (x != y) {
            minCost += weight;
            unionSet(parent, x, y);
        }
    }

    return minCost;
}

/*
===== Graph Coloring =====
V is total vertex, adj list
*/
vector<int> graphColoring(int V, vector<vector<int>>& adj, int maxColor) {
    vector<int> result(V, -1);
    result[0] = 0;
    vector<bool> available(maxColor, true);

    for (int u = 1; u < V; u++) {
        fill(available.begin(), available.end(), true);
        for (int i : adj[u]) {
            if (result[i] != -1) {
                available[result[i]] = false;
            }
        }

        for(int i = 0 ; i < maxColor ; i++){
            if (available[i]) {
                result[u] = i;
                break;
            }
        }
    }

    return result;
}

/*
===== Shorterst Path using BFS =====
V is total vertex, adj list
*/
vector<int> shortestPathBFS(int V, vector<vector<int>> adj){
    vector<int> dis(V, -1);
    queue<int> q;
    dis[0] = 0;
    q.push(0);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (int neighbor : adj[cur]) {
            if (dis[neighbor] == -1) { 
                dis[neighbor] = dis[cur] + 1;
                q.push(neighbor);
            }
        }
    }

    return dis;
}