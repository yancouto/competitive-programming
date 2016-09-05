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
const int N = 112;
double memo[N][N];
int seen[N][N], tempo, n, l[N], b[N];
double solve(int i, int t) {
	if(i == n) return 1;
	if(t <= 0) return 0;
	double &r = memo[i][t];
	if(seen[i][t] == tempo) return r;
	seen[i][t] = tempo;
	r = 0;
	int di = 1;
	int oi = i;
	for(int d = 1; d <= 6; d++) {
		if(i == n) di = -1;
		i += di;
		r += solve(b[i]? 0 : i, t - 1 - l[i]) / 6.;
	}
	return r;
}


int main() {
	int i, T, L, B, x;
	while(scanf("%d %d %d %d", &n, &T, &L, &B) != EOF && n) {
		for(i = 0; i < n; i++) l[i] = b[i] = 0;
		for(i = 0; i < L; i++) {
			scanf("%d", &x);
			l[x] = 1;
		}
		for(i = 0; i < B; i++) {
			scanf("%d", &x);
			b[x] = 1;
		}
		tempo++;
		printf("%.10f\n", solve(0, T));
	}
}
