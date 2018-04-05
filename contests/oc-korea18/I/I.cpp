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
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

const int NS = 1; const int N = 112345 * 2;
int cn, cd, ns, en = 1, lst;
string S[NS]; int si = -1;
vector<int> sufn[N]; // sufn[si][i] no do sufixo S[si][i...]
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

int lfs[N], sz[N];

int dfs(int u) {
	sz[u] = 1;
	if(t[u].adj.empty()) {
		lfs[u] = 1;
		return sz[u];
	}
	for(pair<char, int> pci : t[u].adj) {
		sz[u] += dfs(pci.snd);
		lfs[u] += lfs[pci.snd];
	}
	return sz[u];
}

int en_;

const int M = 1123456;
ll ksum[M], osum[M], o2sum[M], L[M], R[M];
int seg[N], ch[N], ci[N], cs[N];
vector<ll> os, ks;

inline void join(int i) {
	ksum[i] = ksum[L[i]] + ksum[R[i]];
	osum[i] = osum[L[i]] + osum[R[i]];
	o2sum[i] = o2sum[L[i]] + o2sum[R[i]];
}

int build(int l, int r) {
	int i = en_++;
	if(l == r) {
		ksum[i] = ks[l];
		osum[i] = ks[l] * os[l];
		o2sum[i] = ks[l] * os[l] * os[l];
		return i;
	}
	int m = (l + r) / 2;
	L[i] = build(l, m);
	R[i] = build(m + 1, r);
	join(i);
	return i;
}
ll ans = 0;


void go(int u, int h) {
	if(u == h) os.clear(), ks.clear();
	ch[u] = h;
	ci[u] = cs[h]++;
	ks.pb(t[u].len());
	os.pb(lfs[u]);
	if(t[u].adj.empty()) {
		seg[h] = build(0, cs[h] - 1);
		ans += o2sum[seg[h]];
		return;
	}
	int mi = -1;
	for(auto &e : t[u].adj)
		if(mi == -1 || sz[e.snd] > sz[mi])
			mi = e.snd;
	go(mi, h);
	for(auto &e : t[u].adj)
		if(mi != e.snd)
			go(e.snd, e.snd);
}

void sub1(int u) {

}

ll kp[N];

int main() {
	int i;
	string s;
	cin >> s;
	add_string(s);
	dfs(0);
	go(0, 0);
	ans -= s.size() + 1;
	kp[s.size() - 1] = ans;
	for(i = s.size() - 1; i > 0; i--) {
		sub1(sufn[0][s.size() - 1 - i]);
	}
	for(i = 0; i < int(s.size()); i++)
		printf("%lld\n", kp[i]);
}
