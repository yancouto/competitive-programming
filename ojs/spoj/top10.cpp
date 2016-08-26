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

namespace sf {
const int NS = 112345;
const int N = 212345;

int cn, cd, cc, li, ns, en, es[N];
inline int r(int b, int si) { return b == N? es[si] : b; }
string s[NS];
struct edge {
	int a, b;
	int n, si;
	inline int len() { return r(b, si) - a + 1; }
	inline char operator[](int i) { return s[si][a + i]; }
};

int suf[N], p[N];
map<char, edge> tr[N];
int si;

void add() {
	int &e = es[si];
	string &s = sf::s[si];
	e++;
	for(; li <= e; li++) {
		if(ns && cd == 0) suf[ns] = cn, ns = 0;
		if(cd? tr[cn][cc][cd] == s[e] : tr[cn].count(s[e])) {
			if(cd++ == 0) cc = s[e];
			if(cd == tr[cn][cc].len()) cd = 0, cn = tr[cn][cc].n;
			break;
		}
		tr[en].clear();
		if(cd) {
			if(ns) suf[ns] = en;
			tr[en + 1].clear();
			edge &ed = tr[cn][cc];
			char w = ed[cd];
			tr[en][w] = ed;
			tr[en][w].a += cd;
			tr[en][s[e]] = edge{e, N, en + 1, si};
			p[en] = cn;
			p[en + 1] = p[tr[cn][cc].n] = en;
			ns = en;
			ed.b = ed.a + cd - 1;
			ed.n = en++; en++;
			int g = cn? e - cd : li + 1;
			cn = suf[cn];
			while(tr[cn].count(cc = s[g]) && g + tr[cn][s[g]].len() <= e) {
				g += tr[cn][cc].len();
				cn = tr[cn][cc].n;
			}
			cd = e - g;
		} else {
			p[en] = cn;
			tr[cn][s[e]] = edge{e, N, en++, si};
			cn = suf[cn];
		}
	}
}

void reset() {
	tr[0].clear();
	en = 1; si = -1;
}

void sufftree(string ss) {
	si++;
	es[si] = -1;
	ss += '$';
	s[si] = ss;
	ns = cn = cd = cc = li = 0;
	for(int i = 0; i < ss.size(); i++) add();
}
};
using namespace sf;
int pp[NS], inv[NS];
struct cmp {
	bool operator() (int i, int j) { return inv[i] < inv[j]; }
};

set<int, cmp> st[N];
void proc(string &s, int si) {
	cn = cc = cd = 0;
	for(char c : s) {
		if(cd++ == 0) cc = c;
		if(cd == tr[cn][cc].len()) cd = 0, cn = tr[cn][cc].n;
	}
	st[cn].insert(si);
	for(int i = 1; i < s.size(); i++) {
		cn = p[cn];
		int g = cn? s.size() - tr[cn][cc].len() : i;
		cn = suf[cn];
		while(g != s.size()) {
			cc = s[g];
			g += tr[cn][cc].len();
			cn = tr[cn][cc].n;
		}
		st[cn].insert(si);
	}
}

char ss[N];
vector<int> qs[N], val[N];

void dfs(int u) {
	for(auto &it : tr[u]) {
		auto &e = it.snd;
		dfs(e.n);
		if(st[e.n].size() > st[u].size()) st[e.n].swap(st[u]);
		for(int x : st[e.n]) st[u].insert(x);
		st[e.n].clear();
		while(st[u].size() > 10) st[u].erase(prev(st[u].end()));
	}
	for(int q : qs[u])
		for(int x : st[u])
			val[q].pb(x);
}

int main() {
	int i, n, q, j;
	sf::reset();
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%s", ss);
		sf::sufftree(ss);
		pp[i] = i;
	}
	sort(pp, pp + n, [](int i, int j) {
		if(s[i].size() != s[j].size()) return s[i].size() < s[j].size();
		if(s[i] != s[j]) return s[i] < s[j];
		return i < j;
	});
	for(i = 0; i < n; i++) inv[pp[i]] = i;
	for(i = 0; i < n; i++) proc(s[i], i);
	scanf("%d", &q);
	for(j = 0; j < q; j++) {
		scanf("%s", ss);
		cn = cd = cc = 0;
		for(i = 0; ss[i]; i++) {
			if(cd? tr[cn][cc][cd] != ss[i] : !tr[cn].count(ss[i])) { val[j].pb(-2); break; }
			if(cd++ == 0) cc = ss[i];
			if(cd == tr[cn][cc].len()) cd = 0, cn = tr[cn][cc].n;
		}
		if(ss[i]) continue;
		if(cd) cn = tr[cn][cc].n;
		qs[cn].pb(j);
	}
	dfs(0);
	for(i = 0; i < q; i++) {
		for(int x : val[i])
			printf("%d ", x + 1);
		putchar('\n');
	}
}
