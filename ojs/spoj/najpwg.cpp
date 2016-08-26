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

int dv[N]; ll phi[N];

int main() {
	int i, j; ll n;
	for(i = 2; i < N; i++)
		if(!dv[i])
			for(j = i; j < N; j += i)
				dv[j] = i;
	phi[1] = 1;
	for(i = 2; i < N; i++)
		if((i / dv[i]) % dv[i])
			phi[i] = phi[i / dv[i]] * (dv[i] - 1);
		else
			phi[i] = phi[i / dv[i]] * dv[i];
	for(i = 1; i < N; i++)
		phi[i] += phi[i - 1];
	for_tests(t, tt) {
		scanf("%lld", &n);
		printf("Case %d: %lld\n", tt, (n * (n + 1ll)) / 2ll - phi[n]);
	}
}
