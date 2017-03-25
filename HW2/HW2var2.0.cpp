#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <ctime>
using namespace std;
//./a.out /tmp2/dsa2017_hw02/ < input0100.txt
struct doctree{
	vector< vector<int> > pos;
	doctree() : pos(5){}
};
vector< unordered_map<string, doctree> > wordmap(6);
vector< long long int > frequency;
vector< string > sentence;
vector< string > query;
vector< vector <string> > expand;
vector< int > ans;
int GRAMEND[6]={0};

void Get_data(string);
void Query_expand();
bool QM_expand(int);
bool CM_expand(int);
bool SM_expand(int);
void Find_ans();
void Ans_Sort(int);
void Print_ans();
bool Ans_cmp(int,int);

int main(int argc, char** argv){
	clock_t t=clock();
	Get_data(argv[1]);
	t=clock()-t;
	//printf ("%f seconds.\n",((float)t)/CLOCKS_PER_SEC);
	t=clock();
	char inputstr[100],ch;
	string merge;
	
	while(scanf("%s%c",inputstr,&ch)!=EOF){
		query.push_back(inputstr);
		merge+=inputstr;
		if(ch=='\n'){
			//讀完一句
			Query_expand();
			Find_ans();
			printf("query: %s\n",merge.c_str());
			Print_ans();
			//initialize
			merge.clear();
			query.clear();
			expand.clear();
			ans.clear();
			continue;
		}
		merge+=" ";
	}
	t=clock()-t;
	//printf ("%f seconds.\n",((float)t)/CLOCKS_PER_SEC);
}
void Print_ans(){
	int asize=ans.size();
	if(asize>5)
		asize=5;
	printf("output: %d\n",asize);
	for(int i=0;i<asize;i++)
		printf("%s\t%lld\n",sentence[ans[i]].c_str(),frequency[ans[i]]);	
}
void Find_ans(){
	for(int i=0;i<expand.size();i++){
		int gram=expand[i].size();
		if(gram<2)
			continue;
		int howmany=0;
		vector< vector<int> > run(5);
		//wordmap[?gram][word].pos[?][]
		bool notexist=0;
		for(int j=0;j<expand[i].size();j++){
			if(expand[i][j]!="_"){
				if(!wordmap[gram].count(expand[i][j]))
					{notexist=1;break;}
				run[howmany]=wordmap[gram][expand[i][j]].pos[j];
				if(run[howmany].empty()){
					notexist=1;break;
				}
				howmany++;
			}
		}
		if(notexist)
			continue;
		int minrun,runidx[5]={0};
		if(howmany==0){
			//ex:_ _
			for(int i=GRAMEND[gram-1];i<GRAMEND[gram];i++){
				Ans_Sort(i);
			}
		}
		else{
			while(1){
				minrun=0;
				for(int i=1;i<howmany;i++){
					if(run[i][runidx[i]]<run[minrun][runidx[minrun]])
						minrun=i;
				}
				bool same=1;
				for(int i=0;i<howmany-1;i++){
					if(run[i][runidx[i]]!=run[i+1][runidx[i+1]]){
						same=0;
						break;
					}
				}
				

				if(same){
					bool newans=1;
					for(int i=0;i<ans.size();i++){
						if(run[0][runidx[0]]==ans[i]){
							newans=0;
							break;
						}
					}
					if(newans)
						Ans_Sort(run[0][runidx[0]]);

				}

				if(runidx[minrun]+1>=run[minrun].size())
					break;
				else{
					runidx[minrun]+=1;
				}
			}
		}
	}
}
void Ans_Sort(int stridx){
	int asize=ans.size();

	if(asize==0){
		ans.push_back(stridx);
		return;
	}
	for(int i=0;i<asize;i++){
		if(Ans_cmp(stridx,ans[i])){
			ans.insert(ans.begin()+i,stridx);
			if(ans.size()>5)
				ans.erase(ans.end()-1);
			return;
		}
	}
	if(asize<5){
		ans.push_back(stridx);
	}
}
//idx1>idx2 return true
bool Ans_cmp(int idx1,int idx2){
	if(frequency[idx1]>frequency[idx2])
		return 1;
	if(frequency[idx1]<frequency[idx2])
		return 0;
	if(frequency[idx1]==frequency[idx2]){
		int length1=sentence[idx1].length();
		int length2=sentence[idx2].length(); 
		int length=min(length1,length2);
		for(int i=0;i<length;i++){
			if(sentence[idx1][i]<sentence[idx2][i]){
				return 1;
			}
			if(sentence[idx1][i]>sentence[idx2][i]){
				return 0;
			}
		}
		if(length1>length2)
			return 0;
		if(length1<length2)
			return 1;
	}
}
void Query_expand(){
	expand.push_back(query);
	int size;
	size=expand.size();
	for(int i=0,j=0;i<size;i++){
		if(QM_expand(j)){

		}else{
			j++;
		}
	}
	
	size=expand.size();
	for(int i=0,j=0;i<size;i++){
		if(CM_expand(j)){

		}else{
			j++;
		}
	}

	size=expand.size();
	for(int i=0,j=0;i<size;i++){
		if(SM_expand(j)){

		}else{
			j++;
		}
	}
	//刪除空的和重複的
	if(expand[0].empty())
		expand.erase(expand.begin());

	for(int i=0;i<expand.size();i++){
		for(int j=i+1;j<expand.size();j++){
			if(expand[i].size()==expand[j].size()){
				bool same=1;
				for(int k=0;k<expand[i].size();k++){
					if(expand[i][k]!=expand[j][k]){
						same=0;break;
					}
				}
				if(same){
					expand.erase(expand.begin()+j);
					j--;
				}
			}
		}
	}
/*
	cout<<"expand:"<<endl;
	for(int i=0;i<expand.size();i++){
		for(int j=0;j<expand[i].size();j++){
			cout<<expand[i][j]<<" ";
		}
		cout<<endl;
	}
*/
}
bool QM_expand(int qidx){
	vector<string> nowquery=expand[qidx];
	for(int i=0;i<nowquery.size();i++){
		if(nowquery[i][0]=='?'){
			expand.erase(expand.begin()+qidx);
			//delete all
			vector<string> newquery=nowquery;
			newquery.erase(newquery.begin()+i);
			expand.push_back(newquery);
			//delete ?
			newquery=nowquery;
			newquery[i].erase(newquery[i].begin());
			expand.push_back(newquery);
			int size=expand.size();
			for(int k=0,j=0;k<size;k++){
				if(QM_expand(j)){

				}else{
					j++;
				}
			}
			return 1;
		}
	}
	return 0;
}

