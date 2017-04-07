#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
#include <ctime>
#include <bitset>
using namespace std;
unsigned long long nextMap(unsigned long long map, int action);
unsigned long long bitMap(int[]);
void arrayMap(unsigned long long,int[]);
bool dfs(unsigned long long);
vector<int> path;
int ansmap[16];
int main(){
    int N;
    cin>>N;
    for(int i=0;i<N;i++){
        for(int j=0;j<16;j++)
            ansmap[j]=-1;
        int arMap[16];
        path.clear();
        unsigned long long btMap;
        for(int j=0;j<16;j++){
            scanf("%d",&arMap[j]);
        }
        btMap = bitMap(arMap);
        if(dfs(btMap)){
            printf("Action:\n");
            for(int j=path.size()-1;j>=0;j--){
                if(j==0){cout<<path[j]; break;}
                printf("%d ",path[j]);
            }
            printf("\n");
            printf("Final:\n");
            for(int j=0;j<16;j++){
                printf("%d",ansmap[j]);
                if(j%4==3)
                    printf("\n");
                else
                    printf(" ");
            }
        }
        else{
            printf("Action:\n-1\n");
            printf("Final:\n");
            for(int j=0;j<16;j++){
                printf("%d",ansmap[j]);
                if(j%4==3)
                    printf("\n");
                else
                    printf(" ");
            }
 
        }
 
    }
}
bool dfs(unsigned long long nowbitmap){
    int nowarmap[16];
    arrayMap(nowbitmap,nowarmap);
    for(int i=0;i<16;i++)
        if(nowarmap[i]==2048){
            for(int j=0;j<16;j++)
                ansmap[j]=nowarmap[j];
            return true;
        }
    for(int i=0;i<4;i++){
        unsigned long long nextbitmap = nextMap(nowbitmap,i);
        if(nextbitmap == nowbitmap)
            continue;
        if(dfs(nextbitmap)){
            path.push_back(i);
            return true;
        }
    }
    return false;
}
unsigned long long bitMap(int array[]){
    unsigned long long tem=0,muti=1;
    for(int i=0;i<16;i++){
        if(array[i]==0)
            tem+=0;
        else
            tem+=(unsigned long long)(log2(array[i]))*muti;
        muti*=16;
    }
    return tem;
}
void arrayMap(unsigned long long bit,int tem[]){
    for(int i=0;i<16;i++){
        if(bit%16==0)
            tem[i]=0;
        else
            tem[i]=pow(2,bit%16);
        bit/=16;
    }
}