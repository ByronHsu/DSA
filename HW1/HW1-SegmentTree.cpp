#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int n,m,arr[100010],seg[2000000];
int constructSegTree(int ss,int se,int index){
	if(ss==se){
		seg[index]=arr[ss];
		return seg[index];
	}
	int mid=(ss+se)/2;
	seg[index]=max(constructSegTree(ss,mid,2*index+1),
		constructSegTree(mid+1,se,2*index+2));
	return seg[index];
}
int querySegTree(int ss,int se,int qs,int qe,int index){
	if(qs<=ss&&qe>=se){
		return seg[index];
	}
	if(qs>se||qe<ss){
		return -1;
	}
	else{
		int mid=(ss+se)/2;
		return max((querySegTree(ss,mid,qs,qe,2*index+1)),
			(querySegTree(mid+1,se,qs,qe,2*index+2)));
	}
}
int main(){
	//freopen("output.txt", "w", stdout);
	//freopen("input.txt", "r", stdin);
	scanf("%d%d", &n,&m);
	for(int i=0;i<n;i++){
		scanf("%d", &arr[i]);
	}
	constructSegTree(0,n-1,0);
	for(int i=0;i<m;i++){
		int t1,t2;
		scanf("%d%d", &t1,&t2);
		printf("%d\n",querySegTree(0,n-1,t1-1,t2-1,0));
	}
}