// 快速排序
// 结合插入排序进行优化

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>
#include<exception>
#include<time.h>
using namespace std;

string input = "data.txt";
string output = "res.txt";
string outputStd = "sort.txt";
vector<int> loadData(string);
void quickSort(vector<int>&, int, int);
int randomizedPartition(vector<int>&, int, int);
int partition(vector<int>&, int, int);
void insertSort(vector<int>&, int, int);
void QSwithIS(vector<int>&, int, int);

int main()
{
	//-------------------------------input
	vector<int> data;
	try
	{
		data = loadData(input);
	}
	catch(const exception& e)
	{
		cerr<<e.what()<<endl;
	}
	vector<int> data2(data);
	vector<int> data3(data);
	
	//---------------------------------sort()
	auto b = data2.begin();
	auto e = data2.end();
	clock_t startTime = clock();
	sort(b, e);
	clock_t endTime = clock();
	cout<<"sort() time cost: "<< (double)(endTime-startTime)/CLOCKS_PER_SEC << endl;
	
	//---------------------------------quickSort()
	startTime = clock();
	quickSort(data, 0, (int)data.size()-1);
	endTime = clock();
	cout<<"quickSort() time cost: "<< (double)(endTime-startTime)/CLOCKS_PER_SEC <<endl;
	
	//---------------------------------QSwithIS()
	startTime = clock();
	QSwithIS(data3, 0, (int)data3.size()-1);
	endTime = clock();
	cout<<"QSwithIS() time cost: "<< (double)(endTime-startTime)/CLOCKS_PER_SEC <<endl;
	
	//----------------------------------output
	try
	{
		ofstream f(output, ios::out);
		auto iter = data3.begin();
		for(;iter!=data3.end();++iter)
		{
			f<<*iter<<' ';
		}
		ofstream f2(outputStd, ios::out);
		auto iter2 = data2.begin();
		for(;iter2!=data2.end();++iter2)
		{
			f2<<*iter2<<' ';
		}
	}
	catch(const exception& e2)
	{
		cerr<<e2.what()<<endl;
	}
	
}

vector<int> loadData(string path)
{
	ifstream f(path, ios::in);
	if(!f.is_open())
	{
		string err = "Cannot Open the File: " + path;
		throw invalid_argument(err);
	}
	int N = 0;
	int i = 0;
	f>>N;
	vector<int> data(N);
	while(!f.eof() && i<N)
	{
		f>>data[i];
		++i;
	}
	return data;
}

void quickSort(vector<int>& data, int p, int r)
{
	if(p<r)
	{
		// 经测试对于该组数据不使用随机划分耗时更少
		//int q = randomizedPartition(data, p, r);
		int q = partition(data, p, r);
		quickSort(data, p, q-1);
		quickSort(data, q+1, r);
	}
}

void QSwithIS(vector<int>& data, int p, int r)
{
	if(p<r)
	{
		// 当待排序列长度小于一定值时调用插入排序可有效加快速度
		if(r-p<3)
		{
			insertSort(data, p, r);
		}
		int q = partition(data, p, r);
		QSwithIS(data, p, q-1);
		QSwithIS(data, q+1, r);
	}
}

int randomizedPartition(vector<int>& data, int p, int r)
{
	int i = ((int)rand()%(r-p+1))+p;
	swap(data[i], data[r]);
	return partition(data, p, r);
}

int partition(vector<int>& data, int p, int r)
{
	int x = data[r];
	int i = p-1;
	for(int j=p; j<r; j++)
	{
		if(data[j]<=x)
		{
			++i;
			swap(data[i], data[j]);
		}
	}
	swap(data[i+1], data[r]);
	return i+1;
}

void insertSort(vector<int>& data, int p, int r)
{
	for(int i=p+1; i<=r; ++i)
	{
		int key = data[i];
		int j = i-1;
		while(j>=p && data[j]>key)
		{
			data[j+1] = data[j];
			--j;
		}
		data[j+1] = key;
	}
}
