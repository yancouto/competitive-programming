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

int gcd(int a, int b) {
	if(b == 0) return a;
	return gcd(b, a % b);
}

int n;
const int N = 212345;
int mx[N], A[N];
vector<int> adj[N];
unordered_set<int> mp[N][2];
void go(int u, int p, int val, bool can) {
	if(mp[u][can].count(val)) return;
	mp[u][can].insert(val);
	int gval = gcd(val, A[u]);
	mx[u] = max(mx[u], gval);
	if(can) mx[u] = max(mx[u], val);
	for(int v : adj[u]) {
		if(v == p) continue;
		go(v, u, gval, can);
		if(can) go(v, u, val, false);
	}
}

int main() {
	int i, a, b;
	rd(n);
	for(i = 1; i <= n; i++) rd(A[i]);
	for(i = 0; i < n - 1; i++) {
		rd(a); rd(b);
		adj[a].pb(b);
		adj[b].pb(a);
	}
	go(1, -1, 0, 1);
	for(i = 1; i <= n; i++) printf("%d%c", mx[i], " \n"[i == n]);
}
