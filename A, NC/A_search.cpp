#include "bits/stdc++.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
#define node pair<string, int>
#define mapNodeList map<node, list<pair<node,int>> >
#define vectorNode vector< pair<node, list<pair<node,int>> >
#define cal map<string, int>
#define pairNodeNode pair<node,node>

class BestFirstSearch
{
	private:
	    node first, last;
	    mapNodeList A;
	    map<string, string> M;
	    //vectorNode V;
	    cal calG,calF;
	    pairNodeNode mapNN;
	public:
	    BestFirstSearch(node f, node l, mapNodeList A);
	    void Implement(string name);
	    void showWay(string first, string last);
	    void writeFile(string name);
};

BestFirstSearch::BestFirstSearch(node f, node l, mapNodeList A)
{
    this->first = f;
    this->last = l;
    this->A = A;
}

struct compare
{
    bool operator()(pairNodeNode a, pairNodeNode b)
    {
//    	if(a.second.second == b.second.second){
//    		return calG[a.second.first] > calG[b.second.first];
//		}
    	//cout<<a.second.second<<" - "<<b.second.second;
        return a.second.second > b.second.second;
    }
};


void BestFirstSearch::showWay(string start, string end)
{
    if (start == end)
        cout << start;
    else
    {
        showWay(start, M[end]);
        cout << "->" << end;
    }
}

node stringToNode(string input){
	vector<char> split(input.begin(), input.end());
	string strValue = "";
	for(auto s: split) if(isdigit(s))	strValue+=s;
	node nodez = make_pair(string({split.front()}) , stoi(strValue));
	return nodez;
}

vector<string> split(string str, char delimiter)
{
    vector<string> internal;
    stringstream ss(str);
    string tok;
    while (getline(ss, tok, delimiter))  internal.push_back(tok);
    return internal;
}

void readFile(string name, node& start, node& end, mapNodeList& graph)
{
	// var
    ifstream fileInput(name);
    string Sstart, Send;
    
    if (fileInput.fail())	cout << "Failed to open this file!" << endl;

    fileInput >> Sstart >> Send;
    start = stringToNode(Sstart);
   	end = stringToNode(Send);
   	
    string line;	getline(fileInput, line); // skip the first line
    
    while (getline(fileInput, line))
    {
        istringstream iss(line);
        vector<string> sep = split(line, ':');
		vector<string> sub = split(sep[1], ' ');// C-15*9
		list<string> dest;
		dest.assign(sub.begin(), sub.end());
		list<pair<node,int>> nodeDest;
		//cout<<sep[0]<<"------\n";
		for (const string &i: dest) {
			vector<string> sub = split(i, '*');
			int distance = stoi(sub[1]);
			node rs = stringToNode(sub[0]);
			//cout<<rs.first<<"-"<<rs.second<<" - "<<distance<<endl;
        	nodeDest.push_back(make_pair(rs,distance));
    	}
    	
    	node par = stringToNode(sep[0]);
		graph[par] = nodeDest;
    }
    
    fileInput.close();
}

void BestFirstSearch::Implement(string name)
{
    priority_queue<pairNodeNode, vector<pairNodeNode>, compare> Q;
    priority_queue<pairNodeNode, vector<pairNodeNode>, compare> temp;
   
	mapNN = pairNodeNode(first, node(first.first,0));
    Q.push(mapNN);

    list<pairNodeNode> listStack;
	listStack.push_back( pairNodeNode(first, node(first.first,0)) );
    while (Q.size())
    {
        auto u = Q.top().first;
        //cout<<"b "<<Q.size();
        Q.pop();
        
        listStack.pop_front();
        //cout<<u.first<<"-"<<last.first<<endl;
        if (u == last)
        {
        	//A[u] = {node("TTKT",0)};
        	//V.push_back({u,{}});
        	//writeFile(name);
        	showWay(first.first, u.first);
            return;
        }

		for(auto &nei: A[u]){
			//cout<<nei.first.first;
			calG[nei.first.first] = calG[u.first] + nei.second;
			//cout<<"==="<<nei.first.second<<endl;
			calF[nei.first.first] = calG[nei.first.first] + nei.first.second;
			//cout<<nei.first.first<<endl;
			//cout<<calF[nei.first.first]<<"-"<<endl;
			
			mapNN = pairNodeNode(nei.first, node(nei.first.first, calF[nei.first.first]));
			//cout<<mapNN.first.first<<"----"<<mapNN.first.second<<endl;
			Q.push(mapNN);
			temp.push(mapNN);
			
			//temp.push(nei);
//			temp.push(nei);
			M[nei.first.first] = u.first;
		}
		
//		cout<<"\t"<<A[u].size()<<endl;
		while(listStack.size()){
			temp.push(listStack.front());
			listStack.pop_front();
		}
			
		while(temp.size()){
			listStack.push_back(temp.top());
			temp.pop();
		}
		
		for(auto &z: listStack){
			cout<<z.first.first<<"--"<<z.second.second<<" ";	
		}
		cout<<endl;
//      V.push_back({u,listStack});
    }
}


int main()
{
    mapNodeList Graph;
    node start, end;

    readFile("input.txt", start, end, Graph);
	BestFirstSearch h = BestFirstSearch(start, end, Graph);
	h.Implement("output.txt");
}
