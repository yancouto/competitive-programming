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

bool seen[102];
int d[102], low[102], tempo, mx = 0;
int st[102], sn;
vector<int> adj[102];
void dfs(int u) {
	if(seen[u]) return;
	seen[u] = true;
	d[u] = low[u] = tempo++;
	st[sn++] = u;
	for(int v : adj[u]) {
		dfs(v);
		low[u] = min(low[u], low[v]);
	}
	if(low[u] >= d[u]) {
		int sz = 0, a;
		do {
			a = st[--sn];
			low[a] = INT_MAX;
			sz++;
		} while(a != u);
		mx = max(mx, sz);
	}
}


map<string, int> mp;
int get(string s) {
	if(!mp.count(s))
		mp[s] = mp.size() - 1;
	return mp[s];
}

int sp[102];
set<int> ls[102];
char line[1000009];
int main() {
	int i, j, n;
	fgets(line, sizeof line, stdin);
	sscanf(line, "%d", &n);
	for(i = 0; i < n; i++) {
		fgets(line, sizeof line, stdin);
		char *c = strtok(line, " \n");
		c = strtok(NULL, " \n");
		sp[i] = get(c);
		while(c) {
			ls[i].insert(get(c));
			c = strtok(NULL, " \n");
		}
	}
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			if(i != j && ls[j].count(sp[i]))
				adj[i].pb(j);
	for(i = 0; i < n; i++)
		dfs(i);
	printf("%d\n", n - mx);
}
