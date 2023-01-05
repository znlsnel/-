#include <iostream>

using namespace std;

int n = 1000;
bool a[1000];

void PrimeNumber() 
{
	for (int i = 2; i < n; i++)
		a[i] = true;

	for (int i = 2; i < n; i++)
	{
		if (a[i] == false) continue;
		for (int j = i * 2; j < n; j += i)
			a[j] = false;
	}
	for (int i = 2; i < n; i++)
		if (a[i]) cout << i << " ";
}

int main()
{
	PrimeNumber();
	return 0;
}

