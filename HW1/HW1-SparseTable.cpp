#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int n,m,arr[100010],lookup[100000][17];
void constructLookUp(){
	for(int i=0;i<n;i++)
		lookup[i][0]=arr[i];
	for(int j=1;j<=17;j++){
		for(int i=0;i<n;i++){
			if(i+(1<<j)-1>=n)
				break;
			lookup[i][j]=max(lookup[i][j-1],lookup[i+(1<<(j-1))][j-1]);
		}
	}
}
int queryLookUp(int L,int R){
	int dis=R-L+1;
	int index=17;
	for(;index>=0;index--){
		if((1<<(index))<dis)
			break;
	}
	return max(lookup[L][index],lookup[R-(1<<(index))+1][index]);
}
int main(){
	//freopen("output.txt", "w", stdout);
	//freopen("input.txt", "r", stdin);
	scanf("%d%d", &n,&m);
	for(int i=0;i<n;i++){
		scanf("%d", &arr[i]);
	}
	constructLookUp();
	for(int i=0;i<m;i++){
		int t1,t2;
		scanf("%d%d", &t1,&t2);
		printf("%d\n",queryLookUp(t1-1,t2-1));
	}
}