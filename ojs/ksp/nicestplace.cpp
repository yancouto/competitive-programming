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


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef pii tA;
typedef null_type tB; // or null_type if you want a set
typedef tree<tA, tB, less<tA>, rb_tree_tag, tree_order_statistics_node_update> ord_set;
// map: tA -> tB com comparador less<tA>
// pode usar como um map normalmente
// s.find_by_order(k) :: retorna iterador para o k-esimo elemento (0-index) (ou s.end())
// s.order_of_key(x)  :: retorna a qtd de elementos estritamente menores que x

const int N = 512345;

int S[N], sz[N];
ord_set se[N];

int find(int i) {
	if(S[i] != S[S[i]]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
	for(pii p : se[b]) se[a].insert(p);
}

int a[N], b[N], d[N], p[N], q[N], pq[N], dq[N], kq[N], v[N];
int ans[N];


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int i, n, m, Q;
	cin >> n >> m >> Q;
	for(i = 0; i < n; i++)
		cin >> v[i];
	for(i = 0; i < m; i++) {
		cin >> a[i] >> b[i] >> d[i]; a[i]--; b[i]--;
		p[i] = i;
	}
	sort(p, p + m, [](int i, int j) { return d[i] < d[j]; });
	for(i = 0; i < Q; i++) {
		cin >> pq[i] >> dq[i] >> kq[i]; pq[i]--;
		q[i] = i;
	}
	sort(q, q + Q, [](int i, int j) { return dq[i] < dq[j]; });
	for(i = 0; i < n; i++) S[i] = i, sz[i] = 1, se[i].insert(pii(v[i], i));
	i = 0;
	for(int qi_ = 0; qi_ < Q; qi_++) {
		int qi = q[qi_];
		for(; i < m && d[p[i]] <= dq[qi]; i++)
			join(a[p[i]], b[p[i]]);
		int j = find(pq[qi]);
		if(kq[qi] > se[j].size()) ans[qi] = -1;
		else ans[qi] = se[j].find_by_order(sz[j] - kq[qi])->first;
	}
	for(i = 0; i < Q; i++)
		cout << ans[i] << '\n';
}
