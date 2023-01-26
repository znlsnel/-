#include <iostream>
#include <vector>
#include <stack>
#define MAX 10000
using namespace std;

// 강한 결합 요소 ( SCC - Strongly Connected Component ) 알고리즘

bool finished[MAX];		// SCC에 포함되어 있는 애들은 체크하여 중복 제거
int seqID[MAX], id;		// 각 노드에 순서번호를 매겨서 root 노드를 체크함
vector<int> v[MAX];		// 각 정점이 담길 그래프
vector<vector<int>> SCC;	// SCC가 담길 vector

stack<int> s;				// stack을 활용하여 scc 추출

int dfs(int node)
{

	// 현재 노드의 순서번호를 매겨주고 
	// 그 값을 순환의 시작 지점으로 설정함
	int start = seqID[node] = ++id;

	// stack에 현재 노드를 넣음
	s.push(node);

	for (size_t i = 0; i < v[node].size(); i++)
	{
		// 현재 노드와 연결된 다음 노드
		int next = v[node][i];

		// dfs 함수는 start를 추출하게 되어있음
		// 즉, seqID값이 가장 작은 애를 start(순환의 시작 지점)로 한다는 얘기
		// -- 1에서 시작해서 1이 반환 되었다면 순환이 되어 돌아왔다는거
		if (seqID[next] == 0)
			start = min(start, dfs(next));
		
		// 이미 dfs를 돌린 노드라면 seqID만 뽑아서 비교
		else if (finished[next] == false)
			start = min(start, seqID[next]);
	}

	// start가 현재 노드의 seqID라는 것은
	// 위의 반복문에서의 재귀함수가 종료되어
	// 순환이 이루어져 자기 자신으로 돌아왔거나
	// 이어지는 간선이 없거나..
	if (start == seqID[node])
	{

		vector<int> scc;
		while (true)
		{
			int _node = s.top();
			s.pop();
			finished[_node] = true;
			scc.push_back(_node);

			// stack에서 뽑은 노드가 현재 노드라면
			 // 순환의 시작 지점으로 왔다는 이야기
			if (_node == node)
			{
				// 출력 부분
				cout << "SCC---- ";
				for (int i = 0; i < scc.size(); i++)
					cout << scc[i] << " ";
				cout << "\n";

				// 순환의 시작지점으로 왔으니 반복문 종료
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