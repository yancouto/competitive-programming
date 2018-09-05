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

const int N = 112345;
int v[2][N], g[N];

int main() {
	int i, n;
	for_tests(tn, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &v[i & 1][i / 2]);
		sort(v[0], v[0] + ((n + 1) / 2));
		sort(v[1], v[1] + (n / 2));
		for(i = 0; i < n; i++)
			g[i] = v[i & 1][i / 2];
		printf("Case #%d: ", tt);
		for(i = 0; i < n - 1; i++)
			if(g[i] > g[i + 1])
				break;
		if(i < n - 1) printf("%d\n", i);
		else puts("OK");
	}
}
