#include "bits/stdc++.h"
#include <vector>
using namespace std;
#define mapString map<string,list<string>>
#define vectorString vector<pair<string,list<string>>>
class DFS{
	private:
		string first,last;
		mapString A;
		map<string,string> M;
		vectorString V;
	public:
		DFS(string f, string l,mapString A);
		void Implement(string name);
		void showWay(string first,string last,ofstream& out);
		void writeFile(string name);
		
	
};
DFS :: DFS(string f, string l,mapString A){
	this->first=f;
	this->last=l;
	this->A=A;
}

void DFS :: Implement(string name){
	stack<string> S;
	map<string,int> visited;
	visited[first]=1;
	S.push(first);
	list<string> listStack;
	listStack.push_back(first);
	while(S.size()){
		auto u=S.top();
		S.pop();
		listStack.pop_back();
		if(u==last){
			A[u]={"TTKT"};
			V.push_back({u,{}});
			writeFile(name);
			return;
		}
		list<string>::iterator itr;    
		//duyet list cac dinh ke cua dinh u
	    for (itr = A[u].begin(); itr != A[u].end(); ++itr) {
	        if(visited[*itr]!=1){
	        	visited[*itr]=1;
	        	S.push(*itr);
	        	listStack.push_back(*itr);
	        	M[*itr]=u;
			}			
	    }
	   
		V.push_back({u, listStack});
	    
	}
	
}
void DFS::showWay(string start,string end,ofstream& out){
	if(start == end) out<<start;
	else {
		showWay(start ,M[end],out);
		out<<"->"<<end;
	}
}
void readFile(string name,string& start,string& end,mapString& Graph){
	ifstream fileInput(name); 
   	if (fileInput.fail())
	{
		cout << "Failed to open this file!" << endl;
		cout<<"ko doc dc file";
	}
	
	fileInput>>start>>end;
	while (!fileInput.eof())
	{
		char temp[255];
		fileInput.getline(temp, 255);
		string line = temp;
		string first="";
		for (auto x : line)
		{			
			if (x != ':')
			{				
				if(line[0] == x)
				{
					first=x;
				}
				else {					
					string i; 
					i.push_back(x);
					Graph[first].push_back(i);	
				}
			}			
		}	
	}
	fileInput.close();
}
void DFS::writeFile(string name){
	ofstream out(name);
	vectorString::iterator it;
	list<string>::iterator itr;
	
	out<<"|"<<setw(20)<<"Dinh xet"<<"|"<<setw(20)<<"Dinh ke"<<"|"<<setw(20)<<"Stack"<<"|"<<endl;
	for(it=V.begin();it!=V.end();++it){
		string abc=it->first;
		out<<"|"<<setw(20)<<abc<<"|";
		string a="";
		//duyet list cac dinh ke cua dinh u
	    for (itr = A[abc].begin(); itr != A[abc].end(); ++itr) {
	        a.append(*itr);		
	    }
	    out<<setw(20)<<a<<"|";
	    a="";
	    for (itr = it->second.begin(); itr != it->second.end(); ++itr) {
	        a.append(*itr);		
	    }
	    out<<setw(20)<<a<<"|"<<endl;
		
	}
	out<<"Duong di:";
	showWay(first,last,out);
}
int main(){
	mapString Graph;
	string start,end;
	
	readFile("DFS.txt",start,end,Graph);
	//cout<<start;
	
	DFS h= DFS(start,end,Graph);
	h.Implement("DFSOut.txt");
	
}
