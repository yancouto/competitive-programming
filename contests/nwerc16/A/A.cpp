#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;

char v[112][412];
int memo[41][41][401][10], n, m;
int solve(int l, int r, int i, int d) {
	if(r < l) return 0;
	if(i == m) return 0;
	if(d == 10) return 1e8;
	int &ret = memo[l][r][i][d];
	if(ret != -1) return ret;
	ret = solve(l, r, i, d + 1);
	int pr = 0;
	for(int j = l; j <= r; j++) {
		pr += (v[j][i] != (d + '0'));
		ret = min(ret, pr + solve(l, j, i + 1, 0) + solve(j + 1, r, i, d + 1));
	}
	return ret;
}

char v2[112][412];

void build(int l, int r, int i, int d) {
	if(i == m) return;
	if(r < l) return;
	int ret = solve(l, r, i, d);
	if(ret == solve(l, r, i, d + 1)) return build(l, r, i, d + 1);
	int pr = 0;
	for(int j = l; j <= r; j++) {
		pr += (v[j][i] != (d + '0'));
		v2[j][i] = d + '0';
		if(ret == pr + solve(l, j, i + 1, 0) + solve(j + 1, r, i, d + 1)) {
			build(l, j, i + 1, 0);
			build(j + 1, r, i, d + 1);
			return;
		}
	}
}

int main() {
	memset(memo, -1, sizeof memo);
	int i;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) scanf("%s", v[i]);
	build(0, n - 1, 0, 0);
	for(i = 0; i < n; i++) puts(v2[i]);
}
