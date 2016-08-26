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
	double x, y, z;
	double operator * (point p) const { return x * p.x + y * p.y + z * p.z; }
	point operator - (point p) const { return {x - p.x, y - p.y, z - p.y}; }
} ps[502];
point inn[502];

bool side(int i, point x) {
	return (ps[i] * (x - inn[i])) > 0;
}

map<string, int> mp;
int main() {
	int i, j, n, m; double z;
	scanf("%d %d", &m, &n);
	for(i = 0; i < m; i++) {
		scanf("%lf %lf %lf %lf", &ps[i].x, &ps[i].y, &ps[i].z, &z);
		if(ps[i].x != 0) inn[i].x = z / ps[i].x;
		else if(ps[i].y != 0) inn[i].y = z / ps[i].y;
		else inn[i].z = z / ps[i].z;
	}
	bitset<500> b;
	for(i = 0; i < n; i++) {
		point p;
		scanf("%lf %lf %lf", &p.x, &p.y, &p.z);
		for(j = 0; j < m; j++)
			b.set(j, side(j, p));
		mp[b.to_string()]++;
	}
	int mx = 0;
	for(auto &e : mp)
		mx = max(mx, e.snd);
	printf("%d\n", mx);
}
