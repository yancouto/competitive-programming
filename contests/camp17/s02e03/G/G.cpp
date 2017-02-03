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

const int N = 1123;
vector<int> adj[N];
int ans;
int st[N], sn;
int d[N], low[N], t;
int seen[N], t2;
void dfs(int u) {
	st[sn++] = u;
	d[u] = low[u] = t++;
	seen[u] = t2;
	for(int v : adj[u])
		if(seen[v] == t2) {
			low[u] = min(low[u], d[v]);
		} else {
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
	if(low[u] >= d[u]) {
		int sz = 0, a;
		do {
			a = st[--sn];
			sz++;
			d[a] = low[a] = INT_MAX;
		} while(a != u);
		ans = max(ans, sz);
	}
}

int go() {
	ans = 0;
	t = 0;
	t2++;
	for(int i = 0; i < n; i++)
		if(seen[i] != t2)
			dfs(i);
	return ans;
}

const int M = 21234;
int w[M], a[M], b[M];

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int i, j, m;
	rd(n); rd(m);
	for(i = 0; i < m; i++) {
		rd(a[i]); rd(b[i]); a[i]--; b[i]--;
		adj[a[i]].pb(b[i]);
	}
	int mx = go(), ms = 0;
	for(i = 0; i < m; i++) {
		adj[b[i]].pb(a[i]);
		w[i] = go();
		//printf("i %d w %d\n", i, w[i]);
		if(w[i] > mx) ms = 1, mx = w[i];
		else if(w[i] == mx) ms++;
		adj[b[i]].pop_back();
	}
	printf("%d\n%d\n", mx, ms);
	for(i = 0; i < m; i++)
		if(w[i] == mx)
			printf("%d ", i + 1);
	putchar('\n');
}
