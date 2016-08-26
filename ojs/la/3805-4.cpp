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
const int N = 212345;

inline int mp(char c) {
	if(c >= 'a' && c <= 'z') return 1 + c - 'a';
	if(c >= 'A' && c <= 'Z') return 27 + c - 'A';
	if(isdigit(c)) return 53 + c - '0';
	if(c == '.') return 63;
	if(c == ',') return 64;
	return 0;
}

int cn, cd, cc, li, e, ns, en;
inline int r(int b) { return b == N? e : b; }
struct edge {
	int a, b;
	int n;
	inline int len() { return r(b) - a + 1; }
};

int suf[N];
char s[N];
edge tr[N][65];
void clear(int e) { memset(tr[e], 0, sizeof(edge) * 65); }

void add() {
	e++;
	for(; li <= e; li++) {
		if(ns && cd == 0) suf[ns] = cn, ns = 0;		
		if(cd? s[tr[cn][cc].a + cd] == s[e] : tr[cn][s[e]].n) {
			if(cd++ == 0) cc = s[e];
			if(cd == tr[cn][cc].len()) cd = 0, cn = tr[cn][cc].n;
			break;
		}
		clear(en);
		if(cd) {
			if(ns) suf[ns] = en;
			clear(en + 1);
			edge &ed = tr[cn][cc];
			char w = s[ed.a + cd];
			tr[en][w] = ed;
			tr[en][w].a += cd;
			tr[en][s[e]] = edge{e, N, en + 1};
			ns = en;
			ed.b = ed.a + cd - 1;
			ed.n = en++; en++;
			int g;
			if(cn) g = e - cd;
			else g = li + 1;
			cn = suf[cn];
			while(g + tr[cn][s[g]].len() <= e) {
				cc = s[g];
				g += tr[cn][cc].len();
				cn = tr[cn][cc].n;
			}
			cd = e - g;			
			cc = s[g];
		} else {
			tr[cn][s[e]] = edge{e, N, en++};
			cn = suf[cn];
		}
	}
}

int lf[N];

ll dfs(int u, ll ct) {
	ll all = 0;
	lf[u] = 0;
	for(int i = 0; i < 65; i++)
		if(tr[u][i].n) {
			all += dfs(tr[u][i].n, tr[u][i].len());
			lf[u] += lf[tr[u][i].n];
		}
	if(lf[u] == 0) lf[u] = 1;
	return all + ll(lf[u] > 1) * ct;
}

int main() {
	int i;
	while(scanf("%s", s) && s[0] != '*') {
		clear(0);
		ns = cn = cd = cc = li = 0; e = -1; en = 1;
		for(i = 0; s[i]; i++) {
			s[i] = mp(s[i]);
			add();
		}
		add();
		printf("%d\n", dfs(0, 0));
	}
}
