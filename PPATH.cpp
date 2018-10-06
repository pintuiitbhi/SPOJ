#include <bits/stdc++.h>
using namespace std;


//Prime number Generator
vector<long int> sievePrime(long int n){
    bool prime[n+1];
    memset (prime, true, sizeof(prime));

    for (long int i=2;i*i<=n;i++){
      if(prime[i]==true){
        for(long int j=i*2;j<=n;j=j+i)
        prime[j]=false;
      }
    }

  vector<long int> p;
    for(long int i=2;i<=n;i++){
      if(prime[i])
      p.push_back(i);
    }
    return p;
}

//Create Graph
void addEdge(vector<long int> adj[], long int u, long int v){
  adj[u].push_back(v);
  adj[v].push_back(u);
}

// a modified version of BFS that stores predecessor
// of each vertex in array p
// and its distance from source in array d
bool BFS(vector<long int> adj[], long int src,long  int dest, long int v,
                          long  int pred[],long int dist[])
{
    // a queue to maintain queue of vertices whose
    // adjacency list is to be scanned 
    list<long int> queue;

    // boolean array visited[] which stores the
    // information whether ith vertex is reached
    // at least once in the Breadth first search
    bool visited[v];

    // initially all vertices are unvisited
    // so v[i] for all i is false
    // and as no path is yet constructed
    // dist[i] for all i set to infinity
    for (long int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }

    // now source is first to be visited and
    // distance from source to itself should be 0
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);

    // standard BFS algorithm
    while (!queue.empty()) {
      long  int u = queue.front();
        queue.pop_front();
        for (long int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);

                // We stop BFS when we find
                // destination.
                if (adj[u][i] == dest)
                   return true;
            }
        }
    }

    return false;
}

// utility function to print the shortest distance
// between source vertex and destination vertex
void printShortestDistance(vector<long int> adj[],long int s,
                                  long int dest,long int v)
{
    // predecessor[i] array stores predecessor of
    // i and distance array stores distance of i
    // from s
  long  int pred[v], dist[v];

    if (BFS(adj, s, dest, v, pred, dist) == false)
    {
        // cout << "Given source and destination"
        //      << " are not connected";
        printf("%d\n",0);
        return;
    }

   
    // distance from source is in distance array
    // cout << "Shortest path length is : "
    //     << dist[dest];
    printf("%ld\n",dist[dest]);

}


int main(){
  vector<long int> tmp = sievePrime(9999);

  vector<long int> adj[100000];

  long int test =0,num1=0,num2=0;
  scanf("%ld",&test);

  while(test){
    scanf("%ld %ld",&num1,&num2);
    for(long int i =168;i<tmp.size();i++){
      for(long int j=i+1;j<tmp.size();j++){
        int c=4,t1=tmp[i],t2=tmp[j],d=0;

        while(c){
          int r1= t1%10;
          int r2= t2%10;
          if (r1 !=r2)
            d+=1;
          t1=t1/10;
          t2=t2/10;
            c-=1;
        }
        if(d==1)
        {
          addEdge(adj,tmp[i],tmp[j]);}
        }
    }
    long int source = num1, dest = num2;
    printShortestDistance(adj, source, dest, 100000);
    test-=1;
  }

  return 0;
}
