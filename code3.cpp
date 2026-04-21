#include<iostream>
#include<queue>
#include<vector>
#include<climits>
using namespace std;
typedef long long ll;
const ll INF = INT_MAX;
int main(){
    int n,m,s; cin >> n >> m >> s;
    vector<ll> dist(n+1,INF);
    vector<vector<pair<int,int>>> g(n+1);
    for(int i = 1; i<= m; i++){
        int u,v,w; cin >> u >> v >> w;
        g[u].push_back({u,w});
    }
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
    dist[s]=0;
    pq.push({0,s});
    while(!pq.empty()){
        auto [d,u] = pq.top();
        pq.pop();
        if(d>dist[u]) continue;
        for(auto [v,w]:g[u]){
            if(dist[v]>dist[u]+w){
                dist[v] = dist[u]+w;
                pq.push({dist[u],u});
            }
        }
    }
    for(int i = 1;i  <= n; i++){
        if(i!=1) cout << " ";
        cout << dist[i];
    }
    return 0;
}