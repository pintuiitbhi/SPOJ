/*Segmented sieve Eratosthenes
To print prime numbers between l and r when size of array exceeds
10^8 as in the case with Simple sieve of Eratosthenes*/

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define MAX 100001

vector<ll>* sieve(){
bool isPrime[MAX];

  memset(isPrime,true,sizeof(isPrime));

  for(ll i=2;i*i<MAX;i++){
    if(isPrime[i]){
      for(ll j=i*i; j<MAX;j+=i){
        isPrime[j] = false;
      }
    }
  }

  vector<ll>* primes = new vector<ll>();
  primes->push_back(2);
  for(ll i=3;i<MAX;i+=2){
    if(isPrime[i]){
      primes->push_back(i);
    }
  }
  return primes;
}

void printPrimes(ll l,ll r, vector<ll>* &primes){
  bool isPrime[r-l+1];
  memset(isPrime,true,sizeof(isPrime));

  for(ll i=0;primes->at(i)*primes->at(i) <=r;i++){
    ll currPrime = primes->at(i);
    ll base = (l/currPrime)*currPrime;
    if(base<l){
      base+=currPrime;
    }
    for(ll j=base;j<=r;j+=currPrime){
      isPrime[j-l]=false;
    }
    if(base==currPrime){
      isPrime[base-l] = true;
    }
  }

  for(ll i=0; i<=r-l;i++){
    if(isPrime[i]== true){
      if(i+l!=1)
        cout<< i+l<< endl;
    }
  }
}

int main(){
ios_base:: sync_with_stdio(false);
cin.tie(NULL);

vector<ll>* primes = sieve();
ll t,l=0,r=0;
cin>>t;

while(t--){
  cin>>l>>r;
  printPrimes(l,r,primes);
  cout<<endl;
}
  return 0;
}
