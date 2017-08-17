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
int st[N], sn;

int cn;
deque<int> C[N];
set<int> adj[N];
set<int> bad[N];
set<int> cs[N];

int seen[N];

void dfs(int u, int p) {
	st[sn++] = u;
	seen[u] = true;
	for(int v : adj[u]) {
		if(v == p || bad[u].count(v)) continue;
		if(!seen[v]) { dfs(v, u); }
		else {
			C[cn].pb(v); cs[v].insert(cn);
			bad[v].insert(u);
			bad[u].insert(v);
			for(int i = sn - 1; st[i] != v; i--) {
				C[cn].pb(st[i]);
				cs[st[i]].insert(cn);
				bad[st[i]].insert(st[i - 1]);
				bad[st[i - 1]].insert(st[i]);
			}
			cn++;
		}
	}
	sn--;
}

struct op {
	char id;
	int a, b, c;
};

vector<op> ops;

void shift(deque<int> &c, int u) {
	while(c.front() != u) {
		c.push_back(c.front());
		c.pop_front();
	}
}

// cria o cactus rooteado em u
// com u com cor 1 e resto com cor 2
void get(int u, int ci=-1) {
	deque<int> c;
	if(ci == -1) {
		c.push_back(u);
	} else {
		c = C[ci];
		c.pop_front();
		for(int x : c)
			cs[x].erase(ci);
	}
	for(int u : c) {
		for(int v : adj[u]) {
			adj[v].erase(u);
			get(v, -1);
			ops.push_back(op{'r', v, 1, 3});
			ops.push_back(op{'j', v, u, 0});
			ops.push_back(op{'c', u, 1, 3});
			ops.push_back(op{'r', u, 3, 2});
		}
		for(int cci : cs[u]) {
			shift(C[cci], u);
			int v = C[cci][1];
			get(v, cci);
			ops.push_back(op{'r', v, 1, 3});
			ops.push_back(op{'j', v, u, 0});
			ops.push_back(op{'c', u, 1, 3});
			ops.push_back(op{'r', u, 3, 2});
		}
	}
	if(c.size() == 1) return;
	ops.push_back(op{'r', c[1], 1, 3});
	ops.push_back(op{'j', c[0], c[1], 0});
	ops.push_back(op{'c', c[0], 1, 3});
	for(int i = 2; i < int(c.size()); i++) {
		ops.push_back(op{'r', c[i], 1, 4});
		ops.push_back(op{'j', c[0], c[i], 0});
		ops.push_back(op{'c', c[0], 3, 4});
		ops.push_back(op{'r', c[0], 3, 2});
		ops.push_back(op{'r', c[0], 4, 3});
	}
	ops.push_back(op{'r', c[0], 3, 1});
}


int main() {
#ifdef ONLINE_JUDGE
	freopen("cactus.in", "r", stdin);
	freopen("cactus.out", "w", stdout);
#endif
	int i, n, m, k, a, b;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d", &k);
		scanf("%d", &a);
		while(--k) {
			scanf("%d", &b);
			adj[a].insert(b); adj[b].insert(a);
			a = b;
		}
	}
	for(i = 1; i <= n; i++)
		if(!seen[i])
			dfs(i, -1);
	for(i = 1; i <= n; i++)
		for(int x : bad[i])
			adj[i].erase(x);
	get(1, -1);
	printf("%d\n", int(ops.size()));
	for(op o : ops) {
		printf("%c %d %d", o.id, o.a, o.b);
		if(o.id == 'c' || o.id == 'r') printf(" %d", o.c);
		putchar('\n');
	}
}
