#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; cin >> t; for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef int tA;
typedef null_type tB; // or null_type if you want a set
typedef tree<tA, tB, less<tA>, rb_tree_tag, tree_order_statistics_node_update> ord_set;
// map: tA -> tB com comparador less<tA>
// pode usar como um map normalmente
// s.find_by_order(k) :: retorna iterador para o k-esimo elemento (0-index) (ou s.end())
// s.order_of_key(x)  :: retorna a qtd de elementos estritamente menores que x


const int N = 112345;

ord_set tr[N << 2];
int query(int i, int l, int r, int ql, int qr, int x) {
	if(l > qr || r < ql) return 0;
	if(l >= ql && r <= qr)
		return tr[i].order_of_key(x + 1);
	int m = (l + r) / 2;
	return query(2 * i, l, m, ql, qr, x) + query(2 * i + 1, m + 1, r, ql, qr, x);
}

void mod(int i, int l, int r, int p, int x, bool add) {
	if(add) tr[i].insert(x);
	else tr[i].erase(x);
	if(l == r) return;
	int m = (l + r) / 2;
	if(p <= m) mod(2 * i, l, m, p, x, add);
	else mod(2 * i + 1, m + 1, r, p, x, add);
}

int n;

int solve(int L, int R) {
	int l = 1, r = n;
	while(l < r) {
		int m = (l + r) / 2;
		if(query(1, 1, n, L, R, m) < m) r = m;
		else l = m + 1;
	}
	return l;
}

int mn[N], a[N];

map<int, int> dif[N];
multiset<pii> es;

bool ok() {
	int i;
	for(i = 0; i <= n; i++) dif[i].clear();
	map<int, int> cur;
	int tot = 0;
	for(i = n; i >= 0; i--) {
		dif[i] = cur;
		tot += cur.size();
		if(tot > int(es.size())) return false;
		cur[a[i]] = i;
	}
	for(i = 0; i <= n; i++)
		for(pii p : dif[i]) {
			auto it = es.find(pii(i, p.snd));
			if(it == es.end()) return false;
			es.erase(it);
		}
	return es.empty();
}

int main() {
	int i, m;
	ios::sync_with_stdio(0); cin.tie(0);
	for_tests(tn, tt) {
		cin >> n >> m;
		es.clear();
		for(i = 1; i <= n; i++) mn[i] = INT_MAX;
		for(i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			es.insert(pii(a, b));
			mn[b] = min(mn[b], a);
		}
		int cur = 0;
		for(i = 1; i <= n; i++) {
			if(mn[i] > i - 1) break;
			if(mn[i] == 0) a[i] = ++cur;
			else a[i] = a[mn[i]];
		}
		if(i <= n || !ok()) { cout << "-1\n"; continue; }
		for(i = 1; i <= n; i++) cout << a[i] << " \n"[i == n];
	}
}
