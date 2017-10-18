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

int a[3][3];

int main() {
	int i, j, k;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			scanf("%d", &a[i][j]);
	int g = INT_MAX;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			for(k = 0; k < 3; k++) {
				g = min(g, a[0][i] + a[1][j] + a[2][k]);
			}
	printf("%d\n", g);
}
