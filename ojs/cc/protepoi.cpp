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

bool inter(int a, int b, int l, int r) {
	if(a > b) swap(a, b);
	return !(b < l || a > r);
}

bool bad;
int solve(vector<pii> &v, int l, int r) {
	sort(v.begin(), v.end());
	int i = 0, ct = 0;
	while(l <= r) {
		int j = i;
		int mr = l;
		while(i < v.size() && v[i].fst <= l) mr = max(mr, v[i++].snd);
		if(i == j) { bad = true; return -1e8; }
		l = mr + 1;
		ct++;
	}
	return ct;
}

int main() {
	int i, n, k, m, a1, b1, a2, b2;
	for_tests(t, tt) {
		scanf("%d %d %d", &n, &k, &m);
		int l = (n - k) / 2 + 1;
		int r = l + k - 1;
		vector<pii> v1, v2;
		for(i = 0; i < m; i++) {
			scanf("%d %d %d %d", &a1, &b1, &a2, &b2);
			if(inter(a1, a2, l, r))
				v1.pb(pii(max(min(a1, a2), l), min(r, max(a1, a2))));
			else if(inter(b1, b2, l, r))
				v2.pb(pii(max(min(b1, b2), l), min(r, max(b1, b2))));
		}
		bad = false;
		int A = solve(v1, l, r), B = solve(v2, l, r);
		if(bad) puts("-1");
		else printf("%d\n", A + B);
	}
}
