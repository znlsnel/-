#include <iostream>
#include <vector>
#include <queue>

#define MAX 100
#define INF 100000000

using namespace std;

int n = 6, result;
int cost[MAX][MAX], flow[MAX][MAX], parent[MAX];
vector<int> a[MAX];
void maxFlow(int start, int end)
{
	while (1)
	{
		fill(parent, parent + MAX, -1);
		queue<int> q;
		q.push(start);
		while (!q.empty())
		{
			int curr = q.front();
			q.pop();
			for (int i = 0; i < a[curr].size(); i++)
			{
				int next = a[curr][i];
				if (cost[curr][next] - flow[curr][next] > 0 && parent[next] == -1)
				{
					q.push(next);
					parent[next] = curr;
					if (next == end) break;
				}
			}
		}
		// end와 연결된 간선이 없다는 뜻이기에 break;
		if (parent[end] == -1)
		{
			break;
		}
		int Minflow = INF;

		// 거꾸로 최소 유량 탐색
		for (int i = end; i != start; i = parent[i])
		{
			Minflow = min(Minflow, cost[parent[i]][i] - flow[parent[i]][i]);
		}

		// 최소 유량만큼 더해줌
		for (int i = end; i != start; i = parent[i])
		{
			flow[parent[i]][i] += Minflow;
			flow[i][parent[i]] -= Minflow;
		}
		result += Minflow;

	}
}

int main()
{
	a[1].push_back(2);
	a[2].push_back(1);
	cost[1][2] = 12;

	a[1].push_back(4);
	a[4].push_back(1);
	cost[1][4] = 11;

	a[2].push_back(3);
	a[3].push_back(2);
	cost[2][3] = 6;

	a[2].push_back(4);
	a[4].push_back(2);
	cost[2][4] = 3;

	a[2].push_back(5);
	a[5].push_back(2);
	cost[2][5] = 5;

	a[2].push_back(6);
	a[6].push_back(2);
	cost[2][6] = 9;

	a[3].push_back(6);
	a[6].push_back(3);
	cost[3][6] = 8;

	a[4].push_back(5);
	a[5].push_back(4);
	cost[4][5] = 9;

	a[5].push_back(3);
	a[3].push_back(5);
	cost[5][3] = 3;

	a[5].push_back(6);
	a[6].push_back(5);
	cost[5][6] = 4;

	maxFlow(1, 6);
	cout << result << endl;
	return 0;
}