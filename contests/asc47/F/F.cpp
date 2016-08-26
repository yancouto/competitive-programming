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
#define c1 __builtin_popcount

int C[1009];
set<int> adj[1009];
struct cmp {
	bool operator()(int a, int b) {
		if(c1(C[a]) != c1(C[b])) return c1(C[a]) < c1(C[b]);
		if(adj[a].size() < adj[b].size()) return adj[a].size() < adj[b].size();
		return a < b;
	}
};

set<int, cmp> s;

int nxt(int b) {
	for(int i = 1; ; i++)
		if(!((b >> i) & 1))
			return i;
}

void go(int a, int c) {
	s.erase(s.find(a));
	for(int v : adj[a]) {
		s.erase(s.find(v));
		adj[v].erase(a);
		assert(!((C[v] >> c) & 1));
		C[v] |= (1 << c);
		s.insert(v);
	}
}

int main() {
	int i, n, a, b;
	scanf("%d", &n);
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b);
		adj[a].insert(b);
		adj[b].insert(a);
	}
	for(i = 1; i <= n; i++)
		s.insert(i);
	int left = n;
	while(true) {
		int a = *s.rbegin();
		int c = nxt(C[a]);
		printf("%d %d\n", a, c);
		fflush(stdout);
		go(a, c);
		left -= 2;
		scanf("%d %d", &a, &c);
		if(left <= 0) return 0;
		go(a, c);
	}
}
