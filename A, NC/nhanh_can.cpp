#include "bits/stdc++.h"
using namespace std;
#define mapList map<string, list<pair<string, vector<int>>>>
#define parent map<string,string>
#define mapStar vector<pair<string , list<Node>>>
#define mapStarL vector<pair<Node , list<Node>>>

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
		mapStarL V;
		mapStar V1;
	public:
	    searchA(Node first, Node last, mapList M)
	    {
	        this->Nfirst = first;
	        this->Nlast = last;
	        this->M = M;
	    }
	    void Implement(string name);
	    void showWay(string start, string end, ofstream& out);
	    void showWayNor(string start, string end);
	    void writeFile(string name);
};

struct compare
{
    bool operator()(Node a, Node b)
    {
		if(a.getF() == b.getF())	return a.getTTK() > b.getTTK();
        return a.getF() < b.getF();
    }
};

void searchA::Implement(string name)
{
    priority_queue<Node, vector<Node>, compare> Q1;
    
    stack<Node> temp;
    //temp.push(Nfirst);
    
    stack<Node> Q;
    Q.push(Nfirst);
    
    list<Node> LStack;	// store L
    LStack.push_back(Nfirst);
    
    list<Node> L1Stack;	// store L1 - Q
    //L1Stack.push_back(Nfirst);
    
    while (Q.size()) {
        auto u = Q.top(); Q.pop();
        LStack.pop_front();
        //L1Stack.pop_front();
        if (u.getTTK() == Nlast.getTTK()) {
            if(u.getF() < cost)	
			{
				cout<<"TTKt, duong di tam thoi do dai "<<u.getF();
				cost = u.getF();
				stack<Node> checkExtMin = Q;
				// copy new stack
				// check f value element of stack 
				bool minF = false;
				while(checkExtMin.size()){
					Node z = checkExtMin.top();
					if(z.getF() < u.getF())	minF = true;
					checkExtMin.pop();
				}
				if(minF == false)
				{
					cout<<"\nOk";
					showWayNor(Nfirst.getTTK(), u.getTTK());
					V.push_back( { u, LStack } );
        			writeFile(name);
					return;
				}
			}
        }
        for (auto& nei : M[u.getTTK()]) {
            nei.second[2] = u.getG() + nei.second[0];
            //cout<<nei.second[1]<<"  -  "<<nei.second[0]<<endl;
            nei.second[3] = nei.second[2] + nei.second[1];
            Node neizz = Node(nei.first, nei.second[0], nei.second[1], nei.second[2], nei.second[3]); 
            //cout<<"neizz "<<neizz.getTTK()<<" -  F  - "<<neizz.getF()<<" -  H  - "<<neizz.getH()<<" -  K  - "<<neizz.getK()<<" -  G  - "<<neizz.getG()<<endl;
            Q1.push(neizz);
            //temp.push(neizz);
            //listStack.push(neizz);
            par[nei.first] = u.getTTK();
        }	// F27 C24 E21 D13
        
        if(LStack.size()>0)
		{
        	LStack.reverse();
        	//for(auto &kv: LStack) cout<<to_string(kv)<<" ";
        	while(LStack.size()){
        		temp.push(LStack.front());
        		LStack.pop_front();
			}
		}
		
        while(Q1.size())
        {
        	Node a = Q1.top();
			//cout<<"   - " <<a.getF()<<endl;
			L1Stack.push_front(a);
			
        	Q.push(a);
        	temp.push(a);
        	Q1.pop();
		}
		
		while(temp.size()){
			LStack.push_back(temp.top());
			temp.pop();
		}

//		cout<<"\nL1 stack------------";
//		for(auto &z: L1Stack){
//			cout<<z.getTTK()<<"--"<<z.getF()<<" ";	
//		}
//		
//		cout<<"\nL stack------------";
//		for(auto &z: LStack){
//			cout<<z.getTTK()<<"--"<<z.getF()<<" ";	
//		}
		
		cout<<endl;
		V1.push_back({u.getTTK() , L1Stack});
		V.push_back({u, LStack});
		
		//listStack.clear();
		L1Stack.clear();
    }
}


void searchA::showWayNor(string start, string end)
{
    if (start == end)
        cout << start;
    else
    {
        showWayNor(start, par[end]);
        cout << "->" << end;
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
	<<"|"<<setw(10)<<"g(v)"<<"|"<<setw(10)<<"f(v)"<<"|"<<setw(25)<<"Danh sach L1"<<"|"<<setw(40)<<"Danh sach L"<<"|"<<endl;
	out<<string(133,'-')<<endl;
	for(auto &it: V){	//vector<pair<string , list<Node>>>
		//node pos = it.first;
		out<<"|"<<setw(10)<<it.first.getTTK();
		int i = 0;
		for(auto &nei: M[it.first.getTTK()]){	// map<string, list<pair<string, vector<int>>>>
			if(i == 0)
			{
				out<<"|"<<setw(10)<<nei.first;
				out<<"|"<<setw(10)<<nei.second[0];
				out<<"|"<<setw(10)<<nei.second[1];
				out<<"|"<<setw(10)<<nei.second[2];
				out<<"|"<<setw(10)<<nei.second[3]<<"|";
				string builder = "";
				for(auto &l1: V1)
				{
					if(it.first.getTTK() == l1.first)
					{
						for(auto &b: l1.second){
							string f = b.getTTK() + "-";
							f+= to_string(b.getF());
							builder.append(f + ' ');	// queue list<Node>
						}
					}	
				}
				out<<setw(25)<<builder<<"|";
				builder = "";
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
				out<<"|"<<setw(10)<<nei.second[3]<<"|"<<setw(26)<<"|"<<setw(41)<<"|"<<endl;
			}
			i++;
		}
		i = 0;
		
	    if(it.first.getTTK() == Nlast.getTTK())	
		{
			out<<"| TTKT duong tam thoi la ";
			showWay(Nfirst.getTTK() , Nlast.getTTK(), out);
			out<<" do dai la "<<it.first.getF();
			//if(it.second.front.getF != it.first)
			out<<setw(30)<<"|";
			
			string builder = "";
			for(auto &kv: it.second)	
			{
				string f = kv.getTTK() + "-";
				f+= to_string(kv.getF());
				builder.append(f + ' ');	// queue list<Node>
			}
			out<<setw(40)<<builder<<"|"<<endl;
		}
		out<<string(133,'-')<<endl;
	}
	out<<"Duong di la ";
	showWay(Nfirst.getTTK() , Nlast.getTTK(), out);
	out<<" do dai la "<<cost;
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
		//cout<<sep[0]<<"------\n";
		for (const string &i: dest) {	
			vector<string> sub = split(i, '*');	// C-15    9
			int distance = stoi(sub[1]);	// 9
			Node rs = stringToNode(sub[0]);	// 15
			//cout<<rs.getTTK()<<"-"<<rs.getH()<<" - "<<distance<<endl;
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
