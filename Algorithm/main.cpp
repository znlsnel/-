#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
#define MAX 7

vector<int> v[MAX];
int inDegree[MAX + 1];

void TopologySort()
{

	queue<int> q;
	vector<int> result;

	for (int i = 1; i <= MAX ; i++)
		if (inDegree[i] == 0) q.push(i);

	for (int i = 1; i <= MAX; i++)
	{
		if (q.empty())
		{
			cout << "순환 발생" << endl;
			return;
		}
		
		int a = q.front();
		result.push_back(a);
		q.pop();

		for (int j = 0; j < v[a].size(); j++)
		{
			int b = v[a][j];
			if (--inDegree[b] == 0)
			{
				q.push(b);
			}
		}
	}
	for (int i = 0; i < result.size(); i++)
		cout << result[i] << " ";
	
}

int main()
{

	v[1].push_back(2);
	inDegree[2]++;
	v[1].push_back(5);
	inDegree[5]++;
	v[2].push_back(3);
	inDegree[3]++;
	v[3].push_back(4);
	inDegree[4]++;
	v[4].push_back(6);
	inDegree[6]++;
	v[5].push_back(6);
	inDegree[6]++;
	v[6].push_back(7);
	inDegree[7]++;
	TopologySort();
	return 0;
}