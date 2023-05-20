// 寻找平面上的最近点对
// 分治思想

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<exception>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<time.h>
using namespace std;

string input = "data.txt";
struct point
{
	int index;
	float x;
	float y;
};
vector<point> loadData(string);
float distance(const point &, const point &);
bool cmp_x(const point &, const point &);
bool cmp_y(const point &, const point &);
float findClosest(vector<point> &, point[]);
float merge(vector<point> &, float, int, point[]);

int main()
{
	//-------------------------------input
	vector<point> data;
	try
	{
		data = loadData(input);
	}
	catch(const exception& e)
	{
		cerr<<e.what()<<endl;
	}
	cout<<setiosflags(ios::fixed)<<setprecision(3);
	cout<<"Get "<<data.size()<<" points. "<<endl;
	auto startTime = clock();
	auto endTime = clock();
	//-------------------------------findClosest
	sort(data.begin(), data.end(), cmp_x);
	point res[2];
	startTime = clock();
	float d = findClosest(data, res);
	endTime = clock();
	cout<<"The closest pair of points: ("
		<<res[0].x<<", "<<res[0].y
		<<") and ("
		<<res[1].x<<", "<<res[1].y
		<<"), distance = "<<d<<endl;
	cout<<"TIME SPENT "<< (double)(endTime-startTime)/CLOCKS_PER_SEC << endl;
	//-------------------------------bruteForce
	float minD = 99999999;
	cout<<"**********BruteForce**********"<<endl;
	point resBF[2];
	startTime = clock();
	for(auto i=data.begin(); i!=data.end(); i++)
	{
		for(auto j=i+1; j!=data.end(); j++)
		{
			float d = distance(*i, *j);
			if(d<minD)
			{
				resBF[0] = *i;
				resBF[1] = *j;
				minD = d;
			}
		}
	}
	endTime = clock();
	cout<<"The closest pair of points: ("
		<<resBF[0].x<<", "<<resBF[0].y
		<<") and ("
		<<resBF[1].x<<", "<<resBF[1].y
		<<"), distance = "<<minD<<endl;
	cout<<"TIME SPENT "<< (double)(endTime-startTime)/CLOCKS_PER_SEC << endl;
}

vector<point> loadData(string path)
{
	ifstream f(path, ios::in);
	if(!f.is_open())
	{
		string err = "Cannot Open the File: " + path;
		throw invalid_argument(err);
	}
	vector<point> data;
	int index = 0;
	float x = 0;
	float y = 0;
	while(!f.eof())
	{
		f >> index;
		if(f)
		{
			f >> x >> y;
			data.push_back({index, x, y});
		}
	}
	f.close();
	return data;
}

float distance(const point &A, const point &B)
{
	return sqrt(pow(A.x-B.x, 2) + pow(A.y-B.y, 2));
}

bool cmp_x(const point &A, const point &B)
{
	return A.x<B.x;
}

bool cmp_y(const point &A, const point &B)
{
	return A.y<B.y;
}

float findClosest(vector<point> &points, point record[])
{
	if(points.size() == 2)
	{
		record[0] = points[0];
		record[1] = points[1];
		return distance(points[0], points[1]);
	}
	if(points.size() == 3)
	{
		float d01 = distance(points[0], points[1]);
		float d02 = distance(points[0], points[2]);
		float d12 = distance(points[1], points[2]);
		if(d01<d02 && d01<d12)
		{
			record[0] = points[0];
			record[1] = points[1];
			return d01;
		}
		else if(d02<d01 && d02<d12)
		{
			record[0] = points[0];
			record[1] = points[2];
			return d02;
		}
		else
		{
			record[0] = points[1];
			record[1] = points[2];
			return d12;
		}
	}
	int mid = (points.size() >> 1) - 1;
	float d1, d2, d;
	vector<point> left(mid+1), right(points.size()-mid-1);
	copy(points.begin(), points.begin()+mid+1, left.begin());
	copy(points.begin()+mid+1, points.end(), right.begin());
	
	d1 = findClosest(left, record);
	point tmp[2];
	tmp[0] = record[0];
	tmp[1] = record[1];
	d2 = findClosest(right, record);
	if(d1<d2)
	{
		d = d1;
		record[0] = tmp[0];
		record[1] = tmp[1];
	}
	else
	{
		d = d2;
	}
	
	float dm = merge(points, d, mid, record);
	return dm;
}

float merge(vector<point> &points, float d, int mid, point record[])
{
	vector<point> left, right;
	for(int i=0; i<points.size(); ++i)
	{
		/* 分别将第mid个点两侧d范围内的点放入left和right中
		 * 两个集合之间的最近点对只有可能出现在这个范围中
		 */
		if(points[i].x-points[mid].x <= 0 && points[mid].x-points[i].x < d)
			{left.push_back(points[i]);}
		else if(points[i].x-points[mid].x > 0 && points[i].x-points[mid].x < d)
			{right.push_back(points[i]);}
	}
	/* 依据y坐标对right集合中的点进行排序
	 * 然后遍历left集合中的点
	 * 与right集合中纵坐标最接近的几个点计算距离
	 */
	sort(right.begin(), right.end(), cmp_y);
	for(int i=0; i<left.size(); ++i)
	{
		int near = 0;
		for(near=0; near<right.size() && left[i].y>right[near].y; ++near);
		near = near-4<0 ? 0 : near-4;
		for(int j=0; j<7 && near+j<right.size(); ++j)
		{
			if(distance(left[i], right[near+j]) < d)
			{
				record[0] = left[i];
				record[1] = right[near+j];
				d = distance(left[i], right[near+j]);
			}
		}
	}
	return d;
}




