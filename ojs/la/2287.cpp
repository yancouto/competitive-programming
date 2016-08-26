#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

char str[6000000];
vector<int> adj[140000];
int ns = 0, val[140000];
int read_node(char *&s) {
	int u = ns++;
	adj[u].clear();
	if(*s == '[') {
		int l = read_node(++s);
		int r = read_node(++s);
		++s;
		adj[u].pb(l);
		adj[u].pb(r);
	} else {
		val[u] = atoi(s);
		while(isdigit(*s)) s++;
	}
	return u;
}

ull st[140000]; int sn;
void dfs(int u, ull p) {
	if(adj[u].empty()) {
		st[sn++] = p * ull(val[u]);
	}
	else
		for(int i = 0; i < adj[u].size(); i++)
			dfs(adj[u][i], p * 2);
}

int main() {
	int i;
	for_tests(t, tt) {
		scanf("%s", str);
		char *s = str; ns = sn = 0;
		int u = read_node(s);
		dfs(u, 1);
		map<ull, int> mp;
		for(i = 0; i < sn; i++)
			mp[st[i]]++;
		int mx = 0;
		for(map<ull, int>::iterator it = mp.begin(); it != mp.end(); ++it)
			mx = max(mx, it->snd);
		printf("%d\n", sn - mx);
	}
	return 0;
}
