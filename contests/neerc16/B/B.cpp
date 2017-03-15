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

const int N = 4000009;
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
vector<int> q[2*M];
int Q[M];
int E = 0;
int fn;

void imp() {
	puts("NO");
	exit(0);
}

void go(const char *s, int u, int x, bool b) {
	if(!s[0]) {
		if(b) {
			if(tr[u][0]) adj[x].pb(2 * n + tr[u][0]);
			if(tr[u][1]) adj[x].pb(2 * n + tr[u][1]);
			if(u) adj[x].pb(2 * n + en + p[u]);
			adj[2 * n + en + u].pb(x ^ 1);
		} else {
			adj[2 * n + u].pb(x ^ 1);
			q[u].pb(Q[x / 2]);
		}
		if(!b) ot[u].pb(x);
		else if(q[u].size() > 1) {
			sort(q[u].begin(), q[u].end());
			if(q[u][0] == q[u][1] && q[u][0] == -1) imp();
			for(int i = 0; i < int(ot[u].size()) - 2; i++)
				if(q[u][i] == q[u][i + 1] && q[u][i] == q[u][i + 2])
					imp();
			for(int i = 0; i < ot[u].size(); i++) {
				adj[fn + i].pb(ot[u][i] ^ 1);
				if(i < int(ot[u].size()) - 1) adj[fn + i].pb(fn + i + 1);
				adj[fn + ot[u].size() + i].pb(ot[u][i] ^ 1);
				if(i) adj[fn + ot[u].size() + i].pb(fn + ot[u].size() + i - 1);
			}
			for(int i = 0; i < ot[u].size(); i++) {
				if(i < int(ot[u].size()) - 1) adj[ot[u][i]].pb(fn + i + 1);
				if(i) adj[ot[u][i]].pb(fn + ot[u].size() + i - 1);
			}
			fn += 2 * ot[u].size();
		}
	}
	if(s[0] == '?' || s[0] == '0') {
		if(!tr[u][0]) {
			tr[u][0] = en++;
			adj[2 * n + u].pb(2 * n + tr[u][0]);
			p[tr[u][0]] = u;
		}
		go(s + 1, tr[u][0], x, b);
	}
	if(s[0] == '?' || s[0] == '1') {
		if(!tr[u][1]) {
			tr[u][1] = en++;
			adj[2 * n + u].pb(2 * n + tr[u][1]);
			p[tr[u][1]] = u;
		}
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
		if(!strchr(str, '?'))
			adj[2 * i + 1].pb(2 * i), Q[i] = -1;
		else Q[i] = strchr(str, '?') - str;
		go(str, 0, 2 * i, false);
		s[i] = str;
	}
	for(i = 1; i < en; i++) adj[2 * n + i + en].pb(2 * n + p[i] + en);
	fn = 2 * n + 2 * en;
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
