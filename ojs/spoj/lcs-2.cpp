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

const int NS = 13;
const int N = 612345 * 4;
const int E = 30;

int cn, cd, ns, en = 1, lst;
string S[NS]; int si = -1;
/* sufn[si][i] no do sufixo S[si][i...] */
vector<int> sufn[N];
int mrk[N];

struct node {
	int l, r, si;
	int p, suf;
	int adj[E];
	node() {}
	node(int L, int R, int S, int P) : l(L), r(R), si(S), p(P) {}
	inline int len() { return r - l + 1; }
	inline int operator[](int i) { return S[si][l + i]; }
	inline int& operator()(char c) { return adj[c - 'a']; }
} t[N];

inline int new_node(int L, int R, int S, int P) {
	t[en] = node(L, R, S, P);
	for(int i = 0; i < E; i++) t[en].adj[i] = 0;
	return en++;
}

void add_string(string s) {
	s += char('z' + 1);
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

int mx = 0;
int dfs(int u, int h) {
	//for(auto e : t[u].adj)
	//	mrk[u] |= dfs(e.snd, h + t[e.snd].len());
	int any = 0;
	for(int i = 0; i < 30; i++)
		if(t[u].adj[i])
			mrk[u] |= dfs(t[u].adj[i], h + t[t[u].adj[i]].len()), any = true;
	if(mrk[u] == 3) mx = max(mx, h - !any);
	return mrk[u];
}

char s[312345];
int main() {
	for(int i = 0; i < E; i++) t[0].adj[i] = 0;
	t[0].r = -1;
	scanf("%s", s); add_string(s);
	scanf("%s", s); add_string(s);
	for(int i = 0; i < 2; i++)
		for(int ind : sufn[i])
			mrk[ind] |= i+1;
	dfs(0, 0);
	printf("%d\n", mx);
}

