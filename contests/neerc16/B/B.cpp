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

const int N = 3000009;
const int M = 500009;
int n;
char str[N];

#define real alshalsdfh
vector<int> adj[N];

int st[N], sn = 0, tempo = 0;
int cn = 0;
int c[N];
bool mrk[N], real[N];
int d[N], low[N];
bool seen[N];

void dfs(int u) {
	st[sn++] = u;
	d[u] = low[u] = tempo++;
	seen[u] = true;
	for(int v : adj[u])
		if(seen[v])
			low[u] = min(low[u], d[v]);
		else {
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
	if(d[u] == low[u]) {
		cn++;
		int x = -1, sz = 0;
		bool any = false;
		do {
			sz++;
			x = st[--sn];
			c[x] = cn;
			low[x] = d[x] = INT_MAX;
			if(x < 2 * n && c[x ^ 1] == cn) {
				puts("NO");
				exit(0);
			}
			if(x < 2 * n && mrk[x / 2]) any = true;
		} while(x != u);
		if(any) return;
		while(sz--) {
			x = st[sz + sn];
			if(x >= 2 * n) continue;
			mrk[x / 2] = true;
			real[x / 2] = (x & 1);
		}
	}
}

int tr[2*M][2], en = 1;
int p[2*M];
vector<int> ot[2*M];
int E = 0;

void go(const char *s, int u, int x, bool b) {
	if(!s[0]) {
		if(b) {
			if(tr[u][0]) adj[x].pb(2 * n + tr[u][0]), E++;
			if(tr[u][1]) adj[x].pb(2 * n + tr[u][1]), E++;
			if(u) adj[x].pb(2 * n + en + p[u]), E++;
			adj[2 * n + en + u].pb(x ^ 1), E++;
		} else {
			adj[2 * n + u].pb(x ^ 1), E++;
		}
		if(!b) ot[u].pb(x);
		else {
			for(int i = 0; i < ot[u].size(); i++)
				for(int j = 0; j < ot[u].size(); j++)
					if(i != j) {
						adj[ot[u][i]].pb(ot[u][j] ^ 1), E++;
						if(E > 51934567) {
							puts("NO");
							exit(0);
						}
					}
		}
	}
	if(s[0] == '?' || s[0] == '0') {
		if(!tr[u][0]) {
			tr[u][0] = en++;
			adj[2 * n + u].pb(2 * n + tr[u][0]), E++;
			p[tr[u][0]] = u;
		}
		if(b) adj[2 * n + en + tr[u][0]].pb(2 * n + en + u), E++;
		go(s + 1, tr[u][0], x, b);
	}
	if(s[0] == '?' || s[0] == '1') {
		if(!tr[u][1]) {
			tr[u][1] = en++;
			adj[2 * n + u].pb(2 * n + tr[u][1]), E++;
			p[tr[u][1]] = u;
		}
		if(b) adj[2 * n + en + tr[u][1]].pb(2 * n + en + u), E++;
		go(s + 1, tr[u][1], x + (s[0] == '?'), b);
	}
}

string s[M];

int main() {
#ifdef ONLINE_JUDGE
	freopen("binary.in", "r", stdin);
	freopen("binary.out", "w", stdout);
#endif
	int i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%s", str);
		go(str, 0, 2 * i, false);
		if(!strchr(str, '?'))
			adj[2 * i + 1].pb(2 * i);
		s[i] = str;
	}
	for(i = 0; i < n; i++)
		go(s[i].c_str(), 0, 2 * i, true);
	for(i = 0; i < 2 * n + 2 * en; i++)
		if(!seen[i])
			dfs(i);
	puts("YES");
	for(i = 0; i < n; i++) {
		for(j = 0; j < s[i].size(); j++)
			if(s[i][j] != '?') putchar(s[i][j]);
			else putchar('0' + real[i]);
		putchar('\n');
	}
}
