#include"bits/stdc++.h"
using namespace std;
#define mapString map<string,list<string>>

class DFS{
	private:
		string first,last;
		mapString A;
		map<string,string> M;
	public:
		DFS(string f, string l,mapString A);
		void Implement();
		void showWay(string first,string last);
	
};
DFS :: DFS(string f, string l,mapString A){
	this->first=f;
	this->last=l;
	this->A=A;
}

void DFS :: Implement(){
	stack<string> S;
	S.push(first);
	while(S.size()){
		auto u=S.top();
		S.pop();		
		if(u==last){
			showWay(first,last);
			return;
		}
		list<string>::iterator itr;    
		//duyet list cac dinh ke cua dinh u
	    for (itr = A[u].begin(); itr != A[u].end(); ++itr) {       	
        	S.push(*itr);
        	if(M[*itr]==""){
        		M[*itr]=u;					
			}
	    }		    
	}	
}
void DFS::showWay(string start,string end){
	if(start == end) cout<<start;
	else {
		showWay(start ,M[end]);
		cout<<"->"<<end;
	}
}
int main(){
	mapString Graph;
	
//	Graph.insert({"A",{"B","C","D"}});
//	Graph.insert({"B",{"E"}});
//	Graph.insert({"C",{"E","F"}});
//	Graph.insert({"D",{"G","H"}});
//	Graph.insert({"E",{"K"}});
//	Graph.insert({"F",{"K","H"}});
//	Graph.insert({"G",{"H"}});
//	Graph.insert({"H",{"I"}});
//	Graph.insert({"I",{"K"}});
	Graph.insert({"A",{"B","C"}});
	Graph.insert({"B",{"D"}});
	Graph.insert({"C",{"F"}});
	Graph.insert({"D",{"G"}});
	Graph.insert({"E",{"C"}});
	Graph.insert({"F",{"E"}});
	
	DFS h= DFS("A","G",Graph);
	h.Implement();
	
}

