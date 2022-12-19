#include <iostream>
using namespace std;
int N = 8;
int MAX = 1000000000;
int cost[8]; // �� ���������� �ּҺ���� ���� ����

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
		cost[i] = g[start][i]; // ���� ��忡������ ��� ���������� ����� ���

	for (int current = 0; current < N; current++)
	{
		for (int dest = 0; dest < N; dest++)
		{
			if (cost[dest] > cost[current] + g[current][dest])
				cost[dest] = cost[current] + g[current][dest];
		}  // ��ǥ���ϴ� ����� �ּҺ�� = ���� ��ġ������ �ּҺ�� + ���� ��ġ���� ��ǥ ������ ���
	}
}

int main()
{
	dijkstra(1);

	for (int i = 0; i < N; i++)
		cout << cost[i] << " ";

	return 0;
}