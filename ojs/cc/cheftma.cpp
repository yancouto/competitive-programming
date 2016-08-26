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

bool ok(multiset<int> &s, int x) { return !s.empty() && x <= *s.rbegin(); }
int dist(multiset<int> &s, int x) { return *s.lower_bound(x) - x; }

int a[100009];
int main() {
	int i, n, m, k, x;
	for_tests(t, tt) {
		scanf("%d %d %d", &n, &k, &m); m += k;
		multiset<int> s;
		for(i = 0; i < n; i++) scanf("%d", &a[i]);
		for(i = 0; i < n; i++) {
			scanf("%d", &x);
			if(x != a[i]) s.insert(a[i] - x);
		}
		ll tot = 0;
		multimap<int, int> d;
		for(i = 0; i < m; i++) {
			scanf("%d", &x);
			if(s.find(x) != s.end()) s.erase(s.find(x));
			else if(ok(s, x)) d.insert(pii(dist(s, x), x));
		}
		while(!s.empty() && !d.empty()) {
			pii v = *d.begin();
			d.erase(d.begin());
			if(!ok(s, v.snd)) continue;
			if(dist(s, v.snd) > v.fst) { d.insert(pii(dist(s, v.snd), v.snd)); continue; }
			s.erase(s.lower_bound(v.snd));
			tot += v.fst;
		}
		for(int x : s) tot += x;
		printf("%lld\n", tot);
	}
}
