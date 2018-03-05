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

int a[112];

bool solve(int l, int ul, int r, int ur, int x) {
	if(x < 0 || ul < 0 || ul > a[l] || ur > a[r] || ur < 0 || (l == r && ul + ur > a[l])) return false;
	if(l > r) return x == 0;
	if(x == 0) return true;
	if(l == r) {
		if(a[l] - ul - ur < 2 * x) return false;
		return solve(l, ul + x, r, ur + x, x - 1);
	}
	if(a[l] - ul < x || a[r] - ur < x) return false;
	if(a[l] - ul == x) ul = 0, l++;
	else ul += x;
	if(a[r] - ur == x) ur = 0, r--;
	else ur += x;
	return solve(l, ul, r, ur, x - 1);
}

int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	if(accumulate(a, a + n, 0) & 1) { puts("no quotation"); return 0; }
	for(i = 100; i >= 2; i--)
		if(solve(0, 0, n - 1, 0, i)) {
			printf("%d\n", i);
			return 0;
		}
	if((n == 1 && a[0] == 2) || (n == 2 && a[0] == 1 && a[1] == 1))
		puts("1");
	else
		puts("no quotation");
}
