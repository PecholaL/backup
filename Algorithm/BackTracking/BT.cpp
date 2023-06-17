// Back Tracking 解决任务调度问题
#include<fstream>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
 
int MaxNum=0x3f3f3f3f;
int n;
int k;
vector<int> task;
vector<int> machineTime;
vector<vector<int>> scheduleTable;
vector<vector<int>> bestSchedule;

/* 含两个剪枝条件,均为大于当前最大机器运行时间则进行剪枝
 * 参数x为已调度的任务数,y为目前最大机器运行时间
 */
void DFS(int x,int y)
{
	// 超过当前时间上限则剪枝
	if(y>MaxNum)
	{return;}
	// 任务调度完成
	if(x==n)
	{
		if(y<MaxNum)
		{
			MaxNum=y;
			bestSchedule.clear();
			bestSchedule.assign(scheduleTable.begin(), scheduleTable.end());
		}
		return;
	}
	for(int i=0; i<k; i++)
	{
		// 任务x放入机器i造成机器i的时间超过当前时间上限则剪枝
		if(machineTime[i]+task[x] > MaxNum)
		{continue;}
		// 前一台机器已考虑过当前情形
		if(i>0 && machineTime[i]==machineTime[i-1])
		{continue;}
		// 把任务x放入机器i执行 
		machineTime[i] = machineTime[i]+task[x];
		scheduleTable[i].push_back(task[x]);
		DFS(x+1, max(y, machineTime[i]));
		// 回溯
		machineTime[i] = machineTime[i]-task[x];
		scheduleTable[i].pop_back();
	}
	return;
}

int main(int argc, char *argv[])
{
	string path = argv[1];
	try
	{
		ifstream f(path, ios::in);
		if(f.fail())
		{
			string err = "Cannot Open the File: " + path;
			throw invalid_argument(err);
		}
		f>>n>>k;
		int i = 0;
		int tmp = 0;
		while(!f.eof() && i<n)
		{
			f>>tmp;
			task.push_back(tmp);
			++i;
		}
		for(i=0; i<k; i++)
		{
			machineTime.push_back(0);
			vector<int> tmp;
			scheduleTable.push_back(tmp);
		}
	}
	catch(const exception& e)
	{
		cerr<<e.what()<<endl;
	}
	
	DFS(0,0);
	cout<<"Total time: "<<MaxNum<<endl;
	for(int i=0; i<k; i++)
	{
		cout<<"Machine "<<i<<" :";
		for(auto iter=bestSchedule[i].begin(); iter!=bestSchedule[i].end(); iter++)
		{
			cout<<" "<<*iter;
		}
		cout<<endl;
	}
	return 0;
} 
