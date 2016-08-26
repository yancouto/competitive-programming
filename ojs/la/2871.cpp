#include <bits/stdc++.h>
using namespace std;
int n, k, l;
int f[1005], d[1005];


int inf = 100000000;
int memo[2][20009];
inline int& m(int i, int j) { return memo[i%2][j]; }
int main() {
	int i, j;
	while(true) {
		scanf("%d %d %d", &n, &k, &l);
		if(!n) return 0;
		for(i = 0; i < n; i++)
			scanf("%d %d", &f[i], &d[i]);
		m(0, 0) = 0;
		for(j = 1; j <= 20*n; j++) {
			m(0, j) = inf;
			if(j == f[0] && d[0] <= l) m(0, j) = d[0];
		}
		for(i = 1; i < n; i++)
			for(j = 0; j <= 20*n; j++) {
				m(i, j) = max(m(i - 1, j) - k, 0);
				if(j >= f[i] && (m(i - 1, j - f[i]) + d[i]) <= l)
					m(i, j) = min(m(i - 1, j - f[i]) + d[i], m(i, j));
			}
		for(j = 20*n; j >= 0; j--)
			if(m(n-1, j) <= l)
				break;
		printf("%d\n", j);
	}
}