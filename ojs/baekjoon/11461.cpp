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

ll a[4][11234];

int main() {
	int i, j;
	int n[4];
	ll L;
	while(scanf("%lld", &L) != EOF && L) {
		for(i = 0; i < 4; i++) scanf("%d", &n[i]);
		for(i = 0; i < 4; i++)
			for(j = 0; j < n[i]; j++)
				scanf("%lld", &a[i][j]);
		vector<ll> A, B;
		for(i = 0; i < n[0]; i++)
			for(j = 0; j < n[1]; j++)
				A.pb(a[0][i] + a[1][j]);
		for(i = 0; i < n[2]; i++)
			for(j = 0; j < n[3]; j++)
				B.pb(a[2][i] + a[3][j]);
		sort(A.begin(), A.end());
		sort(B.begin(), B.end());
		ll tot = 0;
		for(ll x : A) {
			if(x > L) continue;
			while(!B.empty() && x + B.back() > L)
				B.pop_back();
			tot += ll(B.size());
		}
		printf("%lld\n", tot);
	}
}
