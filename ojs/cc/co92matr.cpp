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

int a[112][112];

int main() {
	int i, j, n, m;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &m);
		bool ok = true;
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++) {
				scanf("%d", &a[i][j]);
				if(a[i][j] == -1) a[i][j] = max(i? a[i - 1][j] : 1, j? a[i][j - 1] : 1);
				if(a[i][j] < max(i? a[i - 1][j] : 1, j? a[i][j - 1] : 1)) ok = false;
			}
		if(!ok) { puts("-1"); continue; }
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				printf("%d%c", a[i][j], " \n"[j == m - 1]);
	}
}
