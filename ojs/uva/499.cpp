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
const int N = 2123;
int x[N], y[N], t[N], d[N];

int main() {
	int i, j, n, m;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < m; i++)
			scanf("%d %d %d", &x[i], &y[i], &t[i]);
		for(i = 0; i < n; i++) d[i] = 0;
		for(i = 0; i < n - 1; i++)
			for(j = 0; j < m; j++)
				d[y[j]] = min(d[y[j]], d[x[j]] + t[j]);
		for(j = 0; j < m; j++)
			if(d[y[j]] > d[x[j]] + t[j])
				break;
		if(j < m) puts("possible");
		else puts("not possible");
	}
}
