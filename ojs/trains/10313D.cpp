#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pdi;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

pdi v[112345];
int main() {
	int i, n, d, s, p, o;
	scanf("%d %d", &d, &n);
	for(i = 0; i < n; i++) {
		scanf("%d %d %d", &s, &p, &o);
		v[i] = pdi(s * p, s * o);
	}
	sort(v, v + n);
	double l = 0, r = 1e6;
	while(r - l > 1e-6) {
		double m = (l + r) / 2;
		double cur = 0; double curw = m;
		for(i = 0; i < n; i++) {
			if(curw > v[i].snd) continue;
			double h = double(v[i].snd - curw) / v[i].fst;
			if(cur + h >= d)
				break;
			cur += h;
			curw = v[i].snd;
		}
		if(i < n) l = m;
		else r = m;
	}
	printf("%.10f\n", l);
}
