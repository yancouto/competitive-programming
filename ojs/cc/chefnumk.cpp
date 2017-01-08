#include <bits/stdc++.h>
using namespace std;
#define l first
#define r second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 212345;
int a[N], b[N];

int f[N], g[N], gs[N];
int mx, sq;

inline void add(int x) {
	if(f[x] > 0) gs[f[x] / sq]--, g[f[x]]--;
	f[x]++;
	if(f[x] > 0) gs[f[x] / sq]++, g[f[x]]++;
}

inline void rem(int x) {
	if(f[x] > 0) gs[f[x] / sq]--, g[f[x]]--;
	f[x]--;
	if(f[x] > 0) gs[f[x] / sq]++, g[f[x]]++;
}

pii qs[N];
int k[N], p[N], ans[N];

#define getchar getchar_unlocked

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

#define putchar putchar_unlocked

void out(int x) {
	int ct = !x, y = 0;
	while(x) ct++, y = (y << 3) + (y << 1) + (x % 10), x /= 10;
	while(ct--) putchar('0' + (y % 10)), y /= 10;
	putchar('\n');
}

int main() {
	int i, j, n, q;
	int tt;
	rd(tt);
	while(tt--) {
		rd(n); rd(q);
		for(i = 0; i < n; i++) rd(a[i]), b[i] = a[i];
		sort(b, b + n);
		int bn = unique(b, b + n) - b;
		for(i = 0; i < n; i++) a[i] = lower_bound(b, b + bn, a[i]) - b;
		for(i = 0; i < q; i++)
			rd(qs[i].l), rd(qs[i].r), rd(k[i]), qs[i].l--, qs[i].r--, p[i] = i;
		sq = ceil(sqrt(n));
		auto cmp = [](pii a, pii b) {
			if((a.l / sq) != (b.l / sq)) return a.l < b.l;
			return a.r < b.r;
		};
		sort(p, p + q, [cmp](int i, int j) { return cmp(qs[i], qs[j]); });
		int l = 0, r = -1;
		for(j = 0; j < q; j++) {
			i = p[j];
			while(r < qs[i].r) add(a[++r]);
			while(r > qs[i].r) rem(a[r--]);
			while(l < qs[i].l) rem(a[l++]);
			while(l > qs[i].l) add(a[--l]);
			int x = 0;
			ans[i] = 0;
			while(x + sq <= k[i]) ans[i] += gs[x / sq], x += sq;
			while(x <= k[i]) ans[i] += g[x++];
		}
		for(i = 0; i < q; i++) out(ans[i]);
		for(i = 0; i <= n; i++) gs[i] = g[i] = f[i] = 0;
	}
}
