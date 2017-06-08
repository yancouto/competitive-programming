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
const int N = 4123456;
ll tr[N], lz[N];
ll a[N], b[N], ans[N];

void build(int i, int l, int r) {
	if(l == r) return (void) (tr[i] = a[l] - l - 1);
	int m = (l + r) / 2;
	build(2 * i, l, m);
	build(2 * i + 1, m + 1, r);
	tr[i] = min(tr[2 * i], tr[2 * i + 1]);
}

void unlaze(int i, int l, int r) {
	tr[i] += lz[i];
	if(l != r) lz[2 * i] += lz[i], lz[2 * i + 1] += lz[i];
	lz[i] = 0;
}

void add(int i, int l, int r, int ql, int qr, ll x) {
	unlaze(i, l, r);
	if(l > qr || r < ql) return;
	if(l >= ql && r <= qr) {
		lz[i] = x;
		unlaze(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	add(2 * i, l, m, ql, qr, x);
	add(2 * i + 1, m + 1, r, ql, qr, x);
	tr[i] = min(tr[2 * i], tr[2 * i + 1]);
}

ll bk;
// first value <= x with index >= j
int query(int i, int l, int r, int j, ll x) {
	unlaze(i, l, r);
	if(tr[i] > x) return INT_MAX;
	if(r < j) return INT_MAX;
	if(l == r) { bk = tr[i]; return l; }
	int m = (l + r) / 2;
	unlaze(2 * i, l, m);
	unlaze(2 * i + 1, m + 1, r);
	int k = INT_MAX;
	if(m >= j && tr[2 * i] <= x) k = query(2 * i, l, m, j, x);
	if(k == INT_MAX && tr[2 * i + 1] <= x) k = query(2 * i + 1, m + 1, r, j, x);
	return k;
}

int bit[N];
void add(int i, int x) {
	for(i += 2; i < N; i += (i & -i))
		bit[i] += x;
}

int get(int i) {
	int x = 0;
	for(i += 2; i; i -= (i & -i))
		x += bit[i];
	return x;
}


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

inline void prn(ll x) {
	int sz = 0; ll y = 0;
	for(; x; x /= 10, sz++) y = (y << 3) + (y << 1) + (x % 10);
	for( ; sz--; y /= 10) putchar('0' + (y % 10));
	putchar(' ');
}

int main() {
	srand(time(NULL));
	int i, n;
	for_tests(tn, tt) {
		rd(n);
		for(i = 0; i < n; i++) rd(b[i]);
		for(i = 0; i < n; i++) rd(a[i]);
		//for(i = 0; i < n; i++) a[i] = b[i] = (ll(rand()) * ll(rand()) + ll(rand())) % 1000000000000ll;
		for(i = 0; i < n; i++) add(i, 1);
		build(1, 0, n - 1);
		ll all = n;
		ll t = 1; i = 0;
		bool bo = false;
		while(all > 0) {
			if(get(n - 1) - get(i - 1) == 0) i = 0;
			int j = query(1, 0, n - 1, i, t - (get(i - 1) + 1));
			if(j != INT_MAX) {
				bo = false;
				add(1, 0, n - 1, j + 1, n - 1, 1);
				add(1, 0, n - 1, j, j, 6e18);
				t += get(j) - get(i - 1);
				t += b[j];
				ans[j] = t - 1;
				all--;
				add(j, -1);
				i = j + 1;
			} else if(i) {
				t += get(n - 1) - get(i - 1);
				i = 0;
			} else {
				assert(!bo);
				bo = true;
				unlaze(1, 0, n - 1);
				ll k = (tr[1] - t + 1ll + all - 1ll) / all;
				t += k * all;
				assert(t - 1 >= tr[1]);
			}
		}
		for(i = 0; i < n; i++) prn(ans[i]);
		putchar('\n');
	}
}
