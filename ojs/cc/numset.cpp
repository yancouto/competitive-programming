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

int ps[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};

int a[1123], g[1123], nx[1123];
pii p[1123];
int seen[1009][1 << 11];
int memo[1009][1 << 11];
int n, t;
int solve(int i, int bm) {
	if(i == n) return 0;
	int &r = memo[i][bm];
	if(seen[i][bm] == t) return r;
	seen[i][bm] = t;
	r = solve(i + 1, bm);
	if((bm & g[i]) == 0) r = max(r, 1 + solve(nx[i], bm | g[i]));
	return r;
}

int dv[1123];
int main() {
	int i, j;
	for(i = 2; i <= 1000; i++)
		if(!dv[i])
			for(j = i+i; j <= 1000; j += i)
				dv[j] = 1;
	for_tests(tn, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) scanf("%d", &a[i]);
		for(i = 0; i < n; i++) {
			int mx = -1;
			for(j = 1; j <= a[i]; j++)
				if(!dv[j] && !(a[i] % j))
					mx = j;
			p[i] = pii(mx, a[i]);
			g[i] = 0;
		}
		sort(p, p + n);
		for(i = 0; i < n; i++)
			for(j = 0; j < 11; j++)
				if(!(p[i].snd % ps[j]))
					g[i] |= (1 << j);
		nx[n - 1] = n;
		for(i = n - 2; i >= 0; i--)
			if(p[i].fst != p[i + 1].fst || p[i].fst <= 31)
				nx[i] = i + 1;
			else nx[i] = nx[i + 1];
		t++;
		printf("%d\n", solve(0, 0));
	}
}
