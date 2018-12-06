#include<bits/stdc++.h>
using namespace std;
#define ll long long

int possibility(ll k, vector<ll> positions,ll N,ll C){
  ll count=1,current=positions[0],distance=0;

  for(ll i=1; i<N;i++){
    distance = positions[i]-current;
    if(distance >=k){
      count+=1;
      current=positions[i];
      // distance=0;
      if(count==C){
        return 1;
      }
    }
    cout<<"check1"<<endl;
  }
    return 0;
}


int main(){
  ios_base:: sync_with_stdio(false);
  cin.tie(NULL);

  ll t,N,C,temp;
  vector <ll> positions;

  cin>>t;

  while(t){
    cin>> N >> C;
    positions.clear();
    // stack <ll> minK;
    for(ll i= 0;i<N;i++){
      cin>>temp;
      positions.push_back(temp);
    }

    sort(positions.begin(),positions.end());
    // for(auto x : positions){
    //   cout<< x << " ";
    // }
    ll low=0,k=0,max=-1;
    ll high = positions[N-1];

    while(low<high){
      cout<<"check2"<<endl;
      k=(low+high)/2;
      // cout<<k<<endl;
      if(possibility(k,positions,N,C)){
        if(k>max)
          max=k;
        low=k+1;
      }
      else{
        // cout<<"Not possible"<<endl;
        high=k;
      }
  }

  // ll res=minK.pop();
  cout<<max<<endl;
    t-=1;
  }

  return 0;
}
