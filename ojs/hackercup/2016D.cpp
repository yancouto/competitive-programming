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
ll base;

string t[309];
int p[309], dif[309];
char s[100009];
vector<int> h[309];

int lcp(int i, int j) {
	if(t[i][0] != t[j][0]) return 0;
	int l = 1, r = min(t[i].size(), t[j].size());
	while(l < r) {
		int m = (l + r + 1) / 2;
		if(h[i][m - 1] == h[j][m - 1]) l = m;
		else r = m - 1;
	}
	return l;
}

bool hless(int i, int j) {
	int s = lcp(i, j);
	if(s == t[i].size() || s == t[j].size()) return t[i].size() < t[j].size();
	return t[i][s] < t[j][s];
}

int lc[309][309];

int memo[304][303];
int solve(int i, int k) {
	if(k == 0) return t[p[i]].size();
	int &r = memo[i][k];
	if(r != -1) return r;
	r = 300000000;
	for(int j = i + 1; !t[j].empty(); j++)
		r = min(r, int(t[p[i]].size() + t[p[j]].size()) - 2 * lc[i][j] + solve(j, k - 1));
	return r;
}

int main() {
	srand(time(NULL));
	base = 259 + (rand() % 200);
	int i, j, n, k;
	for_tests(tn, tt) {
		memset(memo, -1, sizeof memo);
		scanf("%d %d", &n, &k);
		for(i = 0; i < n; i++) {
			scanf("%s", s);
			t[i].append(s);
			h[i].resize(t[i].size());
			ll hh = 0;
			for(j = 0; j < t[i].size(); j++)
				h[i][j] = (hh = hh * base + t[i][j]);
			p[i] = i;
		}
		sort(p, p + n, hless);
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				lc[i][j] = lcp(p[i], p[j]);
		for(i = 0; i < n - 1; i++)
			dif[i + 1] = dif[i] + (t[p[i]].size() + t[p[i + 1]].size() - 2 * lcp(p[i], p[i + 1]));
		int mn = INT_MAX;
		for(i = 0; i + k - 1 < n; i++)
			mn = min(mn, int(t[p[i]].size()) + solve(i, k - 1));
		printf("Case #%d: %d\n", tt, mn + k);
		for(i = 0; i < n; i++) t[i].clear();
	}
}
