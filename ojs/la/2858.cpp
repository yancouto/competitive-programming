#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m;
int p[109];
int memo[109][109];
int solve(int i, int j) {
	if(i == j) return 0;
	int &m = memo[i][j];
	if(m != -1) return m;
	m = 1 + solve(i + 1, j);
	for(int k = i + 2; k <= j; k++)
		if(p[i] == p[k])
			m = min(m, 1 + solve(i + 1, k - 1) + solve(k, j));
	return m;
}

int main() {
	int t, i;
	scanf("%d", &t);
	for(int tt = 1; tt <= t; tt++) {
		scanf("%d %d", &n, &m);
		scanf("%d", &p[0]);
		for(i = 1; i < n;) {
			scanf("%d", &p[i]);
			if(p[i] == p[i - 1]) n--;
			else i++;
		}
		memset(memo, -1, sizeof(memo));
		printf("Case %d: %d\n", tt, solve(0, n - 1) + 1);
	}
	return 0;
}