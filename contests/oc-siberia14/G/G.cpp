#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const ll b = 263;

vector<ll> h[109];
ll pot[51234];
ll hs(int i, int l, int r) {
	ll H = h[i][r] - mod(h[i][l - 1] * pot[r - l + 1]);
	if(H < 0) H += modn;
	//printf("hs(%d, %d, %d) = %lld\n", i, l, r, H);
	return H;
}

inline bool eq(int i, int li, int j, int lj, int sz) { return hs(i, li, li + sz - 1) == hs(j, lj, lj + sz - 1); }

int lcp(int i, int li, int j, int lj) {
	int mx = min(h[i].size() - li, h[j].size() - lj);
	//if(eq(i, li, j, lj, mx)) return mx;
	//printf("lcp(%d, %d, %d, %d)\n", i, li, j, lj);
	if(!eq(i, li, j, lj, 1)) return 0;
	//printf("continue;\n");
	int l = 1, r = mx;
	while(l < r) {
		int m = (l + r + 1) / 2;
		if(eq(i, li, j, lj, m)) l = m;
		else r = m - 1;
	}
	return l;
}

//bool less(int i, int li, int j, int lj) {
//	int mx = min(h[i].size() - li, h[j].size() - lj);
//	int lc = lcp(i, li, j, lj);
//	if(lc == mx) return h[i].size() - li < h[j].size() - lj;
//	return s[i][li + lc - 1] < s[j][lj + lc - 1];
//}

vector<int> lc[109][50009];

int seen[109][50009];
int n;
bool dfs(int i, int j) {
	if(seen[i][j]) return false;
	seen[i][j] = 1;
	//printf("visit %d, %d\n", i, j);
	for(int k = 0; k < n; k++) {
		if(j == 1 && k == i) continue;
		int l = lc[i][j][k];
		//printf("(%d, %d) with %d = %d\n", i, j, k, l);
		if(j + l == h[i].size() && l == h[k].size() - 1) return true;
		if(j + l == h[i].size() && dfs(k, l + 1)) return true;
		if(l == h[k].size() - 1 && dfs(i, j + l)) return true;
	}
	return false;
}

char S[51234];
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int i, j, k;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%s", S + 1);
		int sz = strlen(S + 1);
		//s[i] = (S + 1);
		h[i].resize(sz + 1); h[i][0] = 0;
		for(j = 1; j <= sz; j++) {
			h[i][j] = mod(b * h[i][j - 1] + S[j]);
			//printf("h[%d][%d] = %lld\n", i, j, h[i][j]);
		}
		for(j = 1; j <= sz; j++)
			lc[i][j].resize(n);
	}
	pot[0] = 1;
	for(i = 1; i < 51234; i++)
		pot[i] = mod(pot[i - 1] * b);
	for(i = 0; i < n; i++)
		for(j = 1; j < h[i].size(); j++)
			for(k = 0; k < n; k++)
				lc[i][j][k] = lcp(i, j, k, 1);
	for(i = 0; i < n; i++)
		if(dfs(i, 1)) {
			puts("YES");
			return 0;
		}
	puts("NO");
}
