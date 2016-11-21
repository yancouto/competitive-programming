#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;
const int N = 5123456;
const int M = N;
const int K = 1123;

int S[N], qt[K];
ll sum[K];

int main() {
#ifdef ONLINE_JUDGE
	freopen("digits.in", "r", stdin);
	freopen("digits.out", "w", stdout);
#endif
	int i, j;
	scanf("%d", &n);
	for(i = 1; i < N; i++) {
		int v = S[i / 10] + (i % 10);
		if(i < M) S[i] = v;
		if(qt[v] < n) qt[v]++, sum[v] += i;
	}
	ll mn = LLONG_MAX;
	for(i = 1; i < K; i++)
		if(qt[i] == n)
			mn = min(mn, sum[i]);
	printf("%lld\n", mn);
}
