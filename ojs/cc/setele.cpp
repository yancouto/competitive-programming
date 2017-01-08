#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

#define div asasd
const int N = 112345;
int S[N], sz[N];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

inline void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}

int a[N], b[N], c[N], p[N];

int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d %d", &a[i], &b[i], &c[i]); a[i]--; b[i]--;
		p[i] = i;
	}
	sort(p, p + n - 1, [](int i, int j) { return c[i] < c[j]; });
	double tot = accumulate(c, c + n - 1, 0ll);
	for(i = 0; i < n; i++) S[i] = i, sz[i] = 1;
	ll all = (ll(n) * ll(n - 1)) / 2ll;
	for(i = 0; i < n - 1; i++) {
		tot -= (ll(c[p[i]]) * ll(sz[find(a[p[i]])]) * ll(sz[find(b[p[i]])])) / double(all);
		join(a[p[i]], b[p[i]]);
	}
	printf("%.10f\n", tot);
}
