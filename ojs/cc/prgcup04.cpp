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

const int N = 212345;
int a[N], b[N];
ll c[N];

int S[N], sz[N];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

bool join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return false;
	if(sz[a] < sz[b]) swap(a, b);
	S[b] = a;
	sz[a] += sz[b];
	return true;
}
int p[N];
int main() {
	int i, n, m;
	scanf("%d %d", &n, &m);
	for(i = 0; i <= n; i++) S[i] = i, sz[i] = 1;
	for(i = 0; i < m; i++) {
		scanf("%d %d %lld", &a[i], &b[i], &c[i]);
		p[i] = i;
	}
	sort(p, p + m, [](int i, int j) { return c[i] < c[j]; });
	ll tot = 0;
	for(int i_ = 0; i_ < m; i_++) {
		i = p[i_];
		if(join(a[i], b[i]))
			tot += c[i];
	}
	printf("%lld\n", tot);
}
