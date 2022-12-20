#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int MAX = 1000000000;
int cost[8]; // �� ���������� �ּҺ���� ���� ����
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

class PQ
{
public:
	PQ(bool b)
	{
		isMAX = b; // true�� �ϸ� maxHeap
	}

	void push(int n)
	{
		v.push_back(n);
		// vector�� ��������� �迭�� �ص� ���� ����

		int root = static_cast<int>(v.size()) - 1;
		int c = root;

		do
		{ // �θ���� �� �� �ڸ� �ٲ�
			root = max((c - 1) / 2, 0);
			int rN = v[root];
			int cN = v[c];

			// minHeap, maxHeap�� ����ؼ� ���Լ��� ����
			if (compare(rN, cN))
			{
				v[root] = cN;
				v[c] = rN;
			}

			c = root;
		} while (c > 0);
	}

	// minHeap�� maxHeap ���̿��� ������ ��ȯ�� ���
	void pop()
	{
		if (v.size() == 0) return;

		int size = static_cast<int>(v.size()) - 1;

		v[0] =v.back();
		v.pop_back();

		int c = 0;
		int root = 0;

		// �θ�� �ڽ� �� �� ��ȯ
		do
		{
			c = (root * 2) + 1;
			if (c >= size) break;

			if (c < size -1  && compare(v[c], v[c + 1]))
				c++;

			int rN = v[root];
			int cN = v[c];


			if (c <= size && compare(rN, cN))
			{
				v[root] = cN;
				v[c] = rN;
			}

			root = c;

		} while (root < size);


	}

	int top()
	{
		if ((int)v.size() == 0) return -1;
		return v[0];
	}

	bool compare(int r, int c)
	{
		if (isMAX) return r < c; // maxHeap�� ū�� ����
		return r > c; // minHeap�� ������ ����
	}

	int size()
	{
		return static_cast<int>(v.size());
	}

	bool empty()
	{
		return static_cast<int>(v.size()) == 0;
	}

public:
	bool isMAX = false;
	vector<int> v;
};


void dijkstra1(int start) 
{
	countN = 0;
	for (int i = 0; i < N; i++)
		cost[i] = g[start][i]; // ���� ��忡������ ��� ���������� ����� ���

	for (int current = 0; current < N; current++)
	{
		for (int dest = 0; dest < N; dest++)
		{
			if (cost[dest] > cost[current] + g[current][dest])
				cost[dest] = cost[current] + g[current][dest];
			countN++;
		}  // ��ǥ���ϴ� ����� �ּҺ�� = ���� ��ġ������ �ּҺ�� + ���� ��ġ���� ��ǥ ������ ���
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
		countN++;
	}

	return index;
}

void dijkstra2(int start)
{
	countN = 0;

	for (int i = 0; i < N; i++)
		cost[i] = g[start][i]; // ���� ��忡������ ��� ���������� ����� ���

	v[start] = true;

	for (int i = 0; i < N - 1; i++)
	{
		int current = SmallIndex();
		v[current] = true;

		for (int dest = 0; dest < N; dest++)
		{
			if (cost[dest] > cost[current] + g[current][dest])
				cost[dest] = cost[current] + g[current][dest];
			countN++;
		}  // ��ǥ���ϴ� ����� �ּҺ�� = ���� ��ġ������ �ּҺ�� + ���� ��ġ���� ��ǥ ������ ���
	}
} // countN = 112 

void dijkstra3(int start)
{
	countN = 0;
	PQ pq(false);

	for (int i = 0; i < N; i++)
	{
		cost[i] = g[start][i]; // ���� ��忡������ ��� ���������� ����� ���
		pq.push(cost[i]);
	}

	v[start] = true;

	while(!pq.empty())
	{
		int current = pq.top();
		pq.pop();

		for (int dest = 0; dest < N; dest++)
		{
			if (cost[dest] > cost[current] + g[current][dest])
				cost[dest] = cost[current] + g[current][dest];
			countN++;
		}  // ��ǥ���ϴ� ����� �ּҺ�� = ���� ��ġ������ �ּҺ�� + ���� ��ġ���� ��ǥ ������ ���
	}
} // countN = 112 

int main()
{
	
	dijkstra3(0); // 0 2 1 1 2 2 3 5
	for (int i = 0; i < N; i++)
		cout << cost[i] << " ";

	cout << "\n" << countN << "\n"; 
	
	
	return 0;
}