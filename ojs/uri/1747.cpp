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
const int MAX = 10009;
vector<int> adj[MAX];
int x[MAX];
int mdc(int a, int b) {
	if(b == 0) return a;
	return mdc(b, a % b);
}
set<int> s;
void dfs(int u, int m) {
	s.insert(m);
	for(int v : adj[u])
		if(mdc(m, x[v]) != m)
			dfs(u, mdc(m, x[v]));
}

int main() {
	int i, n, m, a, b;
	scanf("%d %d", &n, &m);
	srand(time(NULL)); rand(); rand();
	for(i = 0; i < n; i++) {
		scanf("%d", &x[i]);
		//x[i] = (rand() % 10000) + 1;
	}
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		//a = (rand() % n) + 1; b = (rand() % n) + 1;
		adj[--a].pb(--b);
		adj[b].pb(a);
	}
	for(i = 0; i < n; i++)
		dfs(i, x[i]);
	printf("%d\n", (int)s.size());
}
