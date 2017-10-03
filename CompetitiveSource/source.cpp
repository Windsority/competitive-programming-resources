#include <iostream>
#include <functional>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define INF 1000000000
#define LL_INF 10000000000000000LL

#define MAXN 20005
int n, m, t;
struct Edge {
	int to, length, history;
};
vector<Edge> G[MAXN];

int dis[MAXN];
bool used[MAXN];
bool Check(int abandon)
{
	fill(dis, dis + n + 1, INF);
	dis[1] = 0;
	queue<int> Q;
	Q.push(1);
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop(); used[u] = false;
		for (int i = 0; i < G[u].size(); ++i)
		{
			if (G[u][i].history <= abandon) continue;
			int v = G[u][i].to, c = G[u][i].length;
			if (dis[v] > dis[u] + c)
			{
				dis[v] = dis[u] + c;
				if (!used[v]) used[v] = true, Q.push(v);
			}
		}
	}
	return dis[n] >= t;
}

int main()
{
	scanf("%d%d%d", &n, &m, &t);
	vi bi_section;
	for (int i = 0; i < m; ++i)
	{
		int u, v, w, c;
		scanf("%d%d%d%d", &u, &v, &w, &c);
		G[u].push_back({ v, w, c });
		bi_section.push_back(c);
	}
	if (Check(-INF))
	{
		printf("-1 %d", dis[n]);
		return 0;
	}
	sort(bi_section.begin(), bi_section.end());
	int l = 0, r = bi_section.size() - 1;
	while (l <= r)
	{
		int mid = l + (r - l) / 2;
		if (Check(bi_section[mid])) r = mid - 1;
		else l = mid + 1;
	}
	printf("%d", bi_section[l]);
}