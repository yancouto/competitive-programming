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
double x[200009], y[200009];
double dist(int i, double xx, double yy) {
	return (x[i] - xx) * (x[i] - xx) + (y[i] - yy) * (y[i] - yy);
}

int main() {
	int i, n;
	while(scanf("%d", &n) != EOF && n) {
		for(i = 0; i < n; i++)
			scanf("%lf %lf", &x[i], &y[i]);
		double l = -200009, r = 200009;
		while(r - l > 1e-9) {
			double m = (l + r) / 2;
			int mi = 0;
			for(i = 1; i < n; i++)
				if(dist(i, m, 0) > dist(mi, m, 0))
					mi = i;
			if(x[mi] < m) r = m;
			else l = m;
		}
		double m = (l + r) / 2;
		int mi = 0;
		for(i = 1; i < n; i++)
			if(dist(i, m, 0) > dist(mi, m, 0))
				mi = i;
		printf("%.9f %.9f\n", m, sqrt(dist(mi, m, 0)));
	}
}
