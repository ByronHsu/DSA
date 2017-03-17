#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <map>
#include <ctime>
using namespace std;

struct Node{
	string s;
	vector<int> v;
};
void Get_data();
int Count_words(string);
bool replace(string&, const string&, const string&);
void Find_in_database(string);
void Correct_answer();
bool Compare_string(string,string);
void Print_ans();
void initialize();
bool cmp(int,int);
void Query_expand(string);
bool QM_expand(int);
bool CM_expand(int);
bool SM_expand(int);
bool repeat_ans(int);

clock_t t;
map<string, int> Find_index;
map<string, int>::iterator iter;
string filename[4]={"2gm.small.txt","3gm.small.txt","4gm.small.txt","5gm.small.txt"};
vector<Node> nv;
string s[50000000];
int L[50000000];
vector<int> ans;
vector<int> real_ans;
vector<string> q;

int main(){
	Get_data();
	cout<<nv.size()<<endl;
	string Q;
	while(getline(cin,Q)){
		initialize();
		Query_expand(Q);
		Correct_answer();
		cout<<"query: "<<Q<<endl;
		Print_ans();
	}
}


void Query_expand(string Q){
	q.push_back(Q);
	int size;
	size=q.size();
	for(int i=0,j=0;i<size;i++){
		if(QM_expand(j)){

		}else{
			j++;
		}
	}
	size=q.size();
	for(int i=0,j=0;i<size;i++){
		if(CM_expand(j)){

		}else{
			j++;
		}
	}
	size=q.size();
	for(int i=0,j=0;i<size;i++){
		if(SM_expand(j)){

		}else{
			j++;
		}
	}
	for(int i=0;i<q.size();i++){
		Find_in_database(q[i]);
	}

}

bool SM_expand(int qindex){
	string underline[5]={"","_","_ _","_ _ _","_ _ _ _"};
	string nowstr=q[qindex];
	string str;
	int starnum=0;
	for(int i=0;i<nowstr.length();i++){
		if(nowstr[i]=='*')
			starnum++;
	}
	for(int i=0;i<nowstr.length();i++){
		if(nowstr[i]=='*'){
			q.erase(q.begin()+qindex);
			int leftspace=5-(Count_words(nowstr)-starnum);
			for(int j=0;j<=leftspace;j++){
				if(j==0){
					if(i==nowstr.length()-1){
						str=nowstr;
						replace(str,"*",underline[j]);
						str.erase(str.begin()+i-1);
						q.push_back(str);					
					}
					else{
						str=nowstr;
						replace(str,"*",underline[j]);
						str.erase(str.begin()+i);
						q.push_back(str);		
					}	
				}else{
					str=nowstr;
					replace(str,"*",underline[j]);;
					q.push_back(str);
				}
			}

			int size=q.size();
			for(int k=0,j=0;k<size;k++){
				if(SM_expand(j)){

				}else{
					j++;
				}
			}

			return true;
		}
	}
	return false;
}
bool CM_expand(int qindex){
	string nowstr=q[qindex];
	for(int i=0;i<nowstr.length();i++){
		if(nowstr[i]=='/'){
			q.erase(q.begin()+qindex);

			int left,right;
			for(int j=i;j>=0;j--){
				if(j==0){
					left=0;break;
				}
				if(nowstr[j]==' '){
					left=j+1;break;
				}
			}
			for(int j=i;j<nowstr.length();j++){
				if(j==nowstr.length()-1){
					right=nowstr.length()-1;break;
				}
				if(nowstr[j]==' '){
					right=j-1;break;
				}
			}
			string merge;
			for(int j=left;j<=right;j++)
				merge+=nowstr[j];
			// at/in/on
			stringstream ss(merge);
			string str,sub_str;
			while(getline(ss,sub_str,'/')){
				str=nowstr;
				replace(str,merge,sub_str);
				q.push_back(str);
			}
			int size=q.size();
			for(int k=0,j=0;k<size;k++){
				if(CM_expand(j)){

				}else{
					j++;
				}
			}
			return true;			
		}
	}
	return false;
}
bool QM_expand(int qindex){
	string nowstr=q[qindex];
	for(int i=0;i<nowstr.length();i++){
		if(nowstr[i]=='?'){
			q.erase(q.begin()+qindex);

			string str;
			string tem;
			tem+='?';
			for(int j=i+1;j<nowstr.length();j++){
				if(nowstr[j]==' ')
					break;
				else{
					tem+=nowstr[j];
				}
			}
			str=nowstr;
			replace(str,tem,"");
			str.erase(str.begin()+i);
			if(str[str.length()-1]==' '){
				str.erase(str.begin()+(str.length()-1));
			}
			q.push_back(str);

			str=nowstr;
			replace(str,"?","");
			q.push_back(str);

			int size=q.size();
			for(int k=0,j=0;k<size;k++){
				if(QM_expand(j)){

				}else{
					j++;
				}
			}
			return true;
		}
	}
	return false;
}
bool Compare_string(string s1,string s2){
	if(Count_words(s1)!=Count_words(s2))
		return false;
	else{
		string str1,str2;
		stringstream ss1(s1);
		stringstream ss2(s2);
		while(getline(ss1,str1,' ')&&getline(ss2,str2,' ')){
			if(str2=="_")
				continue;
			else{
				if(str1!=str2){
					return false;
				}
			}
		}
		return true;
	}
}
void Correct_answer(){
	for(int i=0;i<ans.size();i++){
		for(int j=0;j<q.size();j++){
			if(Compare_string(s[ans[i]],q[j]))
				real_ans.push_back(ans[i]);
		}
	}
}

