#include <iostream>

using namespace std;

class Btree{
	public:
		Btree() : root(NULL){}
		void Add(const string& n, int a){root = AddH(root, n, a);}
		void Print(){PrintH(root);}
	private:
		struct Node{
			string name;
			int age;
			Node* left;
			Node* right;
			Node(const string& n, int a) : name(n), age(a), left(NULL), right(NULL){}
		};
		Node* root;

		Node* AddH(Node* np, const string& n, int a);
		void PrintH(Node* np);
};

Btree::Node* Btree::AddH(Node* np, const string& n, int a){
	
	if(np == NULL)
		np =  new Node(n, a);
	else if(np -> name == n)
		cout << "Name already exists" << endl;
	else if(n < np -> name)
		np -> left = AddH(np -> left, n, a);
	else
		np -> right = AddH(np -> right, n, a);
	return np;
}

void Btree::PrintH(Node* np){

	if(np == NULL)
		return;
	PrintH(np -> left);
	cout << np -> name << " " << np -> age << endl;
	PrintH(np -> right);
}

int main(){

	Btree b;

	b.Add("David", 45);
	b.Add("Carey", 38);
	b.Add("Cecil", 20);
	b.Add("Judea", 77);
	b.Add("Richard", 58);
	b.Add("David", 20);

	b.Print();

	return 0;
}
