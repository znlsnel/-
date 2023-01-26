#include <iostream>
#include <vector>
#include <stack>
#define MAX 10000
using namespace std;

// ���� ���� ��� ( SCC - Strongly Connected Component ) �˰���

bool finished[MAX];		// SCC�� ���ԵǾ� �ִ� �ֵ��� üũ�Ͽ� �ߺ� ����
int seqID[MAX], id;		// �� ��忡 ������ȣ�� �Űܼ� root ��带 üũ��
vector<int> v[MAX];		// �� ������ ��� �׷���
vector<vector<int>> SCC;	// SCC�� ��� vector

stack<int> s;				// stack�� Ȱ���Ͽ� scc ����

int dfs(int node)
{

	// ���� ����� ������ȣ�� �Ű��ְ� 
	// �� ���� ��ȯ�� ���� �������� ������
	int start = seqID[node] = ++id;

	// stack�� ���� ��带 ����
	s.push(node);

	for (size_t i = 0; i < v[node].size(); i++)
	{
		// ���� ���� ����� ���� ���
		int next = v[node][i];

		// dfs �Լ��� start�� �����ϰ� �Ǿ�����
		// ��, seqID���� ���� ���� �ָ� start(��ȯ�� ���� ����)�� �Ѵٴ� ���
		// -- 1���� �����ؼ� 1�� ��ȯ �Ǿ��ٸ� ��ȯ�� �Ǿ� ���ƿԴٴ°�
		if (seqID[next] == 0)
			start = min(start, dfs(next));
		
		// �̹� dfs�� ���� ����� seqID�� �̾Ƽ� ��
		else if (finished[next] == false)
			start = min(start, seqID[next]);
	}

	// start�� ���� ����� seqID��� ����
	// ���� �ݺ��������� ����Լ��� ����Ǿ�
	// ��ȯ�� �̷���� �ڱ� �ڽ����� ���ƿ԰ų�
	// �̾����� ������ ���ų�..
	if (start == seqID[node])
	{

		vector<int> scc;
		while (true)
		{
			int _node = s.top();
			s.pop();
			finished[_node] = true;
			scc.push_back(_node);

			// stack���� ���� ��尡 ���� �����
			 // ��ȯ�� ���� �������� �Դٴ� �̾߱�
			if (_node == node)
			{
				// ��� �κ�
				cout << "SCC---- ";
				for (int i = 0; i < scc.size(); i++)
					cout << scc[i] << " ";
				cout << "\n";

				// ��ȯ�� ������������ ������ �ݺ��� ����
				break;
			}
		}

		SCC.push_back(scc);
	}
	return start;
}

int main()
{
	v[1].push_back(2);

	v[2].push_back(3);
	v[2].push_back(4);
	v[2].push_back(6);

	v[3].push_back(1);

	v[4].push_back(7);

	v[5].push_back(6);
	v[5].push_back(8);

	v[6].push_back(8);

	v[7].push_back(4);
	v[7].push_back(5);

	v[8].push_back(7);


	for (int i = 1; i <= 8; i++)
	{
		if (seqID[i] == 0) dfs(i);
	}

	return 0;
}