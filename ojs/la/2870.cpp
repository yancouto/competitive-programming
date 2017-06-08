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

int main() {
	int i, n, x;
	while(scanf("%d", &n) != EOF && n) {
		int mx = INT_MIN, cur = 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &x);
			cur += x;
			mx = max(mx, cur);
			if(cur < 0) cur = 0;
		}
		printf("%d\n", mx);
	}
}
