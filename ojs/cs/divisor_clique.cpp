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
const int N = 2009;
int a[N], dp[N];

int main() {
	int i, n, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	sort(a, a + n);
	for(i = 0; i < n; i++) {
		dp[i] = 1;
		for(j = 0; j < i; j++)
			if((a[i] % a[j]) == 0)
				dp[i] = max(dp[i], dp[j] + 1);
	}
	printf("%d\n", *max_element(dp, dp + n));
}
