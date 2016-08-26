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
const int MAX = 100009;
char s[MAX]; int r[MAX], lc[MAX], n;
ll h[MAX], pot[MAX];
bool eq(int l1, int r1, int l2, int r2) {
	ll h1 = h[r1] - h[l1 - 1], h2 = h[r2] - h[l2 - 1];
	if(h1 < 0) h1 += modn;
	if(h2 < 0) h2 += modn;
	if(l1 > l2) swap(l1, l2), swap(h1, h2);
	if(l1 != l2) h1 = mod(h1 * pot[l2 - l1]);
	return h1 == h2;
}
int lcp(int i, int j) {
	if(s[i] != s[j]) return 0;
	int l = 0, r = min(n - i, n - j);
	while(l < r) {
		int m = (l + r + 1) / 2;
		if(eq(i, i + m, j, j + m)) l = m;
		else r = m - 1;
	}
	return l + 1;
}
bool cmp(int i, int j) {
	int l = lcp(i, j);
	if(i + l > n) return true;
	if(j + l > n) return false;
	return s[i + l] < s[j + l];
}

int main() {
	int i, j;
	pot[0] = 1;
	for(i = 1; i < MAX; i++)
		pot[i] = mod(pot[i - 1] * 263ll);
	while(true) {
		scanf("%s", s + 1); n = strlen(s + 1);
		if(s[1] == '*') return 0;
		for(i = 1; i <= n; i++) {
			r[i] = i;
			h[i] = mod(h[i - 1] + pot[i - 1] * s[i]);
		}
		sort(r + 1, r + n + 1, cmp);
		for(i = 1; i < n; i++)
			lc[i] = lcp(r[i], r[i + 1]);
		int tot = lc[1], last = lc[1];
		for(i = 2; i < n; i++)
			if(lc[i] > lc[i-1])
				tot += lc[i] - lc[i-1];
		printf("%d\n", tot);
	}
}
