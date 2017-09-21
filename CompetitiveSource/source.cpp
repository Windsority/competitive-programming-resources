#include <iostream>
#include <functional>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define INF 1000000000
#define LL_INF 10000000000000000LL

#define MAXN 100005
int n;

struct Tree {
	vi G[MAXN];
	int key_node, max_dep, d[MAXN], par[MAXN];
	void Input();
	void FindKeyNode();
	void DFS(int, int);
	void Hash();
}a, b;

int main()
{
	scanf("%d", &n);
	a.Input();
	b.Input();
}

void Tree::Input()
{
	for (int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
}

void Tree::DFS(int u, int p)
{
	if (d[u] > max_dep)
	{
		max_dep = d[u];
		key_node = u;
	}
	for (int i = 0; i < G[u].size(); ++i)
	{
		int v = G[u][i];
		if (v == p) continue;
		par[v] = u;
		d[v] = d[u] + 1;
		DFS(v, u);
	}
}

void Tree::Hash()
{

}

void Tree::FindKeyNode()
{
	DFS(1, 0);
	max_dep = 0;
	DFS(key_node, 0);
	max_dep /= 2;
	while (max_dep--) key_node = par[key_node];
}