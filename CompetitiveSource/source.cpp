#include <iostream>
#include <functional>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
using namespace std;

#define ms(x, y) memset((x), (y), sizeof((x)))
#define lb lower_bound
#define ub upper_bound

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
#define INF 1000000000
#define LL_INF 10000000000000000LL
#define rint register int

inline int GetInt(char c = getchar(), int bj = 1, int num = 0)
{
	while (!(c <= '9' && c >= '0')) { if (c == '-') bj = -1; c = getchar(); }
	while (c <= '9' && c >= '0') num = (num << 1) + (num << 3) + c - '0', c = getchar();
	return num;
}

#define MAXN 50005
#define MAX_Q 505
int n, m, m_sv[MAXN], szBlock;
int a[MAXN], toNum[MAXN];
vi numPos[MAXN];

void Input()
{
	n = GetInt(), m = GetInt();
	szBlock = sqrt(n);
	for (rint i = 1; i <= n; ++i)
	{
		toNum[i] = a[i] = GetInt();
		m_sv[i] = (i - 1) / szBlock + 1;
	}
	sort(toNum + 1, toNum + 1 + n);
	int len = unique(toNum + 1, toNum + 1 + n) - toNum - 1;
	for (rint i = 1; i <= n; ++i)
	{
		a[i] = lb(toNum + 1, toNum + 1 + len, a[i]) - toNum;
		numPos[a[i]].push_back(i);
	}
}

int cnt[MAXN], maxMode[MAX_Q][MAX_Q];
void Prepare()
{
	for (rint s = 1; s <= m_sv[n]; ++s)
	{
		ms(cnt, 0);
		int mode, nMode = 0;
		for (rint i = szBlock * (s - 1) + 1; i <= n; ++i)
		{
			++cnt[a[i]];
			if (cnt[a[i]] > nMode ||
				cnt[a[i]] == nMode && toNum[a[i]] < toNum[mode])
				mode = a[i], nMode = cnt[a[i]];
			maxMode[s][m_sv[i]] = mode;
		}
	}
}

#define ALL(x) (x).begin(),(x).end()
inline int GetAmount(const int l, const int r, const int x)
{
	return ub(ALL(numPos[x]), r) - lb(ALL(numPos[x]), l);
}

int Query(int l, int r)
{
	int mode = maxMode[m_sv[l] + 1][m_sv[r] - 1];
	int nMode = GetAmount(l, r, mode);
	for (rint i = l; i <= min(r, szBlock * m_sv[l]); ++i)
	{
		int tMode = GetAmount(l, r, a[i]);
		if (tMode > nMode || 
			tMode == nMode && toNum[a[i]] < toNum[mode])
			mode = a[i], nMode = tMode;
	}
	if (m_sv[l] == m_sv[r]) return toNum[mode];
	for (rint i = szBlock * (m_sv[r] - 1) + 1; i <= r; ++i)
	{
		int tMode = GetAmount(l, r, a[i]);
		if (tMode > nMode || 
			tMode == nMode && toNum[a[i]] < toNum[mode])
			mode = a[i], nMode = tMode;
	}
	return toNum[mode];
}

int main()
{
	Input();
	Prepare();
	int lasAns = 0;
	for (rint i = 1; i <= m; ++i)
	{
		int l = GetInt(), r = GetInt();
		l = (l + lasAns - 1) % n + 1;
		r = (r + lasAns - 1) % n + 1;
		if (l > r) swap(l, r);
		cout << (lasAns = Query(l, r)) << '\n';
	}
	return 0;
}