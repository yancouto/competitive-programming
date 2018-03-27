#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

#define fst first
#define snd second

int oc[512];
int n;
int a[512];

short acc[512][512][512];
int memo2[512][512];
int get(int l, int r) {
	int &ans = memo2[l][r];
	if(ans != -1) return ans;
	for(int i = l; i <= r; i++)
		if(++acc[l][r][a[i]] == 2)
			return ans = -2;
	ans = *min_element(a + l, a + r + 1);
	for(int i = 1; i <= 500; i++)
		acc[l][r][i] += acc[l][r][i - 1];
	return ans;
}

int memo3[512][512];
int solve(int l, int r) {
	if(l == r) return 0;
	int &ans = memo3[l][r];
	if(ans != -1) return ans;
	ans = 1e8;
	for(int i = l; i < r; i++) {
		int cur = solve(l, i) + solve(i + 1, r);
		int gl = get(l, i), gr = get(i + 1, r);
		if(gl < gr) ans = min(ans, cur + (r - l + 1) - acc[l][i][gr]);
		else ans = min(ans, cur + (r - l + 1) - acc[i + 1][r][gl]);
	}
	return ans;
}

int memo[512];
int best(int l) {
	if(l == n) return 0;
	int &ans = memo[l];
	if(ans != -1) return ans;
	ans = 1e8;
	for(int r = l; r < n; r++) {
		if(get(l, r) == 1 && acc[l][r][r - l + 1] == r - l + 1)
			ans = min(ans, solve(l, r) + best(r + 1));
	}
	return ans;
}

int main() {
	int i;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	memset(memo, -1, sizeof memo);
	memset(memo2, -1, sizeof memo2);
	memset(memo3, -1, sizeof memo3);
	if(best(0) > 1e7) puts("impossible");
	else printf("%d\n", best(0));
}
