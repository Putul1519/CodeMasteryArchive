/*Lazy Propagation in Segment Tree: An optimization to make range update faster.*/

#include<bits/stdc++.h>
using namespace std;
void buildTree(int* arr,int* tree,int treeInd,int s,int e)
{
    if(s==e)
    {
        tree[treeInd]=arr[s];
        return;
    }
    int mid=(s+e)/2;
    buildTree(arr,tree,2*treeInd,s,mid);
    buildTree(arr,tree,2*treeInd+1,mid+1,e);
    tree[treeInd]=min(tree[2*treeInd],tree[2*treeInd+1]);
}
void updateSegmentTreeLazy(int *tree,int *lazy,int low,int high,int startR,int endR,int currPos,int inc)
{
    if(low>high)
    return;

    if(lazy[currPos]!=0)
    {
        tree[currPos]+=lazy[currPos];
        if(low!=high)  // not a child node
        {
            lazy[2*currPos]+=lazy[currPos];
            lazy[2*currPos+1]+=lazy[currPos];
        }
        lazy[currPos]=0;
    }

    /*No Overlap*/
    if(startR>high||endR<low)
    return;

    /*Complete Overlap*/
    if(startR<=low&&high<=endR)
    {
        tree[currPos]+=inc;
        if(low!=high){
            lazy[2*currPos]+=inc;
            lazy[2*currPos+1]+=inc;
        }
        return;
    }
    /*Partial Overlap*/

    int mid=(low+high)/2;
    updateSegmentTreeLazy(tree,lazy,low,mid,startR,endR,2*currPos,inc);
    updateSegmentTreeLazy(tree,lazy,mid+1,high,startR,endR,2*currPos+1,inc);
    tree[currPos]=min(tree[2*currPos],tree[2*currPos+1]);
}
int query(int* tree,int* lazy,int low,int high,int startR,int endR,int currPos)
{
    if(low>high)
    return INT_MAX;

     if(lazy[currPos]!=0)
    {
        tree[currPos]+=lazy[currPos];
        if(low!=high)  // not a child node
        {
            lazy[2*currPos]+=lazy[currPos];
            lazy[2*currPos+1]+=lazy[currPos];
        }
        lazy[currPos]=0;
    }
    /*No overlap*/
   if(startR>high||endR<low)
    {
        return INT_MAX;
    }

    /*Complete Overlap*/
    if(startR<=low&&high<=endR)
    {
        return tree[currPos];   
    }
    
    /*Partial Overlap*/
    int ans=INT_MAX;
    int mid=(low+high)/2;
    ans=min(ans,query(tree,lazy,low,mid,startR,endR,2*currPos));
    ans=min(ans,query(tree,lazy,mid+1,high,startR,endR,2*currPos+1));
    return ans;
}

int main()
{
    int arr[]={1,3,-2,4};
    int *tree=new int[12];
    buildTree(arr,tree,1,0,3);

    int *lazy=new int[12]();
    updateSegmentTreeLazy(tree,lazy,0,3,0,3,1,3);
    updateSegmentTreeLazy(tree,lazy,0,3,0,1,1,2);
    cout<<"Tree is:"<<"\n";
    for(int i=1;i<12;i++)
    cout<<tree[i]<<" ";
    cout<<endl;

    cout<<"Lazy tree is:"<<"\n";
    for(int i=1;i<12;i++)
    cout<<lazy[i]<<" ";
    cout<<endl;

    int x=query(tree,lazy,0,3,0,0,1);
    cout<<x<<"\n";
    return 0;
}