bool SM_expand(int qidx){
	vector<string> nowquery=expand[qidx];
	int nowstar=0;
	for(int i=0;i<nowquery.size();i++)
		if(nowquery[i]=="*")
			nowstar++;
	for(int i=0;i<nowquery.size();i++){
		if(nowquery[i][0]=='*'){
			expand.erase(expand.begin()+qidx);
			int restsize=5-nowquery.size()+nowstar;

			vector<string> newquery=nowquery;
			//delete all
			newquery.erase(newquery.begin()+i);
			expand.push_back(newquery);			

			vector<string> nostarquery=newquery;

			for(int j=1;j<=restsize;j++){
				newquery=nostarquery;
				for(int k=1;k<=j;k++)
					newquery.insert(newquery.begin()+i,"_");
				expand.push_back(newquery);
			}

			int size=expand.size();
			for(int k=0,j=0;k<size;k++){
				if(SM_expand(j)){

				}else{
					j++;
				}
			}
			return 1;
		}
	}
	return 0;
}
bool CM_expand(int qidx){
	vector<string> nowquery=expand[qidx];
	for(int i=0;i<nowquery.size();i++){
		for(int j=0;j<nowquery[i].size();j++){
			if(nowquery[i][j]=='/'){
				expand.erase(expand.begin()+qidx);
				vector<string> newquery;
				stringstream ss(nowquery[i]);
				string sub_str;
				while(getline(ss,sub_str,'/')){
					newquery=nowquery;
					newquery[i]=sub_str;
					expand.push_back(newquery);
				}
				int size=expand.size();
				for(int k=0,j=0;k<size;k++){
					if(CM_expand(j)){

					}else{
						j++;
					}
				}
				return 1;
			}
		}
	}
	return 0;
}


void Get_data(string path){
	clock_t t=clock();
	string filename[4]={"2gm.small.txt","3gm.small.txt","4gm.small.txt","5gm.small.txt"};
	char inputstr[100];
	long long int inputfre;
	int nowdocid=0;
	string merge;
	for(int i=2;i<=5;i++){
		string tmp = path + filename[i-2];
		//cout<<tmp<<endl;
		FILE *fin;
		fin=fopen(tmp.c_str(),"rt");
		while(fscanf(fin, "%s", inputstr)!=EOF) {
			merge+=inputstr;
			merge+=" ";
			wordmap[i][inputstr].pos[0].push_back(nowdocid);
			for(int j = 1; j < i; j++) {
				fscanf(fin, "%s", inputstr);
				merge+=inputstr;
				if(j!=i-1)
					merge+=" ";
				wordmap[i][inputstr].pos[j].push_back(nowdocid);
			}
			fscanf(fin, "%lld", &inputfre);
			frequency.push_back(inputfre);
			sentence.push_back(merge);
			merge.clear();
			nowdocid++;
		}
		GRAMEND[i]=nowdocid;
		t=clock()-t;
		//printf ("%f seconds.\n",((float)t)/CLOCKS_PER_SEC);
		t=clock();
	}	
}