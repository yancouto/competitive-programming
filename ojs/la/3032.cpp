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
const int N = 512345;

char op[N]; int x[N], v[N];
int S[N], sz[N], r[N], w[N], a[N], b[N], mrk[N];
int tr[N * 32][2], en, g[N*32];

void add(int r, int x, int p=1) {
	for(int i = 20; i >= 0; i--) {
		if(!tr[r][(x >> i) & 1]) tr[r][(x >> i) & 1] = en++;
		r = tr[r][(x >> i) & 1];
		g[r] += p;
	}
}

int query(int r, int k) {
	int x = 0;
	for(int i = 20; i >= 0; i--) {
		assert(tr[r][0] || tr[r][1]);
		if(!tr[r][0]) x = (x << 1) | 1, r = tr[r][1];
		else if(k >= g[tr[r][0]]) x = (x << 1) | 1, k -= g[tr[r][0]], r = tr[r][1];
		else x <<= 1, r = tr[r][0];
	}
	return x;
}

int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void go(int r1, int r2, int x) {
	if(!tr[r1][0] && !tr[r1][1]) return add(r2, x, g[r1]);
	if(tr[r1][0]) go(tr[r1][0], r2, (x << 1));
	if(tr[r1][1]) go(tr[r1][1], r2, (x << 1) | 1);
}

void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
	go(r[b], r[a], 0);
}

const int off = 1000000;
int main() {
	int i, n, m, tt = 0;
	while(scanf("%d %d", &n, &m) != EOF && n) {
		en = 0;
		for(i = 0; i < n; i++) scanf("%d", &w[i]), S[i] = i, sz[i] = 1, r[i] = en++;
		for(i = 0; i < n; i++) w[i] += off;
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a[i], &b[i]); a[i]--, b[i]--;
			mrk[i] = 1;
		}
		int ct = 0; i = 0;
		while(true) {
			scanf(" %c", &op[i]);
			if(op[i] == 'E') break;
			if(op[i] == 'D') {
				scanf("%d", &x[i]); x[i]--;
				mrk[x[i]] = 0;
			} else if(op[i] == 'C') {
				scanf("%d %d", &x[i], &v[i]); x[i]--; v[i] += off;
				swap(v[i], w[x[i]]);
			} else {
				ct++;
				scanf("%d %d", &x[i], &v[i]); x[i]--; v[i]--;
			}
			i++;
		}
		for(int j = 0; j < n; j++)
			add(r[j], w[j]);
		for(int j = 0; j < m; j++)
			if(mrk[j])
				join(a[j], b[j]);
		ll tot = 0;
		while(i--) {
			if(op[i] == 'D')
				join(a[x[i]], b[x[i]]);
			else if(op[i] == 'C')
				add(r[find(x[i])], w[x[i]], -1), add(r[find(x[i])], w[x[i]] = v[i]);
			else if(v[i] >= 0 && sz[find(x[i])] > v[i]) {
				tot += query(r[find(x[i])], sz[find(x[i])] - 1 - v[i]) - off;
			}
		}
		for(i = 0; i < en + 10; i++) tr[i][0] = tr[i][1] = 0, g[i] = 0;
		printf("Case %d: %.6f\n", ++tt, tot / double(ct));
	}
}
