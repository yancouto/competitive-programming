#include <bits/stdc++.h>
using namespace std;
#define a first
#define b second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define lld I64d
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif
const int N = 112345;

int es[N], to[N], nx[N], fl[N], en = 2;
void add_edge(int a, int b) {
	to[en] = a; nx[en] = es[b]; es[b] = en++;
	to[en] = b; nx[en] = es[a]; es[a] = en++;
}

int seen[N], tempo;
bool dfs(int u, int t) {
	if(u == t) return true;
	if(seen[u] == tempo) return false;
	seen[u] = tempo;
	for(int e = es[u]; e; e = nx[e])
		if((e & 1) - fl[e] && dfs(to[e], t)) {
			fl[e]++;
			fl[e ^ 1]--;
			return true;
		}
	return false;
}

int max_flow(int a, int b) {
	int fl = -1;
	do tempo++, fl++; while(dfs(a, b));
	return fl;
}


map<string, int> mp;
pii get() {
	string s, s2;
	char c;
	while(isspace(c = getchar()));
	s += c;
	while((c = getchar()) != ',') s += c;
	while(isspace(s.back())) s.pop_back();
	while(isspace(c = getchar()));
	s2 += c;
	while((c = getchar()) != '\n') s2 += c;
	while(isspace(s2.back())) s2.pop_back();
	if(!mp.count(s)) mp[s] = mp.size() - 1;
	if(!mp.count(s2)) mp[s2] = mp.size() - 1;
	return pii(mp[s], mp[s2]);

}
int mrk[N], o[N], A[N], B[N];
pii r[N];
vector<int> inv[N], ans[N];
int main() {
	int i, j, n, m;
	scanf("%d %d ", &n, &m);
	for(i = 0; i < n; i++) {
		r[i] = get();
		mrk[r[i].a] = mrk[r[i].b] = 1;
		o[r[i].a] = r[i].b;
	}
	map<pii, int> ar;
	for(i = 0; i < m; i++) {
		pii q = get();
		ar[q] = i + 1;
		ar[pii(q.b, q.a)] = i + 1;
		inv[q.b].pb(q.a);
		inv[q.a].pb(q.b);
	}
	int ct = 0;
	for(i = 0; i < n; i++) {
		A[r[i].b]++;
		if(ar.count(r[i]) && !B[ar[r[i]]]) {
			ans[r[i].a].pb(ar[r[i]]);
			B[ar[r[i]]] = 1;
		} else {
			ct++;
			add_edge(mp.size(), r[i].a);
			for(int x : inv[r[i].b])
				if(!mrk[x] && ar.count(pii(r[i].a, x)))
					add_edge(r[i].a, x);
		}
	}
	for(i = 0; i < mp.size() && A[i] <= 1; i++);
	if(i < mp.size()) { puts("NO"); return 0; }
	for(i = 0; i < mp.size(); i++)
		if(!mrk[i])
			add_edge(i, mp.size() + 1);
	int f = max_flow(mp.size(), mp.size() + 1);
	if(f != ct) { puts("NO"); return 0; }
	for(int e = es[mp.size()]; e; e = nx[e]) {
		assert(fl[e] == 1); int e2;
		for(e2 = es[to[e]]; fl[e2] != 1; e2 = nx[e2]);
		ans[to[e]].pb(ar[pii(to[e], to[e2])]);
		ans[to[e]].pb(ar[pii(to[e2], o[to[e]])]);
	}
	puts("YES");
	for(i = 0; i < n; i++) {
		printf("%d", (int) ans[r[i].a].size());
		for(int x : ans[r[i].a])
			printf(" %d", x);
		putchar('\n');
	}
}
