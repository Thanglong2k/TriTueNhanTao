#include <bits/stdc++.h>
using namespace std;
int main(){
	stack<int> test;
	list<int> n;
	n.push_back(50);
	n.push_back(90);
	n.push_back(10);
	n.push_back(30);
	for (auto it = n.begin(); it != n.end(); it++){
		cout << *it << " ";
	}
	cout<<"rever song";
	n.reverse();
	for (auto it = n.begin(); it != n.end(); it++){
		cout << *it << " ";
	}
//	for(auto &kv:lists)	cout<<kv<<" ";
//	lists.clear();
//	cout<<"asdasd";
//	for(auto &kv:lists)	cout<<kv<<" ";
//	std::list<int>::iterator iter = std::prev(n.end());
//	cout<<*iter;
//	for (iter = n.rbegin(); iter != n.rend(); iter++) {
//			//test.push(*iter);
//        	cout<<*iter<<" ";
//        	//n.erase(iter);
//	}
	
	//list<int>::iterator it;    
//	for (auto itr = n.begin(); itr != n.end(); itr++)
//	{
//	 	itr=n.erase(itr);
////	 	n.pop_back();
//	}
//    cout<<"\nSau do";
//    for (auto it = n.rbegin(); it != n.rend(); it++){
//		cout << *it << " ";
//
//	 }
//	while(n.size()){
//		test.push(*iter);
//		n.erase(iter);
//	}
	//cout<<"\n"<<n.size();
}
