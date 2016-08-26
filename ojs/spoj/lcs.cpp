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

const int NS = 2;
const int N = 500009 * 2;

int cn, cd, ns, en = 1, lst;
string S[NS]; int si = -1;
int mrk[N];

const int E = 40;
struct node {
	int l, r, si;
	int p, suf;
	bool le;
	int adj[E];
	node() {}
	node(int L, int R, int S, int P, bool LE) : l(L), r(R), si(S), p(P), suf(0), le(LE) { }
	inline int len() { return r - l + 1; }
	inline int operator[](int i) { return S[si][l + i]; }
	inline int& operator()(char c) { if(c - 'a'< 0 || c-'a' >= E) exit(0) ;return adj[c - 'a']; }
} t[N];

inline int new_node(int L, int R, int S, int P, bool l=false) {
	if(en == N - 2) exit(0);
	t[en] = node(L, R, S, P, l);
	for(int i = 0; i < E; i++) t[en].adj[i] = 0;
	return en++;
}

void add_string(string s, int ind) {
	if(s.size() > 250000) exit(0);
	for(char c : s) if(c < 'a' || c > 'z') exit(0);
	s += char('z' + 3);
	S[++si] = s;
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
						mrk[cn] |= ind;
						cn = t[cn].suf;
					}
				}
			} else if(cd == t[cn].len()) {
				mrk[en] |= ind;
				if(i) t[lst].suf = en; lst = en;
				t[cn](s[j]) = new_node(j, n - 1, si, cn, true);
				cn = t[cn].suf;
				cd = t[cn].len();
			} else {
				int mid = new_node(t[cn].l, t[cn].l + cd - 1, t[cn].si, t[cn].p);
				t[t[cn].p](t[cn][0]) = mid;
				if(ns) t[ns].suf = mid;
				if(i) t[lst].suf = en; lst = en;
				mrk[en] |= ind;
				t[mid](s[j]) = new_node(j, n - 1, si, mid, true);
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

int mx = 0;
int dfs(int u, int h, int ct = 0) {
	if(ct > 500009) exit(0);
	for(int i = 0; i < E; i++)
		if(t[u].adj[i] > 0 && t[u].adj[i] < en)
			mrk[u] |= dfs(t[u].adj[i], h + t[t[u].adj[i]].len(), ct + 1);
	//for(auto e  : t[u].adj)
	//	mrk[u] |= dfs(e.snd, h + t[e.snd].len());
	if(mrk[u] == 3) mx = max(mx, h - t[u].le);
	return mrk[u];
}

char s[1123456];
int main() {
	t[0].l = 0; t[0].r = -1; t[0].le = false;
	for(int i = 0; i < E; i++) t[0].adj[i] = 0;
	scanf("%s", s); add_string(s, 1);
	scanf("%s", s); add_string(s, 2);
	dfs(0, 0);
	printf("%d\n", mx);
}
