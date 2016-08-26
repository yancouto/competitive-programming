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

struct point {
	int x, y;
	bool operator < (const point &o) const {
		if(x == o.x) return y > o.y;
		return x < o.x;
	}
};

set<point> memo[100009];

bool big_any(point p, int m) {
	auto it = memo[m].lower_bound(p);
	if(it == memo[m].begin()) return false;
	--it;
	return it->y < p.y;
}

int main() {
	int i, n;
	scanf("%d", &n);
	point p; int sz = 1;
	for(i = 0; i < n; i++) {
		scanf("%d %d", &p.x, &p.y);
		int l = 1, r = sz;
		while(l < r) {
			int m = (l + r) / 2;
			if(big_any(p, m)) l = m + 1;
			else r = m;
		}
		if(l == sz) sz++;
		auto it = memo[l].insert(p).fst;
		while(true) {
			auto it2 = it++;
			if(it == memo[l].end()) break;
			if(it->y <= p.y) break;
			memo[l].erase(it);
			it = it2;
		}
	}
	printf("%d\n", sz - 1);
}
