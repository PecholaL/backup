// BFS
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<time.h>

using namespace std;

// bool visitedAll(unordered_map<int, bool>);

// 邻接表表示的图类
class Graph
{
private:
    unordered_map<int, vector<int>> adjacencyList; // 邻接表

public:
    // 添加边
    void addEdge(int source, int destination)
    {
        adjacencyList[source].push_back(destination);
        if(adjacencyList.find(destination) == adjacencyList.end())
        {
            adjacencyList[destination] = {};
        }
    }
	
    // BFS遍历
    void bfsTraversal(int startVertex)
    {
    	int counter = 0;
        // 初始化访问数组和队列
        unordered_map<int, bool> visited;
        for(auto kv : adjacencyList)
        {
        	visited[kv.first] = false;
        }
        queue<int> q;
		
        // 将起始顶点入队并标记为已访问
        q.push(startVertex);
        visited[startVertex] = true;
		
        cout << "BFS Traversal: " << endl;
		
        while(!q.empty())
        {
            // 出队并访问顶点
            int currentVertex = q.front();
            cout << currentVertex << " ";
            ++counter;
            q.pop();
			
            // 将当前顶点的未访问邻接顶点入队并标记为已访问
            for(int neighbor : adjacencyList[currentVertex])
            {
                if(!visited[neighbor])
                {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
            
            if(q.empty())
            {
                // 找到未遍历到的点
                for(auto kv : visited)
                {
                    if(!kv.second)
                    {
                        q.push(kv.first);
                        visited[kv.first] = true;
                        break;
                    }
                }
            }
        }
        cout << "\nVisited vertex quantity: " << counter << endl;
    }
};

// bool visitedAll(unordered_map<int, bool> visited)
// {
//     for(auto kv : visited)
//     {
//         if(!kv.second)
//         {return false;}
//     }
//     return true;
// }

int main()
{
    ifstream file("twitter_small.txt");
	
    if(!file)
    {
        cerr << "Failed to open the file." << endl;
        return 1;
    }
	
    Graph graph;
    string line;
	
	int edgeCounter = 0;
    while(getline(file, line))
    {
        int source, destination;
        istringstream iss(line);
        if(iss >> source >> destination)
        {
        	++edgeCounter;
            graph.addEdge(source, destination);
        }
    }
    // cout << "Edge quantity: " << edgeCounter << endl;
	
    file.close();
	
	clock_t startTime, endTime;
	
	while(true)
	{
		int start;
		cout << "Please enter the start vertex: ";
		cin >> start;
		startTime = clock();
    	graph.bfsTraversal(start);
    	endTime = clock();
    	cout << "Time: " << (double)(endTime-startTime)/CLOCKS_PER_SEC << endl;
    }

    return 0;
}
