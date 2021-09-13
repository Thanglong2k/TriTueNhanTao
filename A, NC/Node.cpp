#ifndef Node_H
#define Node_H
#include"bits/stdc++.h"
#include <string.h>
using namespace std;

class Node
{
	private:
		string name;
		int costH;
		int costG;	
		int costF;
	public:
		Node();
		Node(string _name, int _costH, int _costG, int _costF)
		{
			name = _name;
			costH = _costH;
			costG = _costG;
			costF = _costF;
		}
		string getName(){return name;}
		void setName(string _name){name = _name;}
		
		int getCostH(){return costH;}
		void setCostH(int _costH){costH = _costH;}
		
		int getCostG(){return costG;}
		void setCostG(int _costG){costG = _costG;}
		
		int getCostF(){return costF;}
		void setCostF(int _costF){costF = _costF;}
};

#endif
