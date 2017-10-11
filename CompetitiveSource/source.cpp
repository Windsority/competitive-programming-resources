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
#define MOD 1000000007

#define MAXN 1000005
char mines[MAXN];
enum {
	ZERO, ONE_FRONT, ONE_BACK, TWO, MINED
};
ll f[MAXN][5];

int main()
{
	scanf("%s", mines + 1);
	int len = strlen(mines + 1);
	if (mines[1] == '0') f[1][ZERO] = 1;
	else if (mines[1] == '1') f[1][ONE_BACK] = 1;
	else if (mines[1] == '*') f[1][MINED] = 1;
	else f[1][ONE_BACK] = f[1][ZERO] = f[1][MINED] = 1;
	for (int i = 2; i <= len; ++i)
	{
		if (mines[i] == '?')
		{
			f[i][ZERO] = (f[i - 1][ONE_FRONT] + f[i - 1][ZERO]) % MOD;
			f[i][ONE_FRONT] = f[i - 1][MINED];
			if (i != len) f[i][ONE_BACK] = (f[i][ZERO] + f[i][ONE_FRONT]) % MOD;
			if (i != len) f[i][TWO] = f[i - 1][MINED];
			f[i][MINED] = (f[i - 1][ONE_BACK] + f[i - 1][TWO] + f[i - 1][MINED]) % MOD;
		}
		else
		{
			if (mines[i] == '*') f[i][MINED] = (f[i - 1][ONE_BACK] + f[i - 1][MINED] + f[i - 1][TWO]) % MOD;
			else if (mines[i] == '0') f[i][ZERO] = (f[i - 1][ONE_FRONT] + f[i - 1][ZERO]) % MOD;
			else if (mines[i] == '2') f[i][TWO] = f[i - 1][MINED];
			else
			{
				f[i][ONE_FRONT] = f[i - 1][MINED];
				f[i][ONE_BACK] = (f[i - 1][ZERO] + f[i - 1][ONE_FRONT]) % MOD;
			}			
		}
	}
	ll res = f[len][ZERO] + f[len][ONE_FRONT] + f[len][MINED];
	printf("%lld", res % MOD);
}