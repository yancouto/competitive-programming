#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<double, double> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int main() {
	while(scanf("%d", &n) != EOF) {
		for(i = 0; i < n; i++) {
			scanf("%lf %lf", &p[i].fst, &p[i].snd);
			p[i].snd = -p[i].snd;
		}
		sort(p, p + n);
		reverse(p, p + n);
		map<pii, int> s;
		s[pii(0, -100)] = 0;
		s[pii(100, 0)] = 0;
		for(i = 0; i < n; i++) {
			
		}
	}
}
