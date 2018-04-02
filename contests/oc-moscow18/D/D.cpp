#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, int> pii;
#define pb push_back

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef ll tA;
typedef null_type tB;

typedef tree<tA, tB, less<tA>, rb_tree_tag, tree_order_statistics_node_update> ord_set;
// map: tA -> tB com comparador less<tA>
// pode usar como um map normalmente
// s.find_by_order(k) :: retorna iterador para o k-esimo elemento (0-index) (ou s.end())
// s.order_of_key(x)  :: retorna a qtd de elementos estritamente menores que x

struct ev {
	ll t;
	char where;
	ll rm, add;
	bool operator < (ev o) const {
		if(t != o.t)
			return t < o.t;
		return where < o.where;
	}
};

const int N = 112345;
int a[N], p[N]; ll t[N];
int ans[N];

int main() {
	int i, n, q; ll l;
	scanf("%d %lld", &n, &l);
	ord_set L, R;
	vector<ev> evs;
	for(i = 0; i < n; i++) {
		int x; char c;
		scanf("%d %c", &x, &c);
		if(c == 'L') {
			L.insert(x);
			evs.pb(ev{x, 'L', x, -x});
			evs.pb(ev{x + l, 'R', -x, l + x + l});
		} else {
			R.insert(x);
			evs.pb(ev{l - x, 'R', x, l + (l - x)});
			evs.pb(ev{l + (l - x), 'L', l + (l - x), -(l + (l - x))});
		}
	}
	evs.pb(ev{2 * l, '0', 0, 0});
	scanf("%d", &q);
	for(i = 0; i < q; i++) {
		scanf("%d %lld", &a[i], &t[i]); a[i]--;
		t[i] %= 2ll * l;
		p[i] = i;
	}
	sort(p, p + q, [](int i, int j) { return t[i] < t[j]; });
	int j_ = 0;
	sort(evs.begin(), evs.end());
	for(ev e : evs) {
		//printf("ev at %lld\n", e.t);
		//printf("L:");
		//for(ll x : L) printf(" %lld", x);
		//printf("\nR:");
		//for(ll x : R) printf(" %lld", x);
		//printf("\n");
		for(; j_ < q && t[p[j_]] <= e.t; j_++) {
			int j = p[j_];
			ll l_ = 0, r_ = l;
			while(l_ < r_) {
				ll m = (l_ + r_ + 1) / 2;
				if(int(L.order_of_key(m + t[j]) + R.order_of_key(m - t[j])) <= a[j]) l_ = m;
				else r_ = m - 1;
			}
			ans[j] = l_;
			//printf("%d-th at time %lld is %d\n", a[j], t[j], ans[j]);
		}
		if(e.where == 'L') {
			L.erase(e.rm);
			R.insert(e.add);
		} else if(e.where == 'R') {
			R.erase(e.rm);
			L.insert(e.add);
		}
	}
	for(i = 0; i < q; i++)
		printf("%d\n", ans[i]);
}
