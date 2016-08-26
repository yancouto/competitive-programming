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

#define temp template<typename num>
#define ptn point<num>
temp struct point {
	num x, y;
	ptn() {}
	ptn(num a, num b) : x(a), y(b) {}
	ptn operator + (ptn o) const { return ptn(x + o.x, y + o.y); }
	ptn operator - (ptn o) const { return ptn(x - o.x, y - o.y); }
	num operator * (ptn o) const { return x * o.x + y * o.y; }
	num operator ^ (ptn o) const { return x * o.y - y * o.x; }
};
typedef point<ll> pti;
temp inline num cross(ptn a, ptn b, ptn c) { return (c - a) ^ (b - a); }
const int N = 11234;

ll x[2][N], y[N]; int seen[N];
pti pt[N], P;
int p[N], sn; ll v[N];
bool cmp(int i, int j) {
	ll v = cross(P, pt[i], pt[j]);
	if(v != 0) return v > 0;
	return ::v[i] > ::v[j];
}

int in[N], g[N];
void add(ll x, ll y, ll V, int i) {
	pt[sn] = pti(x, y);
	p[sn] = sn; g[sn] = i;
	v[sn++] = V;
}


int main() {
	srand(time(NULL));
	int i, n, p, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%lld %lld %lld", &x[0][i], &x[1][i], &y[i]);
		//x[0][i] = rand() % 100;
		//x[1][i] = rand() % 100;
		//y[i] = rand() % 100;
		if(x[0][i] < x[1][i]) swap(x[0][i], x[1][i]);
	}
	ll mx = 0;
	for(i = 0; i < n; i++)
		for(p = 0; p < 2; p++) {
			sn = 0;
			P = pti(x[p][i], y[i]);
			for(j = 0; j < n; j++)
				if(y[j] < y[i])
					add(x[0][j], y[j], abs(x[0][j] - x[1][j]),j),
					add(x[1][j], y[j], -abs(x[0][j] - x[1][j]),j);
				else if(y[j] > y[i])
					add(2ll * x[p][i] - x[0][j], 2ll * y[i] - y[j], -abs(x[0][j] - x[1][j]),j),
					add(2ll * x[p][i] - x[1][j], 2ll * y[i] - y[j], abs(x[0][j] - x[1][j]),j);
			sort(::p, ::p + sn, cmp);
			ll cur = abs(x[0][i] - x[1][i]);
			mx = max(cur, mx);
			for(j = 0; j < sn; j++) {
				if(j && cross(P, pt[::p[j]], pt[::p[j-1]]) == 0) assert(v[::p[j-1]] >= 0 || v[::p[j]] <= 0);
				int k = g[::p[j]];
				cur += v[::p[j]];
				if(v[::p[j]] > 0) assert(!in[k]), in[k] = 1;
				else if(v[::p[j]] < 0)  assert(in[k]), in[k] = 0;
				assert(cur >= abs(x[0][i] - x[1][i]));
				mx = max(mx, cur);
			}
		}
	printf("%lld\n", mx);

}
