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

int p[N], h[N], sz[N];
vector<int> adj[N];
int ch[N], ci[N], cs[N];

int dfs(int u, int h) {
	::h[u] = h;
	for(int v : adj[u])
		sz[u] += dfs(v, h + 1);
	return ++sz[u];
}

int *bit[N];

void add(int p, int i, int v) {
	for(i += 2; i < cs[p] + 5; i += (i & -i))
		bit[p][i] += v;
}

int get(int p, int i) {
	int sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum += bit[p][i];
	return sum;
}

void hld(int u, int p) {
	ch[u] = p;
	ci[u] = cs[p]++;
	if(adj[u].empty()) {
		// create bit
		bit[p] = new int[cs[p] + 5];
		for(int i = 0; i < cs[p] + 5; i++)
			bit[p][i] = 0;
		for(int i = 0; i < cs[p]; i++)
			add(p, i, 1);
		return;
	}
	int mx = 0, mi;
	for(int v : adj[u]) if(sz[v] > mx) mx = sz[v], mi = v;
	hld(mi, p);
	for(int v : adj[u])
		if(v != mi)
			hld(v, v);
}

int query(int a, int b) {
	int ans = 0;
	while(ch[a] != ch[b]) {
		if(h[ch[a]] < h[ch[b]]) swap(a, b);
		ans += get(ch[a], ci[a]);
		a = p[ch[a]];
	}
	if(ci[a] > ci[b]) swap(a, b);
	ans += get(ch[a], ci[b]) - get(ch[a], ci[a]) + 1;
	return ans;
}


int main() {
	int i, n, a, b, op;
	scanf("%d", &n);
	for(i = 1; i < n; i++) {
		scanf("%d", &p[i]); p[i]--;
		adj[p[i]].pb(i);
	}
	dfs(0, 0);
	hld(0, 0);
	for_tests(qi, qn) {
		scanf("%d %d", &op, &a); a--;
		if(op == 1) {
			scanf("%d", &b); b--;
			printf("%d\n", query(a, b) - 1);
		} else {
			add(ch[a], ci[a], -1);
		}
	}
}
