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

namespace f {
	const int maxv = 2123;
	const int maxe = 11234 * 2;
	typedef int num;
	num inf = INT_MAX;
	int n = maxv;

	int to[maxe], en, nx[maxe], es[maxe], lv[maxv], qu[maxv], cr[maxv];
	num cp[maxe], fl[maxe];


	bool bfs(int s, int t) {
		memset(lv, -1, sizeof(int) * n);
		lv[s] = 0;
		int a = 0, b = 0;
		qu[b++] = s; cr[s] = es[s];
		while(a < b) {
			for(int i = es[qu[a]]; i != -1; i = nx[i]) {
				if(cp[i] > fl[i] && lv[to[i]] == -1) {
					lv[to[i]] = lv[qu[a]] + 1;
					qu[b++] = to[i];
					cr[to[i]] = es[to[i]];
					if(to[i] == t) return true;
				}
			}
			a++;
		}
		return false;
	}

	num dfs(int u, int t, num mx) {
		if(u == t) return mx;
		for(int &i = cr[u]; i != -1; i = nx[i])
			if(cp[i] > fl[i] && lv[to[i]] == lv[u] + 1)
				if(int a = dfs(to[i], t, min(mx, cp[i] - fl[i]))) {
					fl[i] += a;
					fl[i ^ 1] -= a;
					return a;
				}
		return 0;
	}


	num max_flow(int s, int t) {
		num fl = 0, a;
		while(bfs(s, t))
			while(a = dfs(s, t, inf))
				fl += a;
		return fl;
	}

	void reset_all(int n2=maxv) { n = n2; en = 0; memset(es, -1, sizeof(int) * n); }
	void reset_flow() { memset(fl, 0, sizeof(num) * en); }

	void add_edge(int a, int b, num c, num rc=0) {
		fl[en] = 0; to[en] = b; cp[en] = c;  nx[en] = es[a]; es[a] = en++;
		fl[en] = 0; to[en] = a; cp[en] = rc; nx[en] = es[b]; es[b] = en++;
	}
	const int N = maxv;
}

char s1[100], s2[100];
map<string, int> mp;
int get(string s) {
	if(!mp.count(s)) {
		mp[s] = mp.size() - 1;
		if(*prev(s.end()) == '1') f::add_edge(f::N - 1, mp[s], 1);
		else f::add_edge(mp[s], f::N - 2, 1);
	}
	return mp[s];
}


int main() {
	fprintf(stderr, "%d\n", (int) time(NULL)); rand(); rand();
	srand(time(NULL));
	int i, n;
	for_tests(t, tt) {
		f::reset_all();
		mp.clear();
		scanf("%d", &n);
		for(i = 0; i < n; i++) {
			string S1, S2;
			scanf("%s %s", s1, s2);
			S1 = s1; S2 = s2;
			S1 += '1'; S2 += '2';
			int a = get(S1), b = get(S2);
			f::add_edge(a, b, 1);
		}
		int mn = f::max_flow(f::N - 1, f::N - 2);
		mn += mp.size() - (mn * 2);
		printf("Case #%d: %d\n", tt, n - mn);
	}
}
