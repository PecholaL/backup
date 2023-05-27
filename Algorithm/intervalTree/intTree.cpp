// Interval Tree & Search
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<exception>
#include<algorithm>
using namespace std;

struct interval
{
	interval(int low, int high)
	{
		this->low = low;
		this->high = high;
	}
	interval()
	{
		this->low = 0;
		this->high = 0;
	}
	int low;
	int high;
};
struct TNode
{
	TNode(interval i)
	{
		this->i.low = i.low;
		this->i.high = i.high;
	}
	TNode()
	{
		this->i.low = 0;
		this->i.high = 0;
	}
	bool color; // T for red, F for black
	interval i;
	int max;
	TNode* left;
	TNode* right;
	TNode* parent;
};
struct Tree
{
	TNode* root;
	TNode* nil;
};
string path = "insert.txt";
vector<interval> intervals;
vector<TNode> nodes;
inline bool overlap(interval &a, interval &b)
{return a.low<=b.high && b.low<=a.high;}
void LEFT_ROTATE(Tree* &, TNode*);
void LEFT_ROTATE(Tree* &, TNode*);
void INTERVAL_INSERT_FIXUP(Tree* &, TNode*);
void INTERVAL_INSERT(Tree* &, TNode*);
TNode* INTERVAL_SEARCH(Tree* &, interval &);


int main()
{
//__________________________________________________get data
	try
	{
		ifstream f(path, ios::in);
		if(f.fail())
		{
			string err = "Cannot Open the File: " + path;
			throw invalid_argument(err);
		}
		int N = 0;
		int i =0;
		int tmpLow;
		int tmpHigh;
		f>>N;
		while(!f.eof() && i<N)
		{
			f>>tmpLow>>tmpHigh;
			interval tmpI(tmpLow, tmpHigh);
			TNode tmpTN(tmpI);
			nodes.push_back(tmpTN);
			++i;
		}
	}
	catch(const exception& e)
	{
		cerr<<e.what()<<endl;
	}
//_____________________________________________________insert
	Tree* T = new Tree();
	T->nil = new TNode();
	T->nil->color = false;
	T->root = T->nil;
	for(auto iter = nodes.begin(); iter!=nodes.end(); ++iter)
	{
		cout<<"Insert ["<<(*iter).i.low<<", "<<(*iter).i.high<<"] "<<endl;
		TNode* ptr = &(*iter);
		INTERVAL_INSERT(T, ptr);
	}
	cout<<"Insert Completed! "<<endl;
//_____________________________________________________search
	string para1, para2;
	int low, high;
	while(true)
	{
		cout<<"Please enter the interval(format: low high): ";
		cin>>para1>>para2;
		try
		{
			low = stoi(para1);
			high = stoi(para2);
			if(low>high)
			{
				cout<<"Unexpected Interval!"<<endl;
				continue;
			}
			interval targetInt(low, high);
			TNode* res = INTERVAL_SEARCH(T, targetInt);
			if(res!=T->nil)
				cout<<"Found "<<res->i.low<<", "<<res->i.high<<endl;
			else
				cout<<"Not Found"<<endl;
		}
		catch(const exception& e)
		{
			cerr<<e.what()<<endl;
			break;
		}
	} //end of while
}// end of main()


//____________________________________________________________

void LEFT_ROTATE(Tree* &T, TNode* x)
{
	TNode* y;
	y = x->right;
	x->right = y->left;
	if(y->left!=T->nil)
		y->left->parent = x;
	y->parent = x->parent;
	if(x->parent==T->nil)
		T->root = y;
	else if(x==x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
	// 维护附加信息
	y->max = x->max;
	x->max = max(max(x->i.high, x->left->max), x->right->max);
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
	// 维护附加信息
	x->max = y->max;
	y->max = max(max(y->i.high, y->left->max), y->right->max);
}

void INTERVAL_INSERT_FIXUP(Tree* &T, TNode* z)
{
	TNode* y;
	while(z->parent->color==true)
	{
		if(z->parent==z->parent->parent->left)
		{
			y = z->parent->parent->right;
			if(y->color==true)
			{
				z->parent->color = false;
				y->color = false;
				z->parent->parent->color = true;
				z = z->parent->parent;
			}
			else{                                       
				if(z==z->parent->right)
				{
					z = z->parent;
					LEFT_ROTATE(T, z);
				}
				z->parent->color = false;
				z->parent->parent->color = true;
				RIGHT_ROTATE(T, z->parent->parent);
			}
		}
		else
		{
			y = z->parent->parent->left;
			if(y->color==true)
			{
				z->parent->color = false;
				y->color = false;
				z->parent->parent->color = true;
				z = z->parent->parent;
			}
			else
			{
				if(z==z->parent->left)
				{
					z = z->parent;
					RIGHT_ROTATE(T, z);
				}
				z->parent->color = false;
				z->parent->parent->color = true;
				LEFT_ROTATE(T, z->parent->parent);
			}
		}
	}
	T->root->color = false;
}

void INTERVAL_INSERT(Tree* &T,TNode* z)
{
	TNode* x = T->root;
	TNode* y = T->nil;
	z->max = z->i.high;
	while(x!=T->nil)
	{
		y = x;
		if(z->max>x->max)
			x->max = z->max;
		if(z->i.low<x->i.low)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if(y==T->nil)
		T->root = z;
	else if(z->i.low<y->i.low)
		y->left = z;
	else
		y->right = z;
	z->left = T->nil;
	z->right = T->nil;
	z->color = true;
	INTERVAL_INSERT_FIXUP(T, z);
}

TNode* INTERVAL_SEARCH(Tree* &T, interval &i)
{
	TNode* x = T->root;
	while(x!=T->nil && !overlap(i, x->i))
	{
		if(x->left!=T->nil && x->left->max>=i.low)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}
