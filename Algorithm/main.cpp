#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> makeTable(string Pattern)
{
        vector<int> table(Pattern.size(), 0);

        for (int tail = 1, head = 0; tail < Pattern.length(); tail++)
        {
                while (head > 0 && Pattern[tail] != Pattern[head])
                        head = table[head - 1];

                if (Pattern[tail] == Pattern[head])
                        table[tail] = ++head;
        }


        return table;
}

void KMP(string parent, string pattern)
{
        vector<int> table = makeTable(pattern);
        int parentSize = parent.size();
        int patternSize = pattern.size();

        int j = 0;
        for (int i = 0; i < parentSize; i++)
        {
                while (j > 0 && parent[i] != pattern[j])
                {
                        j = table[j - 1];
                }
                if (parent[i] == pattern[j])
                {
                        if (j == patternSize - 1)
                        {
                                cout << i - patternSize + 2 << "에서 패턴을 찾았습니다." << endl;
                                j = table[j];
                        }
                        else
                        {
                                j++;
                        }
                }
        }
}

int main() {
        string parent = "abcdabcabb";
        string pattern = "abc";
        KMP(parent, pattern);

        return 0;
}