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
const int N = 1000999;
ll f[N], ans[N];

int main() {
	int x;
	for(ll i = 1; i < N; i++)
		f[i] = (i * (i + 1ll)) / 2;
	int i, j;
	for(i = 1; i < N; i++) {
		for(j = i + i; j < N; j += i)
			f[j] -= f[i] * ll(j / i);
	}
	for(i = 1; i < N; i++)
		for(j = i; j < N; j += i)
			ans[j] += ll(j) * f[i];
	for_tests(t, tt) {
		scanf("%d", &x);
		printf("%lld\n", ans[x]);
	}
}
