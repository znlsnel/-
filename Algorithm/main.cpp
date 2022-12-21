#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int MAX = 1000000000;
int cost[8]; // 각 정점으로의 최소비용을 담을 예정
bool v[8];
int N = 8;

int countN = 0;

int g[8][8]
{
	{0, 2, 1, 1, MAX, MAX, MAX, MAX},
	{2, 0, MAX, 2, 4, MAX, MAX, 5},
	{1, MAX, 0, 2, MAX, 1, MAX, MAX},
	{1, 2, 2, 0, 1, 3, 2, MAX},
	{MAX, 4, MAX, 1, 0, MAX, 2, 3},
	{MAX, MAX, 1, 3, MAX, 0, 1, MAX},
	{MAX, MAX, MAX, 2, 2, 1, 0, 2},
	{MAX, 5, MAX, MAX, 3, MAX, 2, 0}
};



void dijkstra1(int start) 
{
	countN = 0;
	for (int i = 0; i < N; i++)
		cost[i] = g[start][i]; // 시작 노드에서부터 모든 정점으로의 비용을 등록

	for (int current = 0; current < N; current++)
	{
		for (int dest = 0; dest < N; dest++)
		{
			if (cost[dest] > cost[current] + g[current][dest])
				cost[dest] = cost[current] + g[current][dest];
			countN++;
		}  // 목표로하는 노드의 최소비용 = 현재 위치까지의 최소비용 + 현재 위치에서 목표 노드로의 비용
	}
} // countN = 64



int SmallIndex()
{
	int index = 0;
	int min = MAX; 

	for (int i = 0; i < N; i++)
	{
		if (v[i] == false && min > cost[i])
		{
			index = i;
			min = cost[i];
		}
	}

	return index;
}

void dijkstra2(int start)
{
	countN = 0;

	for (int i = 0; i < N; i++)
		cost[i] = g[start][i]; // 시작 노드에서부터 모든 정점으로의 비용을 등록

	v[start] = true;

	// 8번 -> 6번만 반복 ( 첫번째 노드, 마지막 노드를 제외 )
	for (int i = 0; i < N - 2; i++)
	{
		int current = SmallIndex();
		v[current] = true;

		for (int dest = 0; dest < N; dest++)
		{
			if (cost[dest] > cost[current] + g[current][dest])
				cost[dest] = cost[current] + g[current][dest];
			countN++;
		}  // 목표로하는 노드의 최소비용 = 현재 위치까지의 최소비용 + 현재 위치에서 목표 노드로의 비용
	}
} // countN = 48 (  + SamllIndex = 48 )


vector<pair<int, int>> vec[8];

void dijkstra3(int start) // E* logE + E
{
	countN = 0;
	cost[start] = 0;

	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(start, 0));

	while (!pq.empty())
	{
		int current = pq.top().second;
		int dist = -pq.top().first; // min Heap으로 만들기 위해서 이렇게 함
		pq.pop(); 

		if (cost[current] < dist) continue;
		for (int i = 0; i < vec[current].size(); i++)
		{
			int next = vec[current][i].second - 1;

			int nextDist = dist + vec[current][i].first;
			if (nextDist < cost[next])
			{
				cost[next] = nextDist;
				pq.push(make_pair(-nextDist, next));
			}
			countN++;
		}
	}

} // countN = 30 ( E*logE + E )

int main()
{
	
	dijkstra2(0); // 0 2 1 1 2 2 3 5
	for (int i = 0; i < N; i++)
		cout << cost[i] << " ";

	cout << "\n" << countN << "\n"; 
	
#pragma region Edge
	vec[0].push_back(make_pair(2, 2));
	vec[0].push_back(make_pair(1, 3));
	vec[0].push_back(make_pair(1, 4));

	vec[1].push_back(make_pair(2, 1));
	vec[1].push_back(make_pair(2, 4));
	vec[1].push_back(make_pair(4, 5));
	vec[1].push_back(make_pair(5, 8));

	vec[2].push_back(make_pair(1, 1));
	vec[2].push_back(make_pair(2, 4));
	vec[2].push_back(make_pair(1, 6));

	vec[3].push_back(make_pair(1, 1));
	vec[3].push_back(make_pair(2, 2));
	vec[3].push_back(make_pair(2, 3));
	vec[3].push_back(make_pair(1, 5));
	vec[3].push_back(make_pair(3, 6));
	vec[3].push_back(make_pair(2, 7));

	vec[4].push_back(make_pair(4, 2));
	vec[4].push_back(make_pair(1, 4));
	vec[4].push_back(make_pair(2, 7));
	vec[4].push_back(make_pair(3, 8));

	vec[5].push_back(make_pair(1, 3));
	vec[5].push_back(make_pair(3, 4));
	vec[5].push_back(make_pair(1, 7));

	vec[6].push_back(make_pair(2, 4));
	vec[6].push_back(make_pair(2, 5));
	vec[6].push_back(make_pair(1, 6));
	vec[6].push_back(make_pair(2, 8));

	vec[7].push_back(make_pair(5, 2));
	vec[7].push_back(make_pair(3, 5));
	vec[7].push_back(make_pair(2, 7));
#pragma endregion

	fill(cost, cost + N, MAX);

	dijkstra3(0);
	for (int i = 0; i < N; i++)
		cout << cost[i] << " ";

	cout << "\n" << countN << "\n";



	
	return 0;
}