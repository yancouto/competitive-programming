#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

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

int n;

const int X = 512345;
vector<int> ls[X], ps[X], dvs[X];
int simple[X];

const int N = 51234;
int a[N], pr[N];

inline int eq(int l, int r, int d) {
	return upper_bound(ls[d].begin(), ls[d].end(), r) - lower_bound(ls[d].begin(), ls[d].end(), l);
}

int any(int l, int r, int x) {
	int ans = 0;
	for(int bm = 1; bm < (1 << ps[x].size()); bm++) {
		int d = 1;
		for(int j = 0; j < ps[x].size(); j++)
			if((bm >> j) & 1)
				d *= ps[x][j];
		//printf("any(%d, %d, %d) bms %d eq(%d, %d, %d) = %d\n", l, r, x, __builtin_popcount(bm) & 1, l, r, d, eq(l, r, d));
		if(__builtin_popcount(bm) & 1)
			ans += eq(l, r, d);
		else
			ans -= eq(l, r, d);
	}
	ans = (r - l + 1) - ans;
	//printf("any(%d, %d, %d) = %d\n", l, r, x, ans);
	return ans;
}

int tr[N << 2];

void build(int i, int l, int r) {
	if(l == r) return (void)(tr[i] = pr[l]);
	int m = (l + r) / 2;
	build(2 * i, l, m);
	build(2 * i + 1, m + 1, r);
	tr[i] = max(tr[2 * i], tr[2 * i + 1]);
}

int get(int i, int l, int r, int ql, int qr) {
	if(l > qr || r < ql) return INT_MIN;
	if(l >= ql && r <= qr) return tr[i];
	int m = (l + r) / 2;
	return max(get(2 * i, l, m, ql, qr), get(2 * i + 1, m + 1, r, ql, qr));
}

int main() {
	int i, j;
	int m;
	rd(n); rd(m);
	for(i = 2; i < X; i++)
		if(ps[i].empty())
			for(j = i; j < X; j += i)
				ps[j].pb(i);
	for(i = 1; i < X; i++) {
		simple[i] = 1;
		for(int p : ps[i]) simple[i] *= p;
		for(int bm = 0; bm < (1 << ps[i].size()); bm++) {
			int d = 1;
			for(int j = 0; j < ps[i].size(); j++)
				if((bm >> j) & 1)
					d *= ps[i][j];
			dvs[i].pb(d);
		}
	}
	for(i = 0; i < n; i++) {
		rd(a[i]);
		a[i] = simple[a[i]];
	}
	pr[0] = -1;
	for(int x : dvs[a[0]]) ls[x].pb(0);
	for(i = 1; i < n; i++) {
		if(any(0, i - 1, a[i]) == 0) {
			pr[i] = -1;
		} else {
			int l = 0, r = i - 1;
			while(l < r) {
				int m = (l + r + 1) / 2;
				if(any(m, i - 1, a[i])) l = m;
				else r = m - 1;
			}
			pr[i] = l;
		}
		for(int x : dvs[a[i]]) ls[x].pb(i);
		//printf("pr[%d] = %d\n", i, pr[i]);
	}
	build(1, 0, n - 1);
	while(m--) {
		int l, r;
		scanf("%d %d", &l, &r); l--; r--;
		if(get(1, 0, n - 1, l, r) >= l) puts("S");
		else puts("N");
	}
}
