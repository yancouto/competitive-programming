#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 112345;

int e = -1;
inline int r(int b) { return b == N? e : b; }

struct edge {
	int a, b;
	int n;
	inline int len() const { return r(b) - a + 1; }
};
int en = 1;

int suf[N];
edge tr[N][128];
int li, ns;
int cn, cd, cc;
char s[N];

inline void cl(int e) { memset(tr[e], 0, sizeof(edge) * 128);}

void add() {
	e++;
	for(; li <= e; li++) {
		if(ns && cd == 0) suf[ns] = cn, ns = 0;
		if(cd? s[tr[cn][cc].a + cd] == s[e] : tr[cn][s[e]].n) {
			if(!cd) cc = s[e];
			if((++cd) == tr[cn][cc].len()) cn = tr[cn][cc].n, cd = 0;
			break;
		}
		if(cd) {
			cl(en); cl(en + 1);
			if(ns) suf[ns] = en;
			edge &ed = tr[cn][cc];
			char w = s[ed.a + cd]; // first wrong char
			tr[en][w] = ed;
			tr[en][w].a += cd;
			tr[en][s[e]] = edge{e, N, en + 1};
			ns = en;
			ed.b = ed.a + cd - 1;
			ed.n = en++;
			en++;
			int g;
			if(cn) g = e - cd;
			else g = li + 1;
			cn = suf[cn];
			while(g + tr[cn][s[g]].len() <= e) {
				int add = tr[cn][s[g]].len();
				cn = tr[cn][s[g]].n;
				g += add;
			}
			if(g == e) cd = 0;
			else cd = e - g, cc = s[g];
		} else {
			cl(en);
			tr[cn][s[e]] = edge{e, N, en++};
			cn = suf[cn];
		}
	}
}

ll all;
void dfs(int u) {
	for(int i = 0; i < 128; i++)
		if(tr[u][i].n) {
			all += tr[u][i].len();
			dfs(tr[u][i].n);
		}
}

int main() {
	int i;
	for_tests(t, tt) {
		cl(0);
		e = -1; all = 0; en = 1;
		li = ns = cc = cd = cn = 0;
		scanf("%s", s);
		for(i = 0; s[i]; i++)
			add();
		add();
		dfs(0);
		printf("%lld\n", all - ll(i + 1));
	}
}
