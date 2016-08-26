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
const int N = 112345;
char op[N];
int l[N], r[N], b[N], id[N], sz[N];
ll val[N];

struct inter {
	ll l, r;
	ll val() { return (ll(l + r) * ll(sz())) / 2ll; }
	ll sz() { return abs(r - l) + 1; }
	bool brk(vector<inter> &v, int &s) {
		s -= sz();
		if(s == 0) { s = 1e9 + 10; v.pb(*this); return true; }
		if(s > 0) { v.pb(*this); return false; }
		s += sz();
		if(l <= r) {
			v.pb({l, l + s - 1});
			v.pb({l + s, r});
			assert(l <= l + s - 1 && l + s <= r);
		} else {
			v.pb({l, l - s + 1});
			v.pb({l - s, r});
			assert(l >= l - s + 1 && l - s >= r);
		}
		s = 1e9 + 10;
		return true;
	}
	void swap(inter &o) {
		std::swap(l, o.r);
		std::swap(o.l, r);
	}
};

int break_at(vector<inter> &v, int s) {
	if(s == 0) return -1;
	vector<inter> nv;
	int j = -1;
	for(int i = 0; i < v.size(); i++)
		if(v[i].brk(nv, s))
			assert(j == -1), j = i;
	assert(j != -1);
	nv.swap(v);
	return j;
}

void deb(vector<inter> &v) {
	return;
	for(inter i : v)
		printf("(%d->%d) ", i.l, i.r);
	putchar('\n');
}

int main() {
	int i, n, m, j, bn = 0, sn = 0, L, R;
	scanf("%d %d", &n, &m);
	vector<inter> v;
	v.pb({1ll, n});
	for(i = 0; i < m; i++) {
		scanf(" %c %d %d", &op[i], &L, &R);
		//printf("%c %d %d\n", op[i], L, R);
		int l = break_at(v, L - 1) + 1;
		//puts("FIRST BREAK");
		deb(v);
		int r = break_at(v, R);
		//puts("SECOND BREAK");
		deb(v);
		//printf("FROM %d TO %d\n", l, r);
		for(j = 0; j < v.size(); j++)
			assert(v[j].sz() > 0);
		if(op[i] == 'I') {
			for(; l < r; l++, r--)
				v[l].swap(v[r]);
			if(l == r) swap(v[l].l, v[l].r);
		} else {
			ll tot = 0;
			for(; l <= r; l++)
				tot += v[l].val();
			printf("%lld\n", tot);
		}
		//puts("FINAL");
		deb(v);
	}
}