void Find_in_database(string dq){
	stringstream ss(dq);
	string words[5];
	for(int i=0;i<5;i++)
		words[i]+="0";
	string str;
	int index=0;
	while(getline(ss,str,' ')){
		if(str!="_"){
			words[index++]=str;
		}
	}
	int nvindex[5],nindex[5]={0},nvsize=nv.size();
	for(int i=0;i<5;i++){
		int f;
		iter=Find_index.find(words[i]);
		if(iter != Find_index.end())
		   f=iter->second;
		else
		   f=-1;
		nvindex[i]=f;
	}

	while(1){
		int min_nvindex_num=0;
		for(int i=1;i<5;i++)
			if(nv[ nvindex[i] ].v[ nindex[i] ]<nv[ nvindex[min_nvindex_num] ].v[ nindex[ min_nvindex_num ] ])
				min_nvindex_num=i;
			if(nindex[ min_nvindex_num ]+1 >= nv[ nvindex[min_nvindex_num] ].v.size())
				break;
			else
				nindex[ min_nvindex_num ] += 1;

			if(nv[nvindex[0]].v[nindex[0]]==nv[nvindex[1]].v[nindex[1]]
				&&nv[nvindex[1]].v[nindex[1]]==nv[nvindex[2]].v[nindex[2]]
				 &&nv[nvindex[2]].v[nindex[2]]==nv[nvindex[3]].v[nindex[3]]
				  &&nv[nvindex[3]].v[nindex[3]]==nv[nvindex[4]].v[nindex[4]]
				   &&Count_words(s[nv[nvindex[0]].v[nindex[0]]])==Count_words(dq)
				    &&!repeat_ans(nv[nvindex[0]].v[nindex[0]]))
						{ans.push_back(nv[nvindex[0]].v[nindex[0]]);}

	}
}
bool repeat_ans(int a){
	for(int i=0;i<ans.size();i++)
		if(a==ans[i]){
			return 1;
		}
	return 0;
}
void Get_data(){

	t = clock();

	Node n;
	n.s="0";
	s[0]+="0";
	for(int i=0;i<10000000;i++)
		n.v.push_back(i);
	nv.push_back(n);
	Find_index.insert(pair<string,int>("0",0));
	int index1=1;

	for(int ll=0;ll<4;ll++){
		ifstream fin(filename[ll]);
		while(getline (fin,s[index1],'	')){
			//cout<<index1<<endl;
			fin>>L[index1];
		    stringstream ss(s[index1]);
		    string sub_str;
		    while(getline(ss,sub_str,' ')){
				int f;
				iter=Find_index.find(sub_str);
				if(iter != Find_index.end())
				   f=iter->second;
				else
				   f=-1;

				if(f==-1){
					Node n;
					n.s=sub_str;
					n.v.push_back(index1);
					nv.push_back(n);				
					Find_index.insert(pair<string,int>(sub_str,nv.size()-1));

				}else{
					if(nv[f].v[ nv[f].v.size()-1 ]!=index1)	
						nv[f].v.push_back(index1);
				}
		    }
			index1++;
			fin.get();
	    }
		t = clock() - t;
		printf ("%f seconds.\n",t,((float)t)/CLOCKS_PER_SEC);
	}
	cout<<index1<<endl;
}

int Count_words(string c){
	int count=1;
	for(int i=0;i<c.length();i++){
		if(c[i]==' ')
			count++;
	}
	return count;
}
bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}
void initialize(){
	ans.clear();
	real_ans.clear();
	q.clear();	
}
void Print_ans(){
	sort(real_ans.begin(),real_ans.end(),cmp);
	int rsize=real_ans.size();
	if(rsize>5)
		rsize=5;
	cout<<"output: "<<rsize<<endl;
	for(int i=0;i<rsize;i++)
		cout<<s[real_ans[i]]<<"	"<<L[real_ans[i]]<<endl;	
}
bool cmp(int a,int b){
	return L[a]>L[b];
}
