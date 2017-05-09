#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

int n;
const int N = 312;
char s[N][N];
int tot[N], blr[N], bll[N], len[N], p[N];

int memo[312][312 * 312];
bool seen[312][312 * 312];
int solve(int i, int cur) {
	if(i == n) return (cur == 0? 0 : INT_MIN);
	if(seen[i][cur]) return memo[i][cur];
	seen[i][cur] = 1;
	int &r = memo[i][cur];
	r = solve(i + 1, cur);
	if(blr[p[i]] <= cur) r = max(r, solve(i + 1, cur + tot[p[i]]) + len[p[i]]);
	return r;
}

int main () {
	int i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%s", s[i]);
	for(i = 0; i < n; i++) {
		int mn = 0;
		int cur = 0;
		len[i] = strlen(s[i]);
		for(j = 0; s[i][j]; j++) {
			cur += (s[i][j] == ')'? -1 : 1);
			mn = min(mn, cur);
		}
		tot[i] = cur;
		blr[i] = -mn;
		cur = mn = 0;
		for(j = len[i] - 1; j >= 0; j--) {
			cur += (s[i][j] == '('? -1 : 1);
			mn = min(mn, cur);
		}
		//printf("bll[%d] = %d\n", i, -mn);
		bll[i] = -mn;
		p[i] = i;
	}
	sort(p, p + n, [](int i, int j) {
		if((tot[i] >= 0) != (tot[j] >= 0)) return tot[i] >= 0;
		if(tot[i] >= 0) {
			return blr[i] < blr[j];
		} else {
			return blr[i] > blr[j];
		}
	});
	printf("%d\n", solve(0, 0));
}
