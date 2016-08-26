//!OK
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

int memo[(1 << 13) + 2][1002];
int a[1002], acc[1002], n;
//int solve(int l, int i) {
//	int r = acc[i] - l;
//	if(i == n) {
//		if(l == r && !(l & (l - 1))) return true;
//		return !(l * r) && !((l + r) & (l + r - 1));
//	}
//	int &ans = memo[l][i];
//	if(ans != -1) return ans;
//	ans = 0;
//	if(!l || !((a[i] - 1) & l)) ans |= solve(l + a[i], i + 1);
//	if(!r || !((a[i] - 1) & r)) ans |= solve(l, i + 1);
//	return ans;
//}

int& m(int i, int j) { return memo[i][j]; }
void build(int l, int i) {
	if(i == n) { putchar('\n'); return; }
	int r = acc[i] - l;
	if(!((a[i] - 1) & l) && m(l, i) == m(l + a[i], i + 1)) { putchar('l'); build(l + a[i], i + 1); }
	else if(!((a[i] - 1) & r) && m(l, i) == m(l, i + 1)) { putchar('r'); build(l, i + 1); }
}
int main() {
	int i, l;
	for_tests(t, tt) {
		scanf("%d", &n); acc[0] = 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			acc[i + 1] = a[i] + acc[i];
		}
		for(i = n; i >= 0; i--) {
			for(l = acc[i]; l >= 0; l--) {
				int r = acc[i] - l;
				if(i == n) {
					if(l == r && !(l & (l - 1))) m(l, i) = true;
					else m(l, i) =  !(l * r) && !((l + r) & (l + r - 1));
					continue;
				}
				m(l, i) = 0;
				if(!((a[i] - 1) & l)) m(l, i) |= m(l + a[i], i + 1);
				if(!((a[i] - 1) & r)) m(l, i) |= m(l, i + 1);
			}
		}
		if(!m(0, 0)) puts("no");
		else build(0, 0);
	}
}
