#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
const ull modn2 = 1000000009;
inline ull mod2(ull x) { return x % modn2; }
int n, sz, len;
char str[20009];
struct hashh {
	ull h1, h2;
	bool operator < (hashh o) const { return h1 < o.h1; }
	bool operator == (hashh o) const { return h1 == o.h1 && h2 == o.h2; }
} hs[52][20009];

void proc(int x) {
	int i;
	for(i = 0; i < len; i++)
		str[i + len] = str[i];
	str[i + len] = '\0';
	hashh h; h.h1 = h.h2 = 0;
	ull pot = 1;
	ull pot2 = 1;
	for(i = 0; i < sz; i++) {
		h.h1 = mod(37 * h.h1 + str[i] - 'A' + 1);
		h.h2 = mod2(259 * h.h2 + str[i]);
		if(i > 0) pot = mod(pot * 37);
		if(i > 0) pot2 = mod2(pot2 * 259);
	}
	hs[x][0] = h;
	for(i = sz; i < 2*len; i++) {
		h.h1 = mod(37 * mod(h.h1 - mod(pot * (str[i-sz]-'A'+1)) + modn) + str[i] - 'A' + 1);
		h.h2 = mod2(259 * mod2(h.h2 - mod2(pot2 * str[i-sz]) + modn2) + str[i]);
		hs[x][i-sz+1] = h;
	}
	sort(hs[x], hs[x] + 2 * len - sz + 1);
	//printf("%d of %s\n", sz, str);
	//for(i = 0; i < 2 * len - sz + 1; i++) {
	//	printf("%llu ", hs[x][i]);
	//}
	//putchar('\n');
}

bool match(int i, int j) {
	for(int k = 0; k <= (2*len-sz); k++) {
		int pp = lower_bound(hs[j], hs[j] + 2 * len - sz + 1, hs[i][k]) - hs[j];
		if(pp <= (2*len-sz) && hs[j][pp] == hs[i][k])
			return true;
	}
	return false;
}


namespace f {
	const int maxv = 54;
	const int maxe = 53 * 53 * 2;
	typedef int num;
	int n = maxv;

	int to[maxe], en, nx[maxe], es[maxe], lv[maxv], qu[maxv];
	num cp[maxe], fl[maxe];
	num inf = INT_MAX;


	bool bfs(int s, int t) {
		memset(lv, -1, sizeof(int) * n);
		lv[s] = 0;
		int a = 0, b = 0;
		qu[b++] = s;
		while(a < b) {
			for(int i = es[qu[a]]; i != -1; i = nx[i]) {
				if(cp[i] > fl[i] && lv[to[i]] == -1) {
					lv[to[i]] = lv[qu[a]] + 1;
					qu[b++] = to[i];
					if(to[i] == t) return true;
				}
			}
			a++;
		}
		return false;
	}

	int dfs(int u, int t, num mx) {
		if(u == t) return mx;
		for(int i = es[u]; i != -1; i = nx[i]) {
			if(cp[i] > fl[i] && lv[to[i]] == lv[u] + 1) {
				if(int a = dfs(to[i], t, min(mx, cp[i] - fl[i]))) {
					fl[i] += a;
					fl[i ^ 1] -= a;
					return a;
				}
			}
		}
		return 0;
	}


	int max_flux(int s, int t) {
		int fl = 0, a;
		while(bfs(s, t)) {
			while(a = dfs(s, t, inf))
				fl += a;
		}
		return fl;
	}

	void reset_all(int n2=maxv) { n = n2; en = 0; memset(es, -1, sizeof(int) * n); }
	void reset_flux(int m=maxe/2) { memset(fl, 0, sizeof(num) * m*2); }

	void add_edge(int a, int b, int c, int rc=0) {
		fl[en] = 0; to[en] = b; cp[en] = c;  nx[en] = es[a]; es[a] = en++;
		fl[en] = 0; to[en] = a; cp[en] = rc; nx[en] = es[b]; es[b] = en++;
	}
}

int main() {
	int i, j, pc;
	scanf("%d %d %s", &n, &pc, str);
	len = strlen(str);
	sz = (len * pc + 99) / 100;
	proc(0);
	for(i = 1; i < n; i++) {
		scanf(" %s", str);
		proc(i);
	}
	f::reset_all();
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++) {
			if(match(i, j)) {
				f::add_edge(i, j, 1, 1);
			}
		}
	int mn = INT_MAX;
	for(i = 1; i < n; i++) {
		f::reset_flux();
		mn = min(mn, f::max_flux(0, i));
	}
	printf("%d\n", mn);
	return 0;
}
