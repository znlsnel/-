#include <iostream>
using namespace std;
int N = 8;
int MAX = 1000000000;
int cost[8]; // 각 정점으로의 최소비용을 담을 예정

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

void dijkstra(int start)
{
	for (int i = 0; i < N; i++)
		cost[i] = g[start][i]; // 시작 노드에서부터 모든 정점으로의 비용을 등록

	for (int current = 0; current < N; current++)
	{
		for (int dest = 0; dest < N; dest++)
		{
			if (cost[dest] > cost[current] + g[current][dest])
				cost[dest] = cost[current] + g[current][dest];
		}  // 목표로하는 노드의 최소비용 = 현재 위치까지의 최소비용 + 현재 위치에서 목표 노드로의 비용
	}
}

int main()
{
	dijkstra(1);

	for (int i = 0; i < N; i++)
		cout << cost[i] << " ";

	return 0;
}