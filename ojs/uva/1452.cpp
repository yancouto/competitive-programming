// WA, mas deve estar certo rs
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }


typedef int num;
const int N = 112345;
const int M = 112345 * 2;
const num eps = 0;

struct dinic {
	int hd[N], seen[N], qu[N], lv[N], ei[N], to[M], nx[M];
	num fl[M], cp[M];
	int en = 2;
	int tempo = 0;

	// Reset the whole graph
	void reset(int n=N) { en = 2; memset(hd, 0, sizeof(int) * n); }
	// Reset only the flow
	void reset_flow() { memset(fl, 0, sizeof(num) * en); }

	// edge from a to b with cap c and edge from b to a with cap rc
	void add_edge(int a, int b, num c, num rc=0) {
		to[en] = b; nx[en] = hd[a]; fl[en] = 0; cp[en] = c; hd[a] = en++;
		to[en] = a; nx[en] = hd[b]; fl[en] = 0; cp[en] = rc; hd[b] = en++;
	}

	bool bfs(int s, int t) {
		seen[t] = ++tempo;
		lv[t] = 0;
		int ql = 0, qr = 0;
		qu[qr++] = t;
		while(ql != qr) {
			t = qu[ql++];
			ei[t] = hd[t];
			if(s == t) return true;
			for(int e = hd[t]; e; e = nx[e])
				if(seen[to[e]] != tempo && cp[e ^ 1] - fl[e ^ 1] > eps) {
					seen[to[e]] = tempo;
					lv[to[e]] = lv[t] + 1;
					qu[qr++] = to[e];
				}
		}
		return false;
	}

	num dfs(int s, int t, num f) {
		if(s == t) return f;
		for(int &e = ei[s]; e; e = nx[e])
			if(ei[to[e]] && seen[to[e]] == tempo && cp[e] - fl[e] > eps && lv[to[e]] == lv[s] - 1)
				if(num rf = dfs(to[e], t, min(f, cp[e] - fl[e]))) {
					fl[e] += rf;
					fl[e ^ 1] -= rf;
					return rf;
				}
		return 0;
	}

	num max_flow(int s, int t) {
		num fl = 0;
		while(bfs(s, t))
			while(num f = dfs(s, t, numeric_limits<num>::max()))
				fl += f;
		return fl;
	}
};

dinic d;

int vn;
map<string, int> mp[3];
string bk[3][N];
int rd(int j) {
	char c;
	while((c = getchar()) == ' ');
	if(!isalnum(c)) return 0;
	string s;
	s.pb(c);
	while(isalnum(c = getchar())) s.pb(c);
	ungetc(c, stdin);
	if(!mp[j].count(s)) mp[j][s] = vn++;
	bk[j][mp[j][s]] = s;
	return mp[j][s];
}

char seen[N];

int main() {
	int t;
	scanf("%d", &t); getchar();
	bool fst = true;
	getchar();
	while(t--) {
		mp[0].clear(); mp[1].clear(); mp[2].clear();
		if(fst) fst = false;
		else putchar('\n');
		memset(seen, 0, sizeof seen);
		vn = 0;
		d.reset();
		int s = vn++; int t = vn++;
		int gn = 0;
		vector<int> ps, gs;
		while(int u = rd(0)) {
			int p = rd(1);
			if(!seen[p]) seen[p] = 1, ps.pb(p);
			d.add_edge(u, p, N);
			while(int g = rd(2)) {
				if(!seen[g]) seen[g] = 1, d.add_edge(s, g, 1), gn++, gs.pb(g);
				d.add_edge(g, u, 1);
			}
		}
		for(int p : ps)
			d.add_edge(p, t, gn / 2);
		if(d.max_flow(s, t) == gn) {
			for(int g : gs)
				for(int e = d.hd[g]; e; e = d.nx[e])
					if(d.fl[e] == 1)
						printf("%s %s\n", bk[0][d.to[e]].c_str(), bk[2][g].c_str());
		} else puts("Impossible.");
	}

}
