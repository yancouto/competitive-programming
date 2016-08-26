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
struct dr {
	int t, f;
	dr() {}
	dr(int a, int b) : t(a), f(b) {}
	bool operator < (dr o) const {
		return t * o.f > o.t * f;
	}
};

int main() {
	int n = 0, t, f;
	priority_queue<dr> s; dr tr(0, 0);
	ull mul = 0, tot = 0;
	while(scanf("%d %d", &t, &f) != EOF) {
		s.push(dr(t, f));
		mul += f;
		if(tr.t == 0) {
			tr = s.top();
			s.pop();
			mul -= tr.f;
		}
		tr.t--;
		tot += mul;
	}
	while(!s.empty()) {
		tot += mul * tr.t;
		tr = s.top();
		s.pop();
		mul -= tr.f;
	}
	tot += mul * tr.t;
	printf("%llu\n", tot);
	return 0;
}
