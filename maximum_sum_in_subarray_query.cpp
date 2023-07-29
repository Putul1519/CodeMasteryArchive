/*Segment Tree Approach of maximum sun in suarray for query*/

#include<bits/stdc++.h>
using namespace std;

struct Node{
    int maxPS;
    int maxSS;
    int TS;
    int maxSum;

    Node(){
        maxPS=maxSS=TS=maxSum=-99;
    }
};

Node merge(Node left,Node right)
{
    Node parent;
    parent.maxPS=max(left.maxPS,left.TS+right.maxPS);
    parent.maxSS=max(right.maxSS,right.TS+left.maxSS);
    parent.TS=left.TS+right.TS;
    parent.maxSum=max({left.maxSum,right.maxSum,left.maxSS+right.maxPS});
    return parent;
}

void constructTreeUtil(Node* tree,vector<int>& arr,int start,int end,int index)
{
    if(start==end)
    {
        tree[index].maxPS=arr[start];
        tree[index].maxSS=arr[start];
        tree[index].maxSum=arr[start];
        tree[index].TS=arr[start];
        return;
    }
    int mid=(start+end)/2;
    constructTreeUtil(tree,arr,start,mid,2*index);
    constructTreeUtil(tree,arr,mid+1,end,2*index+1);
    tree[index]=merge(tree[2*index],tree[2*index+1]);

}

Node* constructTree(vector<int>& arr,int n)
{
    int x=(int)(ceil(log2(n)));
    int max_size=2*(int)pow(2,x)-1;
    Node* tree=new Node[max_size];
    constructTreeUtil(tree,arr,0,n-1,1);
    return tree;
}

Node queryUtil(Node* tree,int ss,int se,int qs,int qe,int index)
{
    if(ss>qe || se<qs)
    {
        Node nullnode;
        return nullnode;
    }
    if(ss>=qs&&se<=qe)
    {
        return tree[index];
    }
    int mid=(ss+se)/2;

    Node left=queryUtil(tree,ss,mid,qs,qe,2*index);
    Node right=queryUtil(tree,mid+1,se,qs,qe,2*index+1);
    Node res=merge(left,right);
    return res;
}

int query(Node* tree,int start,int end,int n)
{
    Node res=queryUtil(tree,0,n-1,start,end,1);
    return res.maxSum;
}

int main()
{
    int n;
    cout<<"Enter Size:";
    cin>>n;
    vector<int> arr(n);
    cout<<"Enter array element:\n";

    for(int i=0;i<n;i++) cin>>arr[i];

    Node* tree=constructTree(arr,n);

    int q=0;
    cout<<"Enter size of query:";
    cin>>q;
    while(q--)
    {
        int start,end;
        cin>>start>>end;
        int ans=query(tree,start,end,n);
        cout<<ans<<"\n";
       
    }
     return 0;
}