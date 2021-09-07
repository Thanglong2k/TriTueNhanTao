#include "bits/stdc++.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
#define node pair<string, int>
#define mapNode map<node, list<node>>

class BestFirstSearch
{
	private:
	    node first, last;
	    mapNode A;
	    map<string, string> M;
	    mapNode V;
	
	public:
	    BestFirstSearch(node f, node l, mapNode A);
	    void Implement(string name);
	    void showWay(string first, string last, ofstream& out);
	    void writeFile(string name);
};

BestFirstSearch::BestFirstSearch(node f, node l, mapNode A)
{
    this->first = f;
    this->last = l;
    this->A = A;
}

struct compare
{
    bool operator()(node a, node b)
    {
        return a.second > b.second;
    }
};

void BestFirstSearch::Implement(string name)
{
    priority_queue<node, vector<node>, compare> Q;
    map<node, int> visited;
    visited[first] = 1;
    Q.push(first);
    list<node> listStack;
	listStack.push_back(first);
    while (Q.size())
    {
        auto u = Q.top();
        Q.pop();
        listStack.pop_back();
        if (u == last)
        {
        	A[u] = {node("TTKT",0)};
        	V[u] = {};
        	writeFile(name);
            return;
        }
        list<node>::iterator itr;
        // duyet list cac dinh ke cua dinh u
        for (itr = A[u].begin(); itr != A[u].end(); ++itr)
        {
            if (visited[*itr] != 1)
            {
                visited[*itr] = 1;
                Q.push(*itr);
                listStack.push_back(*itr);
                M[itr->first] = u.first;
            }
        }
        V[u] = listStack;
    }
}
void BestFirstSearch::showWay(string start, string end, ofstream& out)
{
    if (start == end)
        out << start;
    else
    {
        showWay(start, M[end],out);
        out << "->" << end;
    }
}

node stringToNode(string input){
	vector<char> split(input.begin(), input.end());
	string strValue = "";
	for(auto s: split) if(isdigit(s))	strValue+=s;
	node nodezz = make_pair(string({split.front()}) , std::stoi(strValue));
	return nodezz;
}

vector<string> split(string str, char delimiter)
{
    vector<string> internal;
    stringstream ss(str);
    string tok;
    while (getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    return internal;
}

void readFile(string name, node& start, node& end, mapNode& Graph)
{
	// var
    ifstream fileInput(name);
    string Sstart, Send;
    
    if (fileInput.fail())	cout << "Failed to open this file!" << endl;

    fileInput >> Sstart >> Send;
    start = stringToNode(Sstart);
   	end = stringToNode(Send);
   	
    string line;
    getline(fileInput, line); // skip the first line
    
    while (std::getline(fileInput, line))
    {
        istringstream iss(line);
        vector<string> sep = split(line, ':');
		vector<string> sub = split(sep[1], ' ');
		list<string> dest;
		dest.assign(sub.begin(), sub.end());
		list<node> nodeDest;
		//cout<<sep[0]<<"------\n";
		for (const string &i: dest) {
			node rs = stringToNode(i);
			//cout<<rs.first<<rs.second<<endl;
        	nodeDest.push_back(rs);
    	}
    	
    	node par = stringToNode(sep[0]);
		Graph[par] = nodeDest;
    }
    
    fileInput.close();
}

void BestFirstSearch::writeFile(string name){
	ofstream out(name);
//	mapNode::iterator it;
//	list<node>::iterator itr;
	out<<"|"<<setw(20)<<"Act"<<"|"<<setw(20)<<"Neibor"<<"|"<<setw(20)<<"Queue"<<"|"<<endl;
	for(auto &it: V){
		node pos = it.first;
		out<<"|"<<setw(20)<<pos.first<<"|";
		string a = "";
	    for(auto &kv: A[pos]){
	    	a.append(kv.first);	// dinh ke
		}
	
	    out<<setw(20)<<a<<"|";
	    a = "";
	    
	    for(auto &z: it.second){
	    	a.append(z.first);
		}
	    out<<setw(20)<<a<<"|"<<endl;
	}
//	for(it = V.begin(); it != V.end(); ++it){
//		node pos = it->first;
//		out<<"|"<<setw(20)<<pos.first<<"|";
//		string a = "";
//	    for(auto &kv: A[pos]){
//	    	a.append(kv.first);	// dinh ke
//		}
//	
//	    out<<setw(20)<<a<<"|";
//	    a = "";
//	    
//	    for(auto &z: it->second){
//	    	a.append(z.first);
//		}
//	    out<<setw(20)<<a<<"|"<<endl;
//	}
	out<<"Way:";
	showWay(first.first, last.first, out);
}
int main()
{
    mapNode Graph;
    node start, end;

    readFile("input.txt", start, end, Graph);
	BestFirstSearch h = BestFirstSearch(start, end, Graph);
	h.Implement("output.txt");
}
