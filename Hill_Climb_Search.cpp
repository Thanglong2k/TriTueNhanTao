#include"bits/stdc++.h"

using namespace std;
#define node pair<string,int>
#define mapNode map<node,list<node>>

class HillClimb{
	private:
		node first,last;
		mapNode A;
		mapNode V;
		map<string,string> M;
	public:
		HillClimb(node f, node l,mapNode A);
		void Implement(string name);
		void showWay(string first,string last,ofstream& out);
		void writeFile(string name);
};
HillClimb :: HillClimb(node f, node l,mapNode A){
	this->first=f;
	this->last=l;
	this->A=A;
}
struct compare{
	bool operator()(node a,node b){
		return a.second < b.second;
	}	
};
void HillClimb :: Implement(string name){
	
	stack<node> Q;
	map<node,int> visited;
	visited[first]=1;
	Q.push(first);
	list<node> listStack;
	listStack.push_back(first);
	while(Q.size()){
		auto u=Q.top();
		Q.pop();		
		listStack.pop_back();
		if(u==last){
			A[u]={node("TTKT",0)};
			V[u]={};
			writeFile(name);
			return;
		}
		list<node>::iterator itr;    
		priority_queue<node,vector<node>,compare> Q1;
		//duyet list cac dinh ke cua dinh u
	    for (itr = A[u].begin(); itr != A[u].end(); ++itr) {
	        if(visited[*itr]!=1){
	        	visited[*itr]=1;	        	
	        	Q1.push(*itr);	        	
	        	M[itr->first]=u.first;	        	
			}			
	    }
		while(Q1.size()){
			auto nodeNew=Q1.top();
			Q1.pop();			
			Q.push(nodeNew);
			listStack.push_back(nodeNew);
		}  
		V[u]=listStack;
	}	
}
void HillClimb::showWay(string start,string end,ofstream& out){
	if(start == end) out<<start;
	else {
		showWay(start ,M[end],out);
		out<<"->"<<end;
	}
}
void HillClimb::writeFile(string name){
	ofstream out(name);
	mapNode::iterator it;
	list<node>::iterator itr;
	out<<"|"<<left<<setw(40)<<"Dinh xet"<<"|"<<setw(40)<<"Dinh ke"<<"|"<<setw(40)<<"Stack"<<"|"<<endl;
	for(it=V.begin();it!=V.end();++it){
		node abc=it->first;
		string a;
		a=abc.first+"("+to_string(abc.second)+")";
		out<<"|"<<setw(40)<<a<<"|";
		a="";
		//duyet list cac dinh ke cua dinh u
	    for (itr = A[abc].begin(); itr != A[abc].end(); ++itr) {
	        a=a+itr->first+"("+to_string(itr->second)+")";		
	    }
	    out<<setw(40)<<a<<"|";
	    a="";
	    for (itr = it->second.begin(); itr != it->second.end(); ++itr) {
	        a=a+itr->first+"("+to_string(itr->second)+")";	
	    }
	    out<<setw(40)<<a<<"|"<<endl;
		
	}
	out<<"Duong di:";
	showWay(first.first,last.first,out);
}
vector<string> split (string s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}
node stringToNode(string s){
	vector<string> str;
	str=split(s,'-');
	return node(str[0],stoi(str[1]));
}
void readFile(string name,node& start,node& end,mapNode& Graph){
	ifstream fileInput(name); 
   	if (fileInput.fail())
	{
		cout << "Failed to open this file!" << endl;
		cout<<"ko doc dc file";
	}
	string pointStart,pointEnd;
	fileInput>>pointStart>>pointEnd;
	start=stringToNode(pointStart);	
	end=stringToNode(pointEnd);
	string line;
	getline(fileInput,line);
	int te=0;
	
	while (getline(fileInput, line))
	{	
		vector<string> listString,listStringSecond;
		listString=split(line,':');
		listStringSecond=split(listString[1],',');
		
		for(auto i:listStringSecond){
		
			Graph[stringToNode(listString[0])].push_back(stringToNode(i));
		}
		
		
		
		
	}
	
//	mapNode::iterator it;
//		list<node>::iterator io;
//		for(it=Graph.begin();it!=Graph.end();it++){
//			cout<<it->first.first<<it->first.second<<":";
//			for(io=it->second.begin();io!=it->second.end();io++)
//				cout<<io->first<<io->second;
//			cout<<endl;
//		}
	
	fileInput.close();
}
int main(){
	mapNode Graph;
	node start,end;
//	Graph.insert({node("A",20),{node("B",15),node("C",6),node("D",7)}});
//	Graph.insert({node("B",15),{node("E",10)}});
//	Graph.insert({node("C",6),{node("E",10),node("F",8)}});
//	Graph.insert({node("D",7),{node("G",13),node("H",3)}});
//	Graph.insert({node("E",10),{node("K",0)}});
//	Graph.insert({node("F",8),{node("K",0),node("H",3)}});
//	Graph.insert({node("G",13),{node("H",3)}});
//	Graph.insert({node("H",3),{node("I",5)}});
//	Graph.insert({node("I",5),{node("K",0)}});
	readFile("Hill_Climb_Search.txt",start,end,Graph);	
	HillClimb h= HillClimb(start,end,Graph);
	h.Implement("Hill_Climb_Search_Out.txt");
	
}

