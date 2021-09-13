#include <bits/stdc++.h>
#include "Node.cpp"
using namespace std;

#define graph map<Node, list<Node, int>>	// map node with k
#define infoNode pair<Node, Node>	// second - f , first - h
#define cal map<Node, int>
#define parentMap map<string, string>

class ASearch
{
	private:
		Node first, last;
	    graph A;
	    parentMap parent;
	    cal calG, calF;
	    //infoNode _Node;
	public:
//		ASearch(Node _first, Node _last, graph _A)
//		{
//			first = _first;
//			last = _last;
//			A = _A;
//		}
		void aStar(string fname);
		void showWay(string start, string end);
		void writeFile(string fname);
};

/**
* convert string to node
*/
Node stringToNode(string input){
	vector<char> split(input.begin(), input.end());
	string strValue = "";
	for(auto s: split) if(isdigit(s))	strValue+=s;
	Node nodezz;
	nodezz.setName(string({split.front()}));
	nodezz.setCostH(stoi(strValue));
	//node nodez = make_pair(string({split.front()}) , stoi(strValue));
	return nodezz;
}

/**
* split string to array string
*/
vector<string> split(string str, char delimiter)
{
    vector<string> internal;
    stringstream ss(str);
    string tok;
    while (getline(ss, tok, delimiter))  internal.push_back(tok);
    return internal;
}
/**
* read data from file
*/
void readFile(string name, Node& start, Node& end, graph& _graph)
{
	// var
    ifstream fileInput(name);
    string Sstart, Send;
    
    if (fileInput.fail())	cout << "Failed to open this file!" << endl;

    fileInput >> Sstart >> Send;
    start = stringToNode(Sstart);
   	end = stringToNode(Send);
   	
   	cout<<start.getCostH()<<" - "<<start.getName();
   	
//    string line;	getline(fileInput, line); // skip the first line
//    
//    while (getline(fileInput, line))
//    {
//        istringstream iss(line);
//        vector<string> sep = split(line, ':');
//		vector<string> sub = split(sep[1], ' ');// C-15*9
//		list<string> dest;
//		dest.assign(sub.begin(), sub.end());	// convert vector to list string data
//		list<pair<Node,int>> nodeWithK;
//		cout<<sep[0]<<"------\n";
//		for (const string &i: dest) {
//			vector<string> sub = split(i, '*');
//			int k = stoi(sub[1]);
//			Node rs = stringToNode(sub[0]);
//			cout<<rs.getName()<<"-"<<rs.getCostH()<<" - "<<k<<endl;
//        	nodeWithK.push_back(rs);
//    	}
//    	
//    	Node par = stringToNode(sep[0]);
//		_graph[par] = nodeWithK;
//    }
    
    fileInput.close();
}

int main()
{
    graph Graph;
    Node start, end;

    readFile("input.txt", start, end, Graph);
//	ASearch h = ASearch(start, end, Graph);
//	h.Implement("output.txt");
}
