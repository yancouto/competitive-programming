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

const int N = 112345;

int S[N], sz[N], val[N], ok[N], a[N], p[N];

int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	assert(ok[a] && ok[b]);
	assert((a = find(a)) != (b = find(b)));
	if(sz[a] < sz[b]) swap(a, b);
	S[b] = a;
	sz[a] += sz[b];
	val[a] = min(val[a], val[b]);
}

int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		p[i] = i;
		S[i] = i;
		val[i] = a[i];
		sz[i] = 1;
		ok[i] = 0;
	}
	sz[0] = n;
	sort(p, p + n, [](int i, int j) { return a[i] > a[j]; });
	ll tot = 0;
	for(int i_ = 0; i_ < n; i_++) {
		i = p[i_];
		ok[i] = 1;
		if(i && ok[i - 1]) {
			tot += !!(val[find(i - 1)] - a[i]);
			join(i, i - 1);
		}
		if(ok[i + 1]) {
			tot += !!(val[find(i + 1)] - a[i]);
			join(i, i + 1);
		}
	}
	printf("%lld\n", tot + !!val[find(0)]);
}
