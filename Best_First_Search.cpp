#include"bits/stdc++.h"
using namespace std;
#define node pair<string,int>
#define mapNode map<node,list<node>>

class BestFirstSearch{
	private:
		node first,last;
		mapNode A;
		map<string,string> M;
	public:
		BestFirstSearch(node f, node l,mapNode A);
		void Implement();
		void showWay(string first,string last);
	
};
BestFirstSearch :: BestFirstSearch(node f, node l,mapNode A){
	this->first=f;
	this->last=l;
	this->A=A;
}
struct compare{
	bool operator()(node a,node b){
		return a.second > b.second;
	}	
};
void BestFirstSearch :: Implement(){
	priority_queue<node,vector<node>,compare> Q;
	map<node,int> visited;
	visited[first]=1;
	Q.push(first);
	while(Q.size()){
		auto u=Q.top();
		Q.pop();		
		if(u==last){
			showWay(first.first,last.first);
			return;
		}
		list<node>::iterator itr;    
		//duyet list cac dinh ke cua dinh u
	    for (itr = A[u].begin(); itr != A[u].end(); ++itr) {
	        if(visited[*itr]!=1){
	        	visited[*itr]=1;
	        	Q.push(*itr);
	        	M[itr->first]=u.first;
			}			
	    }		    
	}	
}
void BestFirstSearch::showWay(string start,string end){
	if(start == end) cout<<start;
	else {
		showWay(start ,M[end]);
		cout<<"->"<<end;
	}
}
int main(){
	mapNode Graph;
	
	Graph.insert({node("A",20),{node("B",15),node("C",6),node("D",7)}});
	Graph.insert({node("B",15),{node("E",10)}});
	Graph.insert({node("C",6),{node("E",10),node("F",8)}});
	Graph.insert({node("D",7),{node("G",13),node("H",3)}});
	Graph.insert({node("E",10),{node("K",0)}});
	Graph.insert({node("F",8),{node("K",0),node("H",3)}});
	Graph.insert({node("G",13),{node("H",3)}});
	Graph.insert({node("H",3),{node("I",5)}});
	Graph.insert({node("I",5),{node("K",0)}});
	BestFirstSearch h= BestFirstSearch(node("A",20),node("K",0),Graph);
	h.Implement();
	
}

