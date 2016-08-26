// INCOMPLETE
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

double rnd() { return double(rand()) / RAND_MAX; }
struct no;
no *nil;

struct no {
	no() : l(nil), r(nil), sz(1), lz(0), sum(0), val(0) {}
	no *l, *r;
	int sz;
	ll lz, sum, val;
};

no* acc(no *u) {
	if(u == nil || !u->lz) return u;
	node *v = cp(u);

}

no* cp(no *u) {
	no *v = new node;
	*v = *u;
	return v;
}

no* calc(no *u) {
	u->sz = u->l->sz + 1 + u->r->sz;
	u->sum = u->l->sum + u->val + u->r->sum;
	return u;
}

no* merge(no *l, no *r) {
	if(l == nil) return r;
	if(r == nil) return l;
	no *u;
	if(rnd() * (l->sz + r->sz) <= l->sz) u = cp(l), u->r = merge(l->r, r);
	else u = cp(r), u->l = merge(l, r->l);
	return calc(u);
}

int main() {
	nil = new node;
	nil->l = nil->r = nil;
	nil->sz = 0;
	for_tests(t, tt) {
		scanf("%d", &n);
		root = new node;
		for(i = 0; i < 17; i++)
			root = merge(root, root);
		for_tests(qn, qc) {

		}
	}
}
