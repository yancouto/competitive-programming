#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
#ifndef ONLINE_JUDGE
#	define debug(args...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");}
#else
#	define debug(args...) {}
#endif
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int n, t, ts[53], rr[52][209], ll[52][209];
const int inf = 1000000;

struct no {
	int st, t;
	int spent;
	no() {}
	no(int a, int b, int c) : st(a), t(b), spent(c) {}
	bool operator < (const no &o) const {
		bool sm = t < o.t;
		if(!sm && t == o.t) sm = spent < o.spent;
		return !sm;
	}
};

int seen[52][209], tempo;
int solve() {
	priority_queue<no> pq;
	pq.push(no(0, 0, 0));
	tempo++;
	while(!pq.empty()) {
		no x = pq.top();
		pq.pop();
		if(x.t > t) continue;
		if(x.t == t && x.st == n - 1) return x.spent;
		if(seen[x.st][x.t] == tempo) continue;
		seen[x.st][x.t] = tempo;
		pq.push(no(x.st, x.t + 1, x.spent + 1));
		if(ll[x.st][x.t]) pq.push(no(x.st - 1, x.t + ts[x.st - 1], x.spent));
		if(rr[x.st][x.t]) pq.push(no(x.st + 1, x.t + ts[x.st], x.spent));
	}
	return -1;
}

int main() {
	int cn = 0, i, j, x, m;
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		scanf("%d", &t);
		for(i = 0; i < n - 1; i++)
			scanf("%d", &ts[i]);
		scanf("%d", &m);
		memset(rr, 0, sizeof rr);
		memset(ll, 0, sizeof ll);
		for(i = 0; i < m; i++) {
			scanf("%d", &x); 
			int d = 1, st = 0;
			while(x <= 200) {
				((d == 1)? rr : ll)[st][x] = 1;
				x += ts[st - (d < 0)];
				st += d;
				if(st == n - 1 || st == 0) break;
			}
		}
		scanf("%d", &m);
		for(i = 0; i < m; i++) {
			scanf("%d", &x);
			int d = -1, st = n - 1;
			while(x <= 200) {
				((d == 1)? rr : ll)[st][x] = 1;
				x += ts[st - (d < 0)];
				st += d;
				if(st == n - 1 || st == 0) break;
			}
		}
		int a = solve();
		printf("Case Number %d: ", ++cn);
		if(a == -1) puts("impossible");
		else printf("%d\n", a);
	}
}
