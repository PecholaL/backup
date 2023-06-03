#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

int LCS_1(const string &str1, const string &str2, string &lcs)
{
    int m = str1.length();
    int n = str2.length();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    for(int i=1; i<=m; ++i)
    {
        for(int j=1; j<=n; ++j)
        {
            if(str1[i-1] == str2[j-1])
            {
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    int length = dp[m][n];
    lcs.resize(length);
    int i = m, j = n;
    while(i>0 && j>0)
    {
        if(str1[i-1] == str2[j-1])
        {
            lcs[length-1] = str1[i-1];
            --i;
            --j;
            --length;
        }
        else if(dp[i-1][j] >= dp[i][j-1])
        {
            --i;
        }
        else
        {
            --j;
        }
    }
    return dp[m][n];
}

// Space 2*O(min(m,n))
int LCS_2(const string &str1, const string &str2)
{
    int m = str1.length();
    int n = str2.length();
    const string *s, *l;
    if(m<n)
    {
    	s = &str1;
    	l = &str2;
    }
    else
    {
    	s = &str2;
    	l = &str1;
    }
    vector<vector<int>> dp(2, vector<int>(min(m, n), 0));
    int flag = 1;
    for(int i=0; i<max(m, n); ++i)
    {
        for(int j=0; j<min(m, n); ++j)
        {
            if((*l)[i] == (*s)[j])
            {
            	if(j == 0)
            	{dp[flag][j] = 1;}
            	else
            	{dp[flag][j] = dp[(flag+1)%2][j-1] + 1;}
            }
            else
            {
                if(j == 0)
                {dp[flag][j] = dp[(flag+1)%2][j];}
                else
                {dp[flag][j] = max(dp[(flag+1)%2][j], dp[flag][j-1]);}
            }
        }
        flag = (flag+1)%2;
    }
    return dp[(flag+1)%2][min(m, n)-1];
}

// Space O(min(m,n))
int LCS_3(const string &str1, const string &str2)
{
    int m = str1.length();
    int n = str2.length();
    const string *s, *l;
    if(m<n)
    {
    	s = &str1;
    	l = &str2;
    }
    else
    {
    	s = &str2;
    	l = &str1;
    }
    vector<int> dp(min(m, n), 0);
    int tmp = -1, last = -1;
    for(int i=0; i<max(m, n); ++i)
    {
        for (int j=0; j<min(m, n); ++j)
        {
            last = tmp;
            tmp = dp[j];
            if ((*l)[i] == (*s)[j])
            {
            	if(j==0)
            	{dp[j] = 1;}
            	else
                {dp[j] = last + 1;}
            }
            else
            {
            	if(j==0)
            	{dp[j] = dp[j];}
                else
                {dp[j] = max(dp[j-1], dp[j]);}
            }
        }
    }
    return dp[min(m, n)-1];
}

int main()
{
    string str1;
    string str2;
    string lcs;
    while(true)
    {
	    cout<<"Enter two strings: ";
		cin>>str1;
		if(!str1.compare(".quit"))
		{break;}
		cin>>str2;
	    int length_1 = LCS_1(str1, str2, lcs);
	    int length_2 = LCS_2(str1, str2);
	    int length_3 = LCS_3(str1, str2);
	    cout << "LCS:                        " << lcs << "\n"
	         << "LCS length (O(m*n)):        " << length_1 << "\n"
	         << "LCS length (2*O(min(m,n))): " << length_2 << "\n" 
	         << "LCS length (O(min(m,n))):   " << length_3 <<endl;
	}
    return 0;
}
