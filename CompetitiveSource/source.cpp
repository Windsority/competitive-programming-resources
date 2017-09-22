#include <iostream>
#include <functional>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;
#define INF 1000000005
#define MAXN 10005
typedef long long ll;
int n, m, U, V, S, c[MAXN], dis[MAXN], temp[MAXN];
struct Edge {
	int to, cost;
};
vector<Edge> G[MAXN];
bool in_q[MAXN];

typedef pair<int, int> P;
bool Check(int s)
{
	fill(dis + 1, dis + 1 + n, INF);
	deque<int> Q;
	Q.push_back(U);
	dis[U] = 0;
	if (c[U] > s || c[V] > s) return false;
	while (!Q.empty())
	{
		int u = Q.front(); 
		Q.pop_front();
		in_q[u] = false;
		for (int i = 0; i < G[u].size(); ++i)
		{
			int v = G[u][i].to, cost = G[u][i].cost;
			if (c[v] > s) continue;
			if (dis[v] > dis[u] + cost)
			{
				dis[v] = dis[u] + cost;
				if (!in_q[v])
				{
					in_q[v] = true;
					if (!Q.empty() && dis[v] < dis[Q.front()])
						Q.push_front(v);
					else Q.push_back(v);
				}
			}
		}
	}
	return dis[V] <= S;
}

int main()
{
	scanf("%d%d%d%d%d", &n, &m, &U, &V, &S);
	for (int i = 1; i <= n; ++i) 
	{ 
		scanf("%d", c + i);
		temp[i] = c[i];
	}	
	for (int i = 0; i < m; ++i)
	{
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		if (u == v) continue;
		G[u].push_back({ v, c });
		G[v].push_back({ u, c });

	}
	sort(temp + 1, temp + 1 + n);
	int l = 1, r = n;
	while (l <= r)
	{
		int mid = l + ((r - l) >> 1);
		if (Check(temp[mid])) r = mid - 1;
		else l = mid + 1;
	}
	if (l > n) puts("-1");
	else printf("%d", temp[l]);
}