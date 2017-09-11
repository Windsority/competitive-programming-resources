#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <deque>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define INF 1000000000

#define MAXN 100005
int n, s[MAXN * 2], res;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", s + i);
		s[i + n] = s[i];
		s[i] += s[i - 1];
	}
	for (int i = 1 + n; i < 2 * n; ++i)
		s[i] += s[i - 1];
	deque<int> Q;
	for (int i = 1; i < 2 * n; ++i)
	{
		while (!Q.empty() && Q.front() <= i - n) Q.pop_front();
		while (!Q.empty() && s[i] < s[Q.back()]) Q.pop_back();
		Q.push_back(i);
		if (i >= n && s[i - n] <= s[i]) ++res;
	}
	printf("%d\n", res);
}