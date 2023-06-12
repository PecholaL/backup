// Huffman Code
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<map>
#include<queue>
#include<cmath>

using namespace std;

map<char, string> huffmanCodeBook;
string inputPath = "original.txt";
string outputPath = "table.txt";

struct Node
{
	char symbol;
	int frequency;
	Node *left;
	Node *right;
	
	Node(char s, int f): 
		symbol(s), frequency(f), left(nullptr), right(nullptr){}
};

struct NodesFrequencyCompare
{
	bool operator()(const Node *node1, const Node *node2)
	{
		return node1->frequency > node2->frequency;
	}
};

// 递归调用该函数根据哈夫曼树生成编码
void generateHuffmanCode(Node *currentNode, string code)
{
	if(currentNode==nullptr)
	{return;}
	if(currentNode->left==nullptr && currentNode->right==nullptr)
	{
		huffmanCodeBook[currentNode->symbol] = code;
		return;
	}
	generateHuffmanCode(currentNode->left, code+"0");
	generateHuffmanCode(currentNode->right, code+"1");
}

// 构建哈夫曼树并生成编码
void buildHuffmanTree(map<char, int> &counter)
{
	priority_queue<Node*, vector<Node*>, NodesFrequencyCompare> q;
	for(const auto &pair : counter)
	{
		Node *newNode = new Node(pair.first, pair.second);
		q.push(newNode);
	}
	// 每次将频率最低的两个结点整合为一个结点并以"$"标识
	while(q.size()>1)
	{
		Node *min1 = q.top();
		q.pop();
		Node *min2 = q.top();
		q.pop();
		Node *parent = new Node('$', min1->frequency + min2->frequency);
		parent->left = min1;
		parent->right = min2;
		q.push(parent);
	}
	// 生成哈夫曼编码
	Node *root = q.top();
	generateHuffmanCode(root, "");
	delete root;
}

float compressionRate(map<char, int> &counter, map<char, string> &codeBook)
{
	int original = 0;
	int compression = 0;
	int fixedLength = ceil(log2(counter.size()));
	for(const auto &pair : counter)
	{
		original += pair.second*fixedLength;
	}
	for(const auto &pair : codeBook)
	{
		compression += counter[pair.first]*pair.second.length();
	}
	if(original==0)
	{return 0;}
	return static_cast<float>(compression)/original;
}

int main()
{
	ifstream inFile(inputPath);
	if(!inFile.is_open())
	{
		cerr << "Cannot Open the Input File. " << endl;
		return 1;
	}
	
	map<char, int> counter;
	char c;
	while(inFile.get(c))
	{
		if(c>=33 && c<=126)
		{
			++counter[c];
		}
	}
	inFile.close();
	
	buildHuffmanTree(counter);
	
	/* test
	cout << "字符\t" << "出现频率\t" << "编码\n";
	for(const auto &pair : huffmanCodeBook)
	{
		cout << pair.first << "\t" << counter[pair.first]
		     << "\t" << pair.second << endl;
	}
	*/
	
	ofstream outFile(outputPath);
	if(!outFile.is_open())
	{
		cerr << "Cannot Open the Output File. " << endl;
		return 1;
	}
	outFile << "字符\t" << "出现频率\t" << "编码\n";
	for(const auto &pair : huffmanCodeBook)
	{
		outFile << pair.first << "\t" << counter[pair.first]
		     << "\t" << pair.second << endl;
	}
	outFile.close();
	
	cout << "压缩率: " << compressionRate(counter, huffmanCodeBook) << endl;
	
	
	return 0;
}
