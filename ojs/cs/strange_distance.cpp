#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 112345;
int bit[N];
int b[N], n;
pii p[N];
inline int get2(int l, int r) {
	return upper_bound(b, b + n, r) - lower_bound(b, b + n, l);
}
inline void add(int i, int x) {
	for(i += 2; i < N; i += (i & -i))
		bit[i] += x;
}
inline int get(int i) {
	int sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum += bit[i];
	return sum;
}
inline int get(int l, int r) { return get(min(r, 110000)) - get(max(l - 1, 0)); }

inline void add(int i) { add(p[i].y, 1); }
inline void rem(int i) { add(p[i].y, -1); }

ll leq(int k) {
	int l = 0, r = 0;
	ll tot = 0;
	for(int i = 0; i < n; i++) {
		while(r < n && p[r].x <= p[i].x + k) add(r++);
		while(l < n && p[l].x < p[i].x - k) rem(l++);
		int t = (r - l) + get2(p[i].y - k, p[i].y + k) - get(p[i].y - k, p[i].y + k) - 1;
		tot += t;
	}
	while(l < n) rem(l++);
	assert(!(tot % 2ll));
	return tot / 2ll;
}


int main() {
	int i; ll k;
	scanf("%d %lld", &n, &k);
	for(i = 0; i < n; i++)
		scanf("%d %d", &p[i].x, &p[i].y), b[i] = p[i].y;
	sort(p, p + n);
	sort(b, b + n);
	int l = 0, r = 112345;
	while(l < r) {
		int m = (l + r) / 2;
		if(leq(m) < k) l = m + 1;
		else r = m;
	}
	printf("%d\n", l);
}
