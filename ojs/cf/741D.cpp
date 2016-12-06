#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

int n;
const int N = 512345;
unordered_map<int, int> mp[N];
int best[N];
vector<pii> adj[N];

void dfs(int u, int cur, int d) {
	mp[u][cur] = d;
	for(pii e : adj[u]) {
		int v = e.fst;
		dfs(v, cur ^ (1 << e.snd), d + 1);
		best[u] = max(best[u], best[v]);
		if(mp[u].size() < mp[v].size()) mp[u].swap(mp[v]);
		for(pii k : mp[v]) {
			for(int g = 0; g < 22; g++) {
				auto it = mp[u].find((1 << g) ^ k.fst);
				if(it == mp[u].end()) continue;
				best[u] = max(best[u], k.snd + it->snd - 2 * d);
			}
			auto it = mp[u].find(k.fst);
			if(it == mp[u].end()) continue;
			best[u] = max(best[u], k.snd + it->snd - 2 * d);
		}
		for(pii k : mp[v])
			mp[u][k.fst] = max(mp[u][k.fst], k.snd);
	}
}

int main() {
	int i, j;
	rd(n);
	for(i = 1; i < n; i++) {
		int p;
		rd(p); p--;
		char c = getchar();
		adj[p].pb(pii(i, c - 'a'));
	}
	dfs(0, 0, 0);
	for(i = 0; i < n; i++) printf("%d ", best[i]);
	putchar('\n');
}
