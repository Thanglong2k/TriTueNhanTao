#include"bits/stdc++.h"
#include<list>
#include<vector>
using namespace std;

#define mapString map<string,list<string>>
#define vectorString vector<pair<string,list<string>>>

class BFS{
	private:
		string first,last;
		mapString A;
		map<string,string> M;
		vectorString V;
	public:
		BFS(string f, string l,mapString A);
		void Input();
		void Implement(string name);
		void showWay(string first,string last,ofstream&);
		void writeFile(string name);
	
};
BFS :: BFS(string f, string l,mapString A){
	this->first=f;
	this->last=l;
	this->A = A;
}

void readFile(string name,string& start,string& end,mapString& Graph){
	ifstream fileInput; 
   	fileInput.open("DFS.txt");
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
		list<string> listString;
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
void BFS :: Implement(string name){
	queue<string> Q;
	map<string,int> visited;
	visited[first]=1;
	Q.push(first);
	list<string> listStack;
	listStack.push_back(first);

	while(Q.size()){
		auto u=Q.front();
		Q.pop();	
<<<<<<< HEAD
		listStack.pop_front();	
=======
		
		listStack.pop_front();
>>>>>>> b5dcc8d0db1a5004fd267c8643b3f7116c3f58a4
		if(u==last){
			A[u]={"TTKT"};
			V.push_back({u,{}});
			writeFile(name);
			break;
		}
		list<string>::iterator itr; 
 
		//duyet list cac dinh ke cua dinh u
	    for (itr = A[u].begin(); itr != A[u].end(); ++itr) {
	        if(visited[*itr]!=1){
	        	visited[*itr]=1;
	        	Q.push(*itr);
	        	listStack.push_back(*itr);
<<<<<<< HEAD
	        	M[*itr]=u;	        
			}			
	    }	
		V[u]=listStack;
			    
=======
	        	M[*itr]=u;
			}			
	    }	
	    
		V.push_back({u, listStack});	   
	
>>>>>>> b5dcc8d0db1a5004fd267c8643b3f7116c3f58a4
	}	
	mapString::iterator itr;
	for (itr = V.begin(); itr != V.end(); ++itr) {
	       cout<<"-"<<itr->first;		
	    }
}
void BFS::showWay(string start,string end,ofstream& out){
	if(start == end) out<<start;
	else {
		showWay(start ,M[end],out);
		out<<"->"<<end;
	}
}
void BFS::writeFile(string name){
	ofstream out(name);
	vectorString::iterator it;
	list<string>::iterator itr;

	out<<"BFS"<<endl;
	out<<"|"<<setw(20)<<"Dinh xet"<<"|"<<setw(20)<<"Dinh ke"<<"|"<<setw(20)<<"Queue"<<"|"<<endl;
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
	cout<<"Thanh cong";
}
int main(){
	mapString Graph;
	string start,end;
	readFile("DFS.txt",start,end,Graph);
	BFS h= BFS(start,end,Graph);
	h.Implement("BFSOut.txt");
	
}

