#include "bits/stdc++.h"
using namespace std;
#define mapList map<string, list<pair<string, vector<int>>>>
#define parent map<string,string>
#define mapStar vector<pair<string , list<Node>>>
int cost = INT_MAX;

class Node {
	private:
	    string TTK;
	    int k, h, g, f;
	public:
		Node(){}
	    Node(string TTK, int k, int h, int g, int f)
	    {
	        this->TTK = TTK;
	        this->k = k;
	        this->h = h;
	        this->g = g;
	        this->f = f;
	    }
	    string getTTK(){return TTK;}
	    int getK(){return k;}
	    int getH(){return h;}
	    int getG(){return g;}
	    int getF(){return f;}
};

class searchA {
	private:
	    Node Nfirst, Nlast;
	    mapList M;
		parent par;
		mapStar V;
	public:
	    searchA(Node first, Node last, mapList M)
	    {
	        this->Nfirst = first;
	        this->Nlast = last;
	        this->M = M;
	    }
	    void Implement(string name);
	    void showWay(string start, string end, ofstream& out);
	    void writeFile(string name);
};

struct compare
{
    bool operator()(Node a, Node b)
    {
		if(a.getF() == b.getF())	return a.getTTK() > b.getTTK();
        return a.getF() > b.getF();
    }
};

void searchA::Implement(string name)
{
    priority_queue<Node, vector<Node>, compare> Q;
    priority_queue<Node, vector<Node>, compare> temp;
    Q.push(Nfirst);
    
    list<Node> listStack;
    listStack.push_back(Nfirst);
    while (Q.size()) {
        auto u = Q.top();
        Q.pop();
        
        listStack.pop_front();
        if (u.getTTK() == Nlast.getTTK()) {
        	cost = u.getF();
        	V.push_back( { u.getTTK(), {u} } );
        	writeFile(name);
            return;
        }
        for (auto& nei : M[u.getTTK()]) {
            nei.second[2] = u.getG() + nei.second[0];
            //cout<<nei.second[1]<<"    -  "<<nei.second[0]<<endl;
            nei.second[3] = nei.second[2] + nei.second[1];
            Node neizz = Node(nei.first, nei.second[0], nei.second[1], nei.second[2], nei.second[3]); 
            //cout<<"neizz "<<neizz.getTTK()<<" -  F  - "<<neizz.getF()<<" -  H  - "<<neizz.getH()<<" -  K  - "<<neizz.getK()<<" -  G  - "<<neizz.getG()<<endl;
            Q.push(neizz);
            temp.push(neizz);
            par[nei.first] = u.getTTK();
        }
        
        while(listStack.size()){
			temp.push(listStack.front());
			listStack.pop_front();
		}
			
		while(temp.size()){
			listStack.push_back(temp.top());
			temp.pop();
		}
		
//		for(auto &z: listStack){
//			cout<<z.getTTK()<<"--"<<z.getF()<<" ";	
//		}
		
		//cout<<endl;
		V.push_back({u.getTTK(), listStack});
    }
}

void searchA::showWay(string start, string end, ofstream& out)
{
    if (start == end)
        out << start;
    else
    {
        showWay(start, par[end], out);
        out << "->" << end;
    }
}

void searchA::writeFile(string name)
{
	ofstream out(name);
	out<<"|"<<setw(10)<<"TT"<<"|"<<setw(10)<<"TTK"<<"|"<<setw(10)<<"k(u,v)"<<"|"<<setw(10)<<"h(v)"
	<<"|"<<setw(10)<<"g(v)"<<"|"<<setw(10)<<"f(v)"<<"|"<<setw(40)<<"Danh sach L"<<"|"<<endl;
	out<<string(108,'-')<<endl;
	for(auto &it: V){	//vector<pair<string , list<Node>>>
		out<<"|"<<setw(10)<<it.first;
		int i = 0;
		for(auto &nei: M[it.first]){	// map<string, list<pair<string, vector<int>>>>
			if(i == 0)
			{
				out<<"|"<<setw(10)<<nei.first;
				out<<"|"<<setw(10)<<nei.second[0];
				out<<"|"<<setw(10)<<nei.second[1];
				out<<"|"<<setw(10)<<nei.second[2];
				out<<"|"<<setw(10)<<nei.second[3]<<"|";
				string builder = " ";
				for(auto &kv: it.second)	
				{
					string f = kv.getTTK() + "-";
					f+= to_string(kv.getF());
					builder.append(f + ' ');	// queue list<Node>
				}
				out<<setw(40)<<builder<<"|"<<endl;
				builder = "";
			}
			else
			{
				out<<"|"<<setw(11);
				out<<"|"<<setw(10)<<nei.first;
				out<<"|"<<setw(10)<<nei.second[0];
				out<<"|"<<setw(10)<<nei.second[1];
				out<<"|"<<setw(10)<<nei.second[2];
				out<<"|"<<setw(10)<<nei.second[3]<<"|"<<setw(41)<<"|"<<endl;
			}
			i++;
		}
		i = 0;
	    if(it.first == Nlast.getTTK())	
		{
			out<<"| TTKT duong di la ";
			showWay(Nfirst.getTTK() , Nlast.getTTK(), out);
			out<<" do dai la "<<it.second.front().getF()<<endl;	
		}
		out<<string(108,'-')<<endl;
	}
	out<<"Duong di la ";
	showWay(Nfirst.getTTK() , Nlast.getTTK(), out);
	out<<" do dai "<<cost;
}
vector<string> split(string str, char delimiter)
{
    vector<string> internal;
    stringstream ss(str);
    string tok;
    while (getline(ss, tok, delimiter))  internal.push_back(tok);
    return internal;
}

Node stringToNode(string input){
	Node z;
	if(input.find("-") < input.length()){ //to find ++ 
	    vector<string> sep = split(input, '-');
		z = Node(sep[0] , 0 ,  stoi(sep[1]), 0, 0);
	} else {
	    z = Node(input, 0, 0, 0, 0);
	}
	return z;
}

void readFile(string name, Node& start, Node& end, mapList& graph)
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
        vector<string> sep = split(line, ':');	// A-14
		vector<string> sub = split(sep[1], ' ');// C-15*9 D-6*7 E-8*13 F-7*20
		list<string> dest;
		dest.assign(sub.begin(), sub.end());
		
		list<pair<string, vector<int>>> nodeDest;
		cout<<sep[0]<<"------\n";
		for (const string &i: dest) {	
			vector<string> sub = split(i, '*');	// C-15    9
			int distance = stoi(sub[1]);	// 9
			Node rs = stringToNode(sub[0]);	// 15
			cout<<rs.getTTK()<<"-"<<rs.getH()<<" - "<<distance<<endl;
			vector<int> data;
			data.push_back(distance);	// k
			data.push_back(rs.getH());	// h
        	nodeDest.push_back(make_pair(rs.getTTK() ,   data));
    	}
    	
    	Node par = stringToNode(sep[0]);
		graph[par.getTTK()] = nodeDest;
    }
    
    fileInput.close();
}

int main()
{
	mapList Graph;
    Node start, end;

    readFile("input.txt", start, end, Graph);
    
	searchA h = searchA(start, end, Graph);
	h.Implement("output.txt");
    //system("pause");
    //return 0;
}
