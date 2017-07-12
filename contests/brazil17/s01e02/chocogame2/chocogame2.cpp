#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int memo[112][112];
int seen[112][112];
int solve(int n, int m) {
	if(n == m) return 0;
	if(n < m) return -solve(m, n);
	if(n == 1) return 0;
	assert(n > m);
	if(seen[n][m]) return memo[n][m];
	seen[n][m] = 1;
	int &r = memo[n][m];
	r = 0;
	for(int i = 1; i < n; i++) {
		int s = solve(i, m) + solve(n - i, m) + 1;
		r = max(r, s);
	}
	return r;
}
int n[112], m[112];

int main() {
	int i, p;
	scanf("%d", &p);
	for(i = 0; i < p; i++) scanf("%d %d", &n[i], &m[i]);
	int tot = 0;
	for(i = 0; i < p; i++)
		if(n[i] > m[i])
			tot += solve(n[i], m[i]);
		else if(m[i] > n[i])
			tot -= solve(m[i], n[i]);
	if(tot > 0) puts("Rowan");
	else if(tot < 0) puts("Colette");
	else puts("second");
}
