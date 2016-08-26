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
const int N = 112345;
int x[N], y[N], C[N], L[N];
pii ds[N];
inline int sqr(int x) { return x * x; }

int main() {
	int i, n, j;
	for_tests(tn, tt) {
		int err = 0;
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &x[i]);
		for(i = 0; i < n; i++)
			scanf("%d", &y[i]);
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++) {
				scanf("%d", &L[i * n + j]);
				C[i * n + j] = 0;
				err += (C[i * n + j] != L[i * n + j]);
				ds[i * n + j] = pii(sqr(x[i] - x[j]) + sqr(y[i] - y[j]), i * n + j);
			}
		sort(ds, ds + n * n);
		int mn = INT_MAX, val;
		for(i = 0; i < n * n;) {
			for(j = i; j < n * n && ds[i].fst == ds[j].fst; j++) {
				C[ds[j].snd] = 1;
				if(L[ds[j].snd]) err--;
				else err++;
			}
			if(err < mn) {
				mn = err;
				val = ds[i].fst;
			}
			i = j;
		}
		printf("Case #%d: %d %d\n", tt, val, mn);
	}
}
