#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, ll> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

int ds[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool bis(int y) {
	if(!(y % 400)) return true;
	if(!(y % 100)) return false;
	return !(y % 4);
}
void rnum(int &x) {
	char c;
	while(!isdigit(c = getchar()));
	ungetc(c, stdin);
	scanf("%d", &x);
}

struct tim {
	int d, mo, y, h, mi, s;
	void read() {
		rnum(d); rnum(mo); rnum(y); rnum(h); rnum(mi); rnum(s);
	}
	void print() {
		printf("%02d/%02d/%02d - %02d:%02d:%02d\n", d, mo, y, h, mi, s);
	}
	bool operator > (tim o) const {
		if(y != o.y) return y > o.y;
		if(mo != o.mo) return mo > o.mo;
		if(d != o.d) return d > o.d;
		if(h != o.h) return h > o.h;
		if(mi != o.mi) return mi > o.mi;
		return s > o.s;
	}
	void add(ll x) {
		x += s;
		s = x % 60;
		x /= 60;
		x += mi;
		mi = x % 60;
		x /= 60;
		x += h;
		h = x % 24;
		x /= 24;
		x += d;
		d = 1;
		while(--x) {
			d++;
			if(bis(y) && mo == 2) {
				if(d > 29) d = 1, mo++;
			} else if(d > ds[mo]) {
				d = 1; mo++;
				if(mo > 12) mo = 1, y++;
			}
		}
	}
};

struct no {
	int v;
	ll d;
	bool operator < (no o) const { return d > o.d; }
};
int n;
int seen[100009], tempo;
vector<pii> adj[100009];
ll bfs() {
	priority_queue<no> pq;
	pq.push({0, 0}); tempo++;
	while(!pq.empty()) {
		no x = pq.top(); pq.pop();
		if(x.v == n - 1) return x.d;
		if(seen[x.v] == tempo) continue;
		seen[x.v] = tempo;
		for(pii e : adj[x.v])
			if(seen[e.fst] != tempo)
				pq.push({e.fst, x.d + e.snd});
	}
	return -1;
}


int main() {
	int m, i, a, b, d, h, mi, s;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &m);
		tim st, en;
		st.read();
		en.read();
		for(i = 0; i < n; i++) adj[i].clear();
		for(i = 0; i < m; i++) {
			rnum(a); rnum(b); rnum(d); rnum(h); rnum(mi); rnum(s);
			ll t = s + 60ll * mi + (60ll * 60ll) * h + (60ll * 60ll * 24ll) * d;
			adj[a].pb(pii(b, t));
			adj[b].pb(pii(a, t));
		}
		ll mn = bfs();
		if(mn == -1) { puts("IMPOSSIBLE"); continue; }
		st.add(mn);
		if(st > en) { puts("IMPOSSIBLE"); continue; }
		puts("POSSIBLE");
		st.print();
	}
}
