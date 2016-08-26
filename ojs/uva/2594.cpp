// incompleto
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
int ye[402][402];
vector<int> adj[802];

inline int vf(int v) { return v << 1; }
inline int vs(int v) { return vn(v) + 1; }

bool pos(int y) {
	int i, j;
	for(i = 0; i < n; i++) adj[i].clear(); 
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			if(ye[i][j] < y)
				adj[vs(i)].pb(vf(j)), adj[vs(j)].pb(vf(i));
			else
				adj[vf(i)].pb(vs(j)), adj[vf(j)].pb(vs(i));
	memset(seen, 0, sizeof seen);
	if(dfs();


}

int main() {
	while(scanf("%d %d", &n, &c) != EOF) {
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				ye[i][j] = 2008;
		for(i = 0; i < c; i++) {
			scanf("%d %d %d", &a, &b, &y); a--; b--;
			ye[a][b] = ye[b][a] = y;
		}
		for(i = 1948; i <= 2008; i++)
			if(pos(i))
				break;
		if(i <= 2008) printf("%d\n", i);
		else puts("Impossible");
	}

}
