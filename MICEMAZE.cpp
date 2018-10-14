#include <bits/stdc++.h>
using namespace std;

# define INF 0x3f3f3f3f

void addEdge(vector < pair<int,int> > adj[],int u, int v, int wt){
  adj[u].push_back(make_pair(v,wt));
  adj[v].push_back(make_pair(u,wt));
}

int dijkstra(vector <pair <int,int> > adj[], int src, int node,long long int timer){
  priority_queue <pair<int, int> , vector< pair< int,int> >, greater<pair<int,int> > > pq;

  vector <long long int> dist(node+1,INF);

  dist[src]=0;
  pq.push(make_pair(dist[src],src));

  while(!pq.empty()){
    pair <int,int> temp = pq.top();
    pq.pop();
    int u=temp.second;

    for(auto x : adj[u]){
      int v=x.first;
      int wt=x.second;
      if(dist[v]>dist[u]+wt){
        dist[v]= dist[u]+wt;
        pq.push(make_pair(dist[v],v));
      }
    }
  }
  int count=0;
  for(int i=1;i<node+1;i++){
    if(dist[i]<=timer)
    count++;
  }
  return count;
}


int main(){
  int N,E,M;
  long long int T;
  scanf("%d",&N);
  scanf("%d",&E);
  scanf("%lld",&T);
  scanf("%d",&M);

  int a,b,t;
  vector < pair <int,int> > adj[N+1];

  for(int i=1;i<=M;i++){
    scanf("%d %d %d",&a,&b,&t);
    addEdge(adj,a,b,t);
  }

  int r=dijkstra(adj, E, N, T);
  printf("%d",r);
  return 0;
}
