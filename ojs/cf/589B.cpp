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

int a[4009], b[4009];
vector<int> v[1000009];
vector<int> acc[1000009];
int main() {
	int n, i, j;
	scanf("%d", &n);
	int xs[8009], xn = 0;
	for(i = 0; i < n; i++) {
		scanf("%d %d", &a[i], &b[i]);
		if(a[i] > b[i]) swap(a[i], b[i]);
		xs[xn++] = a[i];
		xs[xn++] = b[i];
	}
	sort(xs, xs + xn);
	xn = unique(xs, xs + xn) - xs;
	pii ps[8009]; int sz;
	for(i = 0; i < n; i++) {
		sz = 0;
		for(j = 0; j < n; j++) {
			ps[sz++] = pii(min(a[i], a[j]), min(b[i], b[j]));
			if(ps[sz-1].fst > ps[sz-1].snd) swap(ps[sz-1].fst, ps[sz-1].snd);
			ps[sz++] = pii(min(a[i], b[j]), min(b[i], a[j]));
			if(ps[sz-1].fst > ps[sz-1].snd) swap(ps[sz-1].fst, ps[sz-1].snd);
		}
		sort(ps, ps + sz);
		sz = unique(ps, ps + sz) - ps;
		for(j = 0; j < sz; j++)
			v[ps[j].fst].pb(ps[j].snd);
	}
	for(i = 0; i < xn; i++) {
		vector<int> &vv = v[xs[i]];
		sort(vv.begin(), vv.end());
		vv.resize(unique(vv.begin(), vv.end()) - vv.begin());
		for(j = 0; j < vv.size() + 1; j++)
			acc[xs[i]].pb(0);
	}
	for(i = 0; i < n; i++) {
		for(j = 0; j < xn && xs[j] <= a[i]; j++) {
			int p = upper_bound(v[xs[j]].begin(), v[xs[j]].end(), b[i]) - v[xs[j]].begin();
			acc[xs[j]][0]++; acc[xs[j]][p]--;
		}
	}
	ll best = 0; int bw, bh;
	for(i = 0; i < xn; i++) {
		int s = 0;
		for(j = 0; j < v[xs[i]].size(); j++) {
			s += acc[xs[i]][j];
			ll b = ll(xs[i]) * ll(v[xs[i]][j]) * ll(s);
			if(b > best) {
				best = b;
				bw = xs[i];
				bh = v[xs[i]][j];
			}
		}

	}
	printf("%I64d\n%d %d\n", best, bw, bh);
}
