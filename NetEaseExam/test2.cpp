#include <iostream>
using namespace std;

int findmax(int n, int []);

int main() {
    int n, A, B, C;
    cin >> n >> A >> B >> C;
    int costa[n];
    int costb[n];
    int costc[n];
    int val[n];
    for (int i=0; i<n; i++)
    {
    	cin >> costa[i] >> costb[i] >> costc[i] >> val[i];
    }
    
    int total_val = 0;
    while (A>=0 && B>=0 && C>=0)
    {
        int cc = findmax(n, val);
        if (val[cc]==0)
        {
            cout << total_val;
            return 0;
        }
        if (costa[cc]<=A && costb[cc]<=B && costc[cc]<=C)
        {
            total_val += val[cc];
            A -= costa[cc];
            B -= costb[cc];
            C -= costc[cc];
        }
        val[cc] = 0;
    }
    cout << total_val;
    return 0;
}

int findmax(int n, int val[])
{
    int maxVal = 0;
    int res = 0;
    for (int i=0; i<n; i++)
    {
        if (val[i]>maxVal)
        {
            res = i;
            maxVal = val[i];
        }
    }
    return res;
}




