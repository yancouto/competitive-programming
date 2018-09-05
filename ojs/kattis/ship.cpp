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
typedef pair<double, double> pdd;

int main() {
	int n, w, u, v, t1, t2, i;
	scanf("%d %d %d %d %d %d", &n, &w, &u, &v, &t1, &t2);
	vector<pdd> vs;
	for(i = 0; i < n; i++) {
		char c; int m;
		scanf(" %c %d", &c, &m);
		double sp = (c == 'E'? u : -u);
		while(m--) {
			int l, p;
			scanf("%d %d", &l, &p);
			double from, to;
			from = -p / sp;
			to = -(p + (c == 'E'? -l : l)) / sp;
			assert(from <= to);
			vs.pb(pdd(from - (i + 1) * (double(w) / v), to - i * (double(w) / v)));
		}
	}
	map<double, int> mp;
	mp[t1] = 0;
	mp[t2] = 0;
	for(pdd p : vs)
		mp[p.fst]++, mp[p.snd]--;
	double lst = -1. / 0.;
	int cur = 0;
	double best = 0;
	for(auto &e : mp) {
		double t = e.fst;
		if(lst >= t1 && t <= t2 && cur == 0)
			best = max(best, t - lst);
		cur += e.snd;
		lst = t;
	}
	printf("%.10f\n", best);
}
