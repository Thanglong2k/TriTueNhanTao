#include"bits/stdc++.h"
using namespace std;
#define mapString map<string,list<string>>

class BFS{
	private:
		string first,last;
		mapString A;
		map<string,string> M;
	public:
		BFS(string f, string l,mapString A);
		void Implement();
		void showWay(string first,string last);
	
};
BFS :: BFS(string f, string l,mapString A){
	this->first=f;
	this->last=l;
	this->A=A;
}

void BFS :: Implement(){
	queue<string> Q;
	map<string,int> visited;
	visited[first]=1;
	Q.push(first);
	while(Q.size()){
		auto u=Q.front();
		cout<<endl<<u<<":";
		Q.pop();		
		if(u==last){
			showWay(first,last);
			return;
		}
		list<string>::iterator itr;    
		//duyet list cac dinh ke cua dinh u
	    for (itr = A[u].begin(); itr != A[u].end(); ++itr) {
	        if(visited[*itr]!=1){
	        	visited[*itr]=1;
	        	Q.push(*itr);
	        	cout<<*itr<<",";
	        	M[*itr]=u;
			}			
	    }		    
	}	
}
void BFS::showWay(string start,string end){
	if(start == end) cout<<start;
	else {
		showWay(start ,M[end]);
		cout<<"->"<<end;
	}
}
int main(){
	mapString Graph;
	
	Graph.insert({"A",{"B","C","D"}});
	Graph.insert({"B",{"E"}});
	Graph.insert({"C",{"E","F"}});
	Graph.insert({"D",{"G","H"}});
	Graph.insert({"E",{"K"}});
	Graph.insert({"F",{"K","H"}});
	Graph.insert({"G",{"H"}});
	Graph.insert({"H",{"I"}});
	Graph.insert({"I",{"K"}});
	BFS h= BFS("A","K",Graph);
	h.Implement();
	
}

