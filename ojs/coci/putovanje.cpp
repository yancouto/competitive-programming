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

int a[1009];
int main() {
	int n, c, i, j;
	scanf("%d %d", &n, &c);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	int mx = 0;
	for(i = 0; i < n; i++) {
		int cur = 0, ans = 0;
		for(j = i; j < n; j++)
			if(cur + a[j] <= c)
				cur += a[j], ans++;
		mx = max(mx, ans);
	}
	printf("%d\n", mx);
}
