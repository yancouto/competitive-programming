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

vector<int> adj[1123];
int pos[1123];
int main() {
	int i, n, m, a, b, x;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		adj[a].pb(b);
	}
	for(i = 0; i < n; i++) {
		scanf("%d", &x);
		pos[x] = i;
	}
	bool bad = false;
	for(i = 1; i <= n; i++)
		for(int x : adj[i])
			if(pos[x] <= pos[i])
				bad = true;
	if(bad) puts("NO");
	else puts("YES");
}
