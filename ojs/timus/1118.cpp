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
const int N = 1123456;

int sum[N];

int main() {
	int i, l, r, j;
	for(i = 1; i < N; i++)
		for(j = 2*i; j < N; j += i)
			sum[j] += i;
	scanf("%d %d", &l, &r);
	ll a = 1, b = 0;
	for(i = l; i <= r; i++) {
		ll na = sum[i], nb = i;
		if(na * b < nb * a)
			a = na, b = nb;
	}
	printf("%d\n", (int)b);
}
