//
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<exception>

using namespace std;

struct TNode
{
	TNode(int key)
	{
		this->key = key;
	}
	bool color; // T for red, F for black
	int key;
	TNode* left;
	TNode* right;
	TNode* parent;
};

struct Tree
{
	TNode* root;
	TNode* nil;
};

void LEFT_ROTATE(Tree* &T, TNode* x)
{
	TNode* y;
 
	y = x->right;
	x->right = y->left;
	if(y->left!=T->nil)
		y->left->parent = x;
	y->parent =  x->parent;
	if(x->parent==T->nil)
		T->root = y;
	else if(x==x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void RIGHT_ROTATE(Tree* &T, TNode* y)
{
	TNode* x;
 
	x = y->left;
	y->left = x->right;
	if(x->right!=T->nil)
		x->right->parent = y;
	x->parent = y->parent;
	if(y->parent==T->nil)
		T->root = x;
	else if(y==y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;
	x->right = y;
	y->parent = x;
}

void RB_INSERT_FIXUP(Tree* &T, TNode* z)
{
	TNode* y;
 
	while(z->parent->color==true)
	{
		if(z->parent==z->parent->parent->left)
		{
			y = z->parent->parent->right;
			if(y->color==true)
			{                                        //case1
				z->parent->color = false;
				y->color = false;
				z->parent->parent->color = true;
				z = z->parent->parent;
				cout<<"case 1: 父结点为祖父结点的左孩子，叔结点为红色"<<endl;
			}
			else{                                       
				if(z==z->parent->right)
				{                                     //case2
					z = z->parent;
					LEFT_ROTATE(T, z);
					cout<<"case 2: 父结点为祖父结点的左孩子，叔结点为黑色，当前结点为右孩子"<<endl;
				}
				z->parent->color = false;             //case3
				z->parent->parent->color = true;
				RIGHT_ROTATE(T, z->parent->parent);
				cout<<"case 3: 父结点为祖父结点的左孩子，叔结点为黑色，当前结点为左孩子"<<endl;
			}
		}
		else
		{
			y = z->parent->parent->left;
			if(y->color==true)
			{						 //case4
				z->parent->color = false;
				y->color = false;
				z->parent->parent->color = true;
				z = z->parent->parent;
				cout<<"case 4: 父结点为祖父结点的右孩子，叔结点为红色"<<endl;
			}
			else
			{
				if(z==z->parent->left)
				{                                     //case5
					z = z->parent;
					RIGHT_ROTATE(T, z);
					cout<<"case 5: 父结点为祖父结点的左孩子，叔结点为黑色，当前结点为左孩子"<<endl;
				}
				z->parent->color = false;             //case6
				z->parent->parent->color = true;
				LEFT_ROTATE(T, z->parent->parent);
				cout<<"case 6: 父结点为祖父结点的左孩子，叔结点为黑色，当前结点为右孩子"<<endl;
			}
		}
	}
	T->root->color = false;
}

void RB_INSERT(Tree* &T,TNode* z)
{
	TNode* x = T->root;
	TNode* y = T->nil;
	while(x!=T->nil)
	{
		y = x;
		if(z->key<x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if(y==T->nil)
		T->root = z;
	else if(z->key<y->key)
		y->left = z;
	else
		y->right = z;
	z->left = T->nil;
	z->right = T->nil;
	z->color = true;
	RB_INSERT_FIXUP(T, z);
}

int main()
{
	vector<TNode> nodes;
	string path = "insert.txt";
	try
	{
		ifstream f(path, ios::in);
		if(f.fail())
		{
			string err = "Cannot Open the File: " + path;
			throw invalid_argument(err);
		}
		int N = 0;
		int i = 0;
		int key = 0;
		f>>N;
		while(!f.eof() && i<N)
		{
			f>>key;
			TNode tmp = TNode(key);
			nodes.push_back(tmp);
			++i;
		}
	}
	catch(const exception &e)
	{
		cerr<<e.what()<<endl;
	}
	
	Tree* T = new Tree();
	T->nil = new TNode(0);
	T->nil->color = false;
	T->root = T->nil;
	
	for(auto iter = nodes.begin(); iter!=nodes.end(); iter++)
	{
		cout<<"Insert "<<(*iter).key<<endl;
		TNode* ptr = &(*iter);
		RB_INSERT(T, ptr);
	}
}


