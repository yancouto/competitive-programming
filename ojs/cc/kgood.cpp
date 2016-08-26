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
int a[N], ct[256]; char s[N];

int main() {
	int i, k;
	for_tests(t, tt) {
		scanf("%s %d", s, &k);
		memset(ct, 0, sizeof ct);
		memset(a, 0, sizeof a);
		for(i = 0; s[i]; i++)
			ct[s[i]]++;
		int tot = accumulate(ct, ct + 256, 0);
		for(i = 0; i < 256; i++)
			a[ct[i]]++;
		int best = INT_MAX;
		int bef = 0, nx = 256;
		for(i = 0; i < k; i++)
			nx -= a[i], tot -= a[i] * i;
		for(; i < N; i++) {
			nx -= a[i]; tot -= a[i] * i;
			best = min(best, bef + tot - nx * i);
			bef += a[i - k] * (i - k);
		}
		printf("%d\n", best);
	}
}
