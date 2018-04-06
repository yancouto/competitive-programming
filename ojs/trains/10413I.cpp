#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int NS = 1; const int N = 412345 * 2;
int cn, cd, ns, en = 1, lst;
string S[NS]; int si = -1;
vector<int> sufn[NS]; // sufn[si][i] no do sufixo S[si][i...]
struct node {
	int l, r, si, p, suf;
	map<char, int> adj;
	node() : l(0), r(-1), suf(0), p(0) {}
	node(int L, int R, int S, int P) : l(L), r(R), si(S), p(P) {}
	inline int len() { return r - l + 1; }
	inline int operator[](int i) { return S[si][l + i]; }
	inline int& operator()(char c) { return adj[c]; }
} t[N];
inline int new_node(int L, int R, int S, int P) { t[en] = node(L, R, S, P); return en++; }
void add_string(string s) {
	s += '$'; S[++si] = s; sufn[si].resize(s.size() + 1); cn = cd = 0;
	int i = 0; const int n = s.size();
	for(int j = 0; j < n; j++)
		for(; i <= j; i++) {
			if(cd == t[cn].len() && t[cn](s[j])) { cn = t[cn](s[j]); cd = 0; }
			if(cd < t[cn].len() && t[cn][cd] == s[j]) {
				cd++;
				if(j < s.size() - 1) break;
				else {
					if(i) t[lst].suf = cn;
					for(; i <= j; i++) { sufn[si][i] = cn; cn = t[cn].suf; }
				}
			} else if(cd == t[cn].len()) {
				sufn[si][i] = en;
				if(i) t[lst].suf = en; lst = en;
				t[cn](s[j]) = new_node(j, n - 1, si, cn);
				cn = t[cn].suf; cd = t[cn].len();
			} else {
				int mid = new_node(t[cn].l, t[cn].l + cd - 1, t[cn].si, t[cn].p);
				t[t[cn].p](t[cn][0]) = mid;
				if(ns) t[ns].suf = mid;
				if(i) t[lst].suf = en; lst = en;
				sufn[si][i] = en;
				t[mid](s[j]) = new_node(j, n - 1, si, mid);
				t[mid](t[cn][cd]) = cn;
				t[cn].p = mid; t[cn].l += cd; cn = t[mid].p;
				int g = cn? j - cd : i + 1; cn = t[cn].suf;
				while(g < j && g + t[t[cn](S[si][g])].len() <= j) {
					cn = t[cn](S[si][g]); g += t[cn].len();
				}
				if(g == j) { ns = 0; t[mid].suf = cn; cd = t[cn].len(); }
				else { ns = mid; cn = t[cn](S[si][g]); cd = j - g; }
			}
		}
	}

char s[N];

const int L = 19;

int h[N], lc[N][L];
int d[N], f[N], tempo;

void dfs(int u, int h) {
	lc[u][0] = t[u].p;
	::h[u] = h;
	for(int i = 1; i < L; i++)
		lc[u][i] = lc[lc[u][i - 1]][i - 1];
	d[u] = tempo++;
	for(auto e : t[u].adj)
		dfs(e.snd, h + t[e.snd].len());
	f[u] = tempo - 1;
}

int get(int l, int r) {
	int u = sufn[0][l];
	// up till r
	for(int i = L - 1; i >= 0; i--)
		if(h[lc[u][i]] >= r - l + 1)
			u = lc[u][i];
	return u;
}

struct cmp {
	bool operator() (int i, int j) {
		return d[i] < d[j];
	}
};

int st[N], sn;
vector<int> adj[N];

inline bool anc(int p, int u) {
	return d[u] >= d[p] && f[u] <= f[p];
}
ll we[N];

ll go(int u) {
	ll ans = 1;
	for(int v : adj[u]) {
		ans = mod(ans * go(v));
	}
	return mod(ans + we[u]);
}

int main() {
	int n, q, i;
	scanf("%d %d", &n, &q);
	scanf("%s", s);
	add_string(s);
	dfs(0, 0);
	while(q--) {
		int k;
		scanf("%d %lld", &k, &modn);
		map<int, int, cmp> mp;
		for(i = 0; i < k; i++) {
			int l, r;
			scanf("%d %d", &l, &r); l--; r--;
			mp[get(l, r)]++;
		}
		sn = 0;
		st[sn++] = 0;
		adj[0].clear();
		for(auto e : mp) {
			we[e.fst] = e.snd;
			adj[e.fst].clear();
			while(!anc(st[sn -1], e.fst)) sn--;
			adj[st[sn - 1]].pb(e.fst);
			st[sn++] = e.fst;
		}
		printf("%lld\n", go(0));
	}
}
