/*
Dynamic Programming, recursion, and use of map
*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long

map<ll,ll> cache;

ll dp(ll x){
  if(x==0)
    return 0;

  if(cache[x]>0)
    return cache[x];

    cache[x]=max(x,(dp(x/2)+dp(x/3)+dp(x/4)));
    return cache[x];

}

int main(){
  ios_base:: sync_with_stdio(false);
  cin.tie(NULL);

  ll n;

  while(cin>>n){
    cout<<dp(n)<<endl;
  }
  return 0;
}
