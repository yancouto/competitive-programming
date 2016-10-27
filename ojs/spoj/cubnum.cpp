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
int pd[N];

int main() {
	int i, j, n;
	for(i = 1; i < N; i++) {
		pd[i] = i;
		for(j = 1; j * j * j <= i; j++)
			pd[i] = min(pd[i], pd[i - j*j*j] + 1);
	}
	int t = 0;
	while(scanf("%d", &n) != EOF)
		printf("Case #%d: %d\n", ++t, pd[n]);
}
