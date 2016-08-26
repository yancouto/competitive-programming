#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
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

const int N = 1123;

vector<int> adj[N];
char c[N];

void dfs(int u, int sp) {
	for(int i = 0; i < sp; i++) putchar(' ');
	if(u) printf("%c object%d\n", c[u], u);
	else printf("%c project\n", c[u]);
	if(c[u] == '-')
		for(int v : adj[u])
			dfs(v, sp + 2);
}

int main() {
	int i, j, n, k, x;
	scanf("%d", &n);
	for(i = 0; i <= n; i++) {
		scanf(" %c %d", &c[i], &k);
		if(k == 0) c[i] = ' ';
		for(j = 0; j < k; j++) {
			scanf("%d", &x);
			adj[i].pb(x);
		}
	}
	dfs(0, 0);
}
