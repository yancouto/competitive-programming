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

#include <bits/stdc++.h>
using namespace std;

namespace sf {
const int NS = 812;
const int N = 812 * 812 * 2;

int cn, cd, ns, en = 1, lst;
string S[NS]; int si = -1;
/* sufn[si][i] no do sufixo S[si][i...] */
vector<int> sufn[N];

struct node {
	int l, r, si;
	int p, suf;
	map<char, int> adj;
	node() : l(0), r(-1), suf(0), p(0) {}
	node(int L, int R, int S, int P) : l(L), r(R), si(S), p(P) {}
	inline int len() { return r - l + 1; }
	inline int operator[](int i) { return S[si][l + i]; }
	inline int& operator()(char c) { return adj[c]; }
} t[N];

inline int new_node(int L, int R, int S, int P) {
	t[en] = node(L, R, S, P);
	return en++;
}

void add_string(string s) {
	s += '$';
	S[++si] = s;
	sufn[si].resize(s.size() + 1);
	cn = cd = 0;
	int i = 0; const int n = s.size();
	for(int j = 0; j < n; j++)
		for(; i <= j; i++) {
			if(cd == t[cn].len() && t[cn](s[j]))
				cn = t[cn](s[j]), cd = 0;
			if(cd < t[cn].len() && t[cn][cd] == s[j]) {
				cd++;
				if(j < s.size() - 1) break;
				else {
					if(i) t[lst].suf = cn;
					for(; i <= j; i++) {
						sufn[si][i] = cn;
						cn = t[cn].suf;
					}
				}
			} else if(cd == t[cn].len()) {
				sufn[si][i] = en;
				if(i) t[lst].suf = en; lst = en;
				t[cn](s[j]) = new_node(j, n - 1, si, cn);
				cn = t[cn].suf;
				cd = t[cn].len();
			} else {
				int mid = new_node(t[cn].l, t[cn].l + cd - 1, t[cn].si, t[cn].p);
				t[t[cn].p](t[cn][0]) = mid;
				if(ns) t[ns].suf = mid;
				if(i) t[lst].suf = en; lst = en;
				sufn[si][i] = en;
				t[mid](s[j]) = new_node(j, n - 1, si, mid);
				t[mid](t[cn][cd]) = cn;
				t[cn].p = mid; t[cn].l += cd;
				cn = t[mid].p;
				int g = cn? j - cd : i + 1;
				cn = t[cn].suf;
				while(g < j && g + t[t[cn](S[si][g])].len() <= j)
					cn = t[cn](S[si][g]), g += t[cn].len();
				if(g == j)
					ns = 0, t[mid].suf = cn, cd = t[cn].len();
				else
					ns = mid, cn = t[cn](S[si][g]), cd = j - g;
			}
		}
}
};


int n, m;

char g[812][812];
char p[412][412];

bitset<412> oc[812][412];

using namespace sf;

int main() {
	int i, j, k, r, c;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			scanf(" %c", &g[i][j]);
	scanf("%d %d", &r, &c);
	for(i = 0; i < r; i++)
		for(j = 0; j < c; j++)
			scanf(" %c", &p[i][j]);
	for(i = 0; i < n + r - 1; i++)
		for(j = 0; j < m + c - 1; j++)
			g[i][j] = g[i % n][j % m];
	int on = n, om = m;
	n += r - 1; m += c - 1;
	for(i = 0; i < n; i++)
		add_string(g[i]);
	map<int, vector<pii>> rev;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			rev[sufn[i][j]].pb(pii(i, j));
	for(i = 0; i < r; i++) {
		vector<pii> ns;
		ns.pb(pii(0, 0));
		for(j = 0; j < c; j++) {
			vector<pii> nx;
			for(pii e : ns) {
				if(e.snd == t[e.fst].len()) {
					if(p[i][j] == '?') for(auto y : t[e.fst].adj) nx.pb(pii(y.snd, 1));
					else if(t[e.fst].adj.count(p[i][j])) nx.pb(pii(t[e.fst].adj[p[i][j]], 1));
				} else if(p[i][j] == '?' || p[i][j] == t[e.fst][e.snd]) nx.pb(pii(e.fst, e.snd + 1));
			}
			ns = nx;
		}
		vector<int> ls;
		while(!ns.empty()) {
			int v = ns.back().fst; ns.pop_back();
			if(t[v].adj.empty()) ls.pb(v);
			else for(auto x : t[v].adj) ns.pb(pii(x.snd, 0));
		}
		for(int v : ls)
			for(pii o : rev[v]) {
				if(o.snd >= om) continue;
				//printf("[%d] occurs in (%d, %d)\n", i, o.fst, o.snd);
				oc[o.fst][o.snd][i] = true;
			}
	}
	for(i = 0; i < on; i++)
		for(j = 0; j < om; j++) {
			for(k = 0; k < r && oc[i + k][j][k]; k++);
			putchar('0' + (k == r));
			if(j == om - 1) putchar('\n');
		}
}
