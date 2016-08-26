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
#ifndef ONLINE_JUDGE
#	define debug(args...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");
#else
#	define debug(args...)
#endif
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int n, b;
bool poss(map<string, vector<pii> > &m, int q) {
	int tot = 0; int i;
	for(auto &it : m) {
		int mn = INT_MAX;
		for(pii p : it.second)
			if(p.snd >= q && p.fst < mn)
				mn = p.fst;
		if(mn == INT_MAX) return false;
		tot += mn;
	}
	return tot <= b;
}

int main() {
	int i;
	char str[40]; int p, q;
	for_tests(t, tt) {
		scanf("%d %d", &n, &b);
		map<string, vector<pii> > m;
		set<int> qs;
		for(i = 0; i < n; i++) {
			scanf(" %s %*s %d %d", str, &p, &q);
			m[string(str)].pb(pii(p, q));
			qs.insert(q);
		}
		for(auto it = qs.rbegin(); it != qs.rend(); ++it) {
			if(poss(m, *it)) {
				printf("%d\n", *it);
				break;
			}
		}
	}
	return 0;
}
