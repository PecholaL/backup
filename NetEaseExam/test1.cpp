#include <iostream>
using namespace std;

int one_attack(int[], int[], int[], int[], int, int);

int main() {
    int YI_att[5];
    int YI_life[5];
    int ct_att[5];
    int ct_life[5];

    for (int i=0; i<5; i++) {
    	cin >> YI_att[i];
    }
    for (int i=0; i<5; i++) {
    	cin >> YI_life[i];
    }
    for (int i=0; i<5; i++) {
    	cin >> ct_att[i];
    }
    for (int i=0; i<5; i++) {
    	cin >> ct_life[i];
    }
    
    int a_counter = 0;
    int b_counter = 0;
    
    while (a_counter<5 && b_counter<5)
    {
    	int res = one_attack(YI_att, YI_life, ct_att, ct_life, a_counter, b_counter);
    	if (res == -1)
    	{
    		b_counter++;
    		if (b_counter==5)
    		{
    			break;
    		}
    	}
    	int res_back = one_attack(ct_att, ct_life, YI_att, YI_life, b_counter, a_counter);
    	if (res_back == -1)
    	{
    		a_counter++;
    		if (a_counter==5)
    		{
    			break;
    		}
    	}
    }
    if (a_counter==5)
    {
    	cout<<"lose\n"<<5-b_counter<<endl;
    }
    else
    {
    	cout<<"win\n"<<5-a_counter<<endl;
    }    
}

// a_no attacks b_no
// -1 for killed
int one_attack(int a_att[], int a_life[], int b_att[], int b_life[], int a_no, int b_no)
{
	b_life[b_no] -= a_att[a_no];
	if (b_life[b_no]<=0)
	{
		return -1;
	}
	return 0;
}







