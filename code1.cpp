#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const long long MAX = 1e9+10;
int main(){
    int n,m,s; cin >>n>>m>>s;
    vector<int> dist(n+1,MAX);
    vector<vector<pair<int,int>>> g(n+1);
    for(int i = 1; i <= m; i++) {
        int u,v,w; cin >> u >> v >> w;
        g[u].push_back({v,w});
    }       
    dist[s]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
     pq.push({0,s});
    while(!pq.empty()){
        auto [d,u] = pq.top();
        pq.pop();
        if(d>dist[u]) continue;
        for(auto [v,w]:g[u]){
            if(dist[v]>dist[u]+w){
                dist[v] = dist[u]+w;
                pq.push({dist[v],v});
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        if(i!=1) cout << " ";
        cout << dist[i];
    }
    return 0;
}