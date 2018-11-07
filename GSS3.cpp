#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 0x3f3f

struct Node {
    ll maxPrefixSum;
    ll maxSuffixSum;
    ll totalSum;
    ll maxSubarraySum;

    Node(){
      maxPrefixSum = maxSuffixSum = maxSubarraySum = -inf;
      totalSum = -inf;
    }
};

Node merge(Node leftChild , Node rightChild){
  Node parentNode;

  parentNode.maxPrefixSum=max(leftChild.maxPrefixSum,
                              leftChild.totalSum+rightChild.maxPrefixSum);
  parentNode.maxSuffixSum=max(rightChild.maxSuffixSum,
                            rightChild.totalSum+leftChild.maxSuffixSum);
  parentNode.totalSum=leftChild.totalSum + rightChild.totalSum;
  parentNode.maxSubarraySum = max({leftChild.maxSubarraySum,
                                  rightChild.maxSubarraySum,
                                leftChild.maxSuffixSum + rightChild.maxPrefixSum});

  return parentNode;
}

//Builds the segment tree recursively
void constructTreeUtil(Node* tree, ll arr[], ll start, ll end, ll index){
  //Leaf Node
  if (start == end) {
    //single element is covered under this range
    tree[index].totalSum = arr[start];
    tree[index].maxSuffixSum = arr[start];
    tree[index].maxPrefixSum = arr[start];
    tree[index].maxSubarraySum=arr[start];
    return;
  }

  //Recursively build left and right children
  int mid = (start + end)/2;
  constructTreeUtil(tree, arr, start, mid, 2* index);
  constructTreeUtil(tree, arr, mid+1, end, 2* index+1);

  //Merge left and right child into Parent Node
  tree[index] = merge(tree[2* index],tree[2* index +1]);
}

/*Function to construct segment tree from given array.
This function allocates memory for segment tree and
calls constructTreeUtil() to fill the allocated
memory*/

Node* constructTree(ll arr[], ll n){
  //Allocate memory for segment tree
  ll x = (ll) (ceil(log2(n)));
  //Maximum size of segment tree
  ll max_size = 2 * (ll)pow(2,x)-1;
  // ll max_size=2*n;
  Node* tree = new Node[max_size];

  //Fill the allocated memory tree
  constructTreeUtil(tree, arr, 0,n-1,1);
  return tree;
}

/* A Recursive function to get the desired
   Maximum Sum Sub-Array,
The following are parameters of the function-

tree     --> Pointer to segment tree
index --> Index of the segment tree Node
ss & se  --> Starting and ending indexes of the
             segment represented by
                 current Node, i.e., tree[index]
qs & qe  --> Starting and ending indexes of query range */

Node queryUtil(Node* tree, ll ss,ll se, ll qs,
                                    ll qe, ll index){

  //No overlap
    if(ss > qe || se < qs){
      //returns a Node for out of bounds condition
      Node nullNode;
      return nullNode;
    }

  //Complete overlap
  if(ss >= qs && se <= qe){
    return tree[index];
  }

  // Partial Overlap Merge results of Left
  // and Right subtrees
  ll mid = (ss+se)/2;
  Node left = queryUtil(tree, ss, mid, qs, qe,
                            2*index);
  Node right = queryUtil(tree, mid+1,se,qs,qe,2*index+1);

  // merge left and right subtree query results
  Node res = merge(left, right);
  return res;

}

ll query(Node* tree, ll start, ll end, ll n){
  Node res = queryUtil(tree, 0, n-1, start, end, 1);
  return res.maxSubarraySum;
}


//Update the Array
void update(Node* tree, ll arr[], ll start, ll end, ll idx, ll val,ll index){
  if(start==end){
    tree[index].maxPrefixSum=tree[index].maxSuffixSum=tree[index].maxSubarraySum =tree[index].totalSum=val;
    arr[idx]=val  ;
    return;
  }

  else{
  ll mid = (start+end)/2;
  if(idx<=mid)
    update(tree,arr, start,mid,idx,val,2*index);
  else
    update(tree,arr,mid+1,end,idx,val,2*index+1);
  tree[index] = merge(tree[2* index],tree[2* index +1]);
  return;
}
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  ll N,M,q,x,y,maxSubarraySum;
  cin>>N;

  ll arr[N],temp=0;

  for(ll i=0;i<N;i++){
    cin>>temp;
    arr[i]=temp;
  }

  Node* Tree = constructTree(arr,N);
  // for(ll i=1;i<=2*N;i++){
  //   cout<<Tree[i].maxSubarraySum<<endl;
  // }

  cin>>M;

  for(ll i=0;i<M;i++){
    cin>>q>>x>>y;

    if(q==1){
      maxSubarraySum=query(Tree,x-1,y-1,N);
      cout<<maxSubarraySum<<endl;	}
		else{
			update(Tree,arr,0,N-1,x-1,y,1);
		}


  }
  return 0;
}
