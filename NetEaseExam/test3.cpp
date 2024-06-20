#include <iostream>
#include <math.h>
using namespace std;

int distance(int, int, int, int);
int impact_num(int, int[][3], int, int);

int main() {
    int n;
    int info[n][3]; // 0 for x, 1 for y, 2 for r
    int q;
    int query[q][2]; // 0 for x, 1 for y
    cin >> n;
    for (int i=0; i<n; i++)
    {
    	cin >> info[i][0] >> info[i][1] >> info[i][2];
    }
    cin >> q;
    for (int i=0; i<q; i++)
    {
    	cin >> query[i][0] >> query[i][1];
    }
    
    for (int i=0; i<q; i++)
    {
    	cout << impact_num(n, info, query[i][0], query[i][1]) << endl;
    }
}

int distance(int x, int y, int x_, int y_)
{
	return abs(x_-x)>abs(y-y_)?abs(x-x_):abs(y-y_);
}

int impact_num(int n, int info[][3], int x, int y)
{
	int res = 0;
	for (int i=0; i<n; i++)
	{
		if (distance(info[i][0], info[i][1], x, y) <= info[i][2])
		{
			res++;
		}
	}
	return res;
}