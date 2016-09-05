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

vector<int> adj[256];
bool seen[256];
int dfs(int a) {
	seen[a] = true;
	int tot = 1;
	for(int b : adj[a])
		if(!seen[b])
			tot += dfs(b);
	return tot;
}

char s[1000];
int main() {
	int i;
	for_tests(t, tt) {
		for(i = 'A'; i <= 'Z'; i++) adj[i].clear(), seen[i] = false;
		while(scanf(" %s", s) && s[0] != '*') {
			adj[s[1]].pb(s[3]);
			adj[s[3]].pb(s[1]);
		}
		scanf(" %s", s);
		int ac = 0, tr = 0;
		for(i = 0; !i || s[i-1] == ','; i += 2)
			if(!seen[s[i]]) {
				if(dfs(s[i]) == 1) ac++;
				else tr++;
			}
		printf("There are %d tree(s) and %d acorn(s).\n", tr, ac);
	}
}
