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

typedef double dbl;

const int N = 17;
const int NN = (1 << N);

int c[N], f[N], a[N][N], bm[N];
dbl p[NN];

ll fat[N];

inline ll choose(ll k, ll n) {
	if(k > n || k < 0) return 0;
	return fat[n] / (fat[k] * fat[n - k]);
}

int main() {
	ios::sync_with_stdio(0);
	int i, j, n, s, m;
	fat[0] = 1;
	for(i = 1; i < N; i++)
		fat[i] = ll(i) * fat[i - 1];
	cin >> n >> s >> m;
	for(i = 0; i < m; i++)
		cin >> c[i];
	for(i = 0; i < m - 1; i++)
		cin >> f[i];
	for(i = 0; i < m - 1; i++)
		for(j = 0; j < c[i]; j++)
			cin >> a[i][j], bm[i] |= (1 << a[i][j]);
	vector<int> ps, pc;
	for(i = 0; i < (1 << n); i++)
		if(__builtin_popcount(i) == s)
			ps.pb(i);
	for(i = 0; i < (1 << n); i++)
		if(__builtin_popcount(i) == c[m - 1])
			pc.pb(i);
	for(int sb : ps) {
		dbl prob = 1;
		for(i = 0; i < m - 1; i++) {
			int k = __builtin_popcount(sb & bm[i]);
			prob *= choose(f[i], k) / dbl(1 << k);
		}
		p[sb] = prob;
	}
	double tot = accumulate(p, p + (1 << n), dbl(0));
	for(int sb : ps)
		p[sb] /= tot;
	dbl best = 0;
	for(int cb : pc) {
		dbl cur = 0;
		for(int sb : ps)
			if((sb & cb) == 0)
				cur += p[sb];
		best = max(best, cur);
	}
	cout << setprecision(20) << best << '\n';
}
