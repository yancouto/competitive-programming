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
const int N = 212345;

int cn, cd, cc, li, e, ns, en;
string s;
inline int r(int b) { return b == N? e : b; }
struct edge {
	int a, b;
	int n;
	inline int len() { return r(b) - a + 1; }
	inline char operator[](int i) { return s[a + i]; }
};
map<char, edge> tr[N];

int suf[N];

void add() {
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
			tr[en][s[e]] = edge{e, N, en + 1};
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
			tr[cn][s[e]] = edge{e, N, en++};
			cn = suf[cn];
		}
	}
}

void sufftree(string ss) {
	ss += '$';
	s = ss;
	tr[0].clear();
	ns = cn = cd = cc = li = 0; e = -1; en = 1;
	for(int i = 0; i < s.size(); i++) add();
}
};
using sf::tr;

char s[sf::N];
int lf[sf::N];

ll dfs(int u, ll ct) {
	ll all = 0;
	lf[u] = 0;
	for(auto &it : tr[u]) {
		auto &e = it.snd;
		all += dfs(e.n, e.len());
		lf[u] += lf[e.n];
	}
	if(lf[u] == 0) lf[u] = 1;
	return all + ll(lf[u] > 1) * ct;
}

int main() {
	while(scanf("%s", s) && s[0] != '*') {
		sf::sufftree(s);
		printf("%lld\n", dfs(0, 0));
	}
}
