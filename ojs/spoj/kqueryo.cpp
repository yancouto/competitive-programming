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
const int MAX = 30009;
int a[MAX];
vector<int> t[MAX << 2];

inline int l(int i) { return i << 1; }
inline int r(int i) { return (i << 1) + 1; }

void build(int i, int le, int ri) {
	if(le == ri) {
		t[i].pb(a[le]);
		return;
	}
	int mi = (le + ri) / 2;
	build(l(i), le, mi);
	build(r(i), mi + 1, ri);
	t[i].resize(ri - le + 1);
	merge(t[l(i)].begin(), t[l(i)].end(), t[r(i)].begin(), t[r(i)].end(), t[i].begin());
}

int query(int i, int le, int ri, int ql, int qr, int k) {
	if(le > qr || ri < ql) return 0;
	if(le >= ql && ri <= qr) return t[i].end() - lower_bound(t[i].begin(), t[i].end(), k);
	int mi = (le + ri) / 2;
	return query(l(i), le, mi, ql, qr, k) + query(r(i), mi + 1, ri, ql, qr, k);
}

int main() {
	int i, n, q, a, b, c;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d", &::a[i]);
	build(1, 0, n - 1);
	int l = 0;
	scanf("%d", &q);
	for(i = 0; i < q; i++) {
		scanf("%d %d %d", &a, &b, &c);
		l = query(1, 0, n - 1, (a ^ l) - 1, (b ^ l) - 1, (c ^ l) + 1);
		printf("%d\n", l);
	}
	return 0;
}
