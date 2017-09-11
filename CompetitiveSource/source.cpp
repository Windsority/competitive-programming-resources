#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define INF 1000000000000000LL

#define MAXN 200005
int n, m, k;
struct Edge {
	int to, cost;
};
vector<Edge> G[MAXN];

ll dis[MAXN];
bool in_q[MAXN];
queue<int> Q;

void shortest_path(int S)
{
	for (int i = 1; i <= n; ++i) dis[i] = INF;
	dis[S] = 0;
	Q.push(S);
	while (!Q.empty())
	{
		int u = Q.front(); Q.pop(); in_q[u] = false;
		for (int i = 0; i < G[u].size(); ++i)
		{
			int v = G[u][i].to, c = G[u][i].cost;
			if (dis[v] > dis[u] + c) {
				dis[v] = dis[u] + c;
				if (!in_q[v]) Q.push(v), in_q[v] = true;
			}
		}
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i < m; ++i)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back({ v, w });
		G[v].push_back({ u, w });
	}
	int ST, ED;
	scanf("%d%d", &ST, &ED);
	shortest_path(1);
	ll dis_n = dis[n], du1 = dis[ST], dv1 = dis[ED];
	shortest_path(n);
	ll du2 = dis[ST], dv2 = dis[ED];
	for (int i = 1; i <= k; ++i)
	{
		ll w;
		scanf("%lld", &w);
		ll res = dis_n;
		res = min(res, du1 + dv2 + w);
		res = min(res, du2 + dv1 + w);
		if (res >= INF) puts("+Inf");
		else printf("%d\n", res);
	}
}