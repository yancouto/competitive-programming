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
const int N = 5009;
int a[N], nxmn[N], nxmx[N];

int main() {
	int i, n;
	scanf("%d", &n);
	int mn = INT_MAX, mx = INT_MIN;
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		mn = min(mn, a[i]);
		mx = max(mx, a[i]);
	}
	nxmn[n] = nxmx[n] = -1;
	int ans = INT_MAX;
	for(i = n - 1; i >= 0; i--) {
		if(a[i] == mn) nxmn[i] = i;
		else nxmn[i] = nxmn[i + 1];
		if(a[i] == mx) nxmx[i] = i;
		else nxmx[i] = nxmx[i + 1];
		if(nxmn[i] != -1 && nxmx[i] != -1)
			ans = min(ans, abs(nxmn[i] - nxmx[i]) + 1);
	}
	printf("%d\n", ans);
}
