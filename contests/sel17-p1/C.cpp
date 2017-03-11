#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef pair<int, int> pii;

const int N = 1123;
vector<pii> all;
inline int g(int b, int f) {
	return lower_bound(all.begin(), all.end(), pii(b, f)) - all.begin();
}
int f[612][612];
vector<int> b[N];

inline void ed(int a, int b, int t) {
	f[a][b] = f[b][a] = min(t, f[a][b]);
}

inline int go(int A, int a, int B, int C, int c, int D) {
	return abs(b[A][a] - B) + f[g(A, b[A][a])][g(C, b[C][c])] + abs(b[C][c] - D);
}

int bi[N], fi[N], bj[N], fj[N], t[N];

int main() {
	int i, tt, n, j, k, q, m, A, B, C, D;
	scanf("%d", &tt);
	while(tt--) {
		scanf("%d %*d %d", &n, &m);
		for(i = 0; i < n; i++) all.pb(pii(i, 1)), b[i].pb(1);
		for(i = 0; i < m; i++) {
			scanf("%d %d %d %d %d", &bi[i], &fi[i], &bj[i], &fj[i], &t[i]);
			bi[i]--; bj[i]--;
			b[bi[i]].pb(fi[i]);
			b[bj[i]].pb(fj[i]);
			all.pb(pii(bi[i], fi[i]));
			all.pb(pii(bj[i], fj[i]));
		}
		sort(all.begin(), all.end());
		all.erase(unique(all.begin(), all.end()), all.end());
		for(i = 0; i < n; i++) {
			sort(b[i].begin(), b[i].end());
			b[i].erase(unique(b[i].begin(), b[i].end()), b[i].end());
		}
		for(i = 0; i < all.size(); i++)
			for(j = 0; j < all.size(); j++)
				f[i][j] = (i == j? 0 : 1e8);
		for(i = 0; i < n; i++)
			ed(g(i, 1), g((i + 1) % n, 1), 1);
		for(i = 0; i < n; i++)
			for(j = 0; j < b[i].size() - 1; j++)
				ed(g(i, b[i][j]), g(i, b[i][j + 1]), abs(b[i][j + 1] - b[i][j]));
		for(i = 0; i < m; i++)
			ed(g(bi[i], fi[i]), g(bj[i], fj[i]), t[i]);
		for(k = 0; k < all.size(); k++)
			for(i = 0; i < all.size(); i++)
				for(j = 0; j < all.size(); j++)
					f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
		scanf("%d", &q);
		while(q--) {
			scanf("%d %d %d %d", &A, &B, &C, &D); A--; C--;
			int a = upper_bound(b[A].begin(), b[A].end(), B) - b[A].begin();
			int c = upper_bound(b[C].begin(), b[C].end(), D) - b[C].begin();
			int ans = go(A, a - 1, B, C, c - 1, D);
			if(a < b[A].size()) ans = min(ans, go(A, a, B, C, c - 1, D));
			if(c < b[C].size()) ans = min(ans, go(A, a - 1, B, C, c, D));
			if(a < b[A].size() && c < b[C].size()) ans = min(ans, go(A, a, B, C, c, D));
			if(A == C) ans = min(ans, abs(B - D));
			printf("%d\n", ans);
		}

		all.clear();
		for(i = 0; i < n; i++) b[i].clear();
	}
}
