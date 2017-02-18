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
#	define debug(args...) {}
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

const int N = 2009;

int mx(int a, int b) { return max(a, b); }
int mn(int a, int b) { return min(a, b); }

int en;
const int Q = 11234567;
int L[Q], R[Q], val[Q];
int& get(int &x, const int def) {
	if(x == 0) {
		x = en++;
		L[x] = R[x] = 0;
		val[x] = def;
	}
	return x;
}

void sset(int &i, int l, int r, int pos, int x, function<int(int,int)> fun, const int def) {
	get(i, def);
	if(l == r) {
		val[i] = fun(val[i], x);
		return;
	}
	int m = (l + r) / 2;
	if(pos <= m) sset(L[i], l, m, pos, x, fun, def);
	else sset(R[i], m + 1, r, pos, x, fun, def);
	val[i] = fun(val[get(L[i], def)], val[get(R[i], def)]);
}

int get(int &i, int l, int r, int pos, function<int(int, int)> fun, const int def) {
	if(r < pos) return def;
	get(i, def);
	if(l >= pos) return val[i];
	int m = (l + r) / 2;
	return fun(get(L[i], l, m, pos, fun, def), get(R[i], m + 1, r, pos, fun, def));
}

int mn1[N][N], mx1[N][N];
int mn2[N][N], mx2[N][N];
int a[N][N];
int m;

int solve(void);

int main() {
	int i, j;
	rd(n); rd(m);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			rd(a[i][j]);
	int x = solve();
	for(i = 0; i < n; i++)
		reverse(a[i], a[i] + m);
	printf("%d\n", min(x, solve()));
}

int mn3[N*N], mx3[N*N];

int solve() {
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			mx1[i][j] = mn1[i][j] = a[i][j];
			if(i) mn1[i][j] = min(mn1[i][j], mn1[i - 1][j]),
			      mx1[i][j] = max(mx1[i][j], mx1[i - 1][j]);
			if(j) mn1[i][j] = min(mn1[i][j], mn1[i][j - 1]),
			      mx1[i][j] = max(mx1[i][j], mx1[i][j - 1]);
		}
	//while(true) {
	//	int l, r; rd(l); rd(r);
	//	int mn = INT_MAX, mx = INT_MIN;
	//	for(i = 0; i < n; i++)
	//		for(j = 0; j < m; j++) {
	//			if(a[i][j] >= l && a[i][j] <= r)  printf("%2d", a[i][j]);
	//			else printf("--"), mn = min(mn, a[i][j]), mx = max(mx, a[i][j]);
	//			putchar(" \n"[j == m - 1]);
	//		}
	//	printf("%d-%d\n", mn, mx);
	//}
	vector<pii> all;
	for(i = n - 1; i >= 0; i--)
		for(j = m - 1; j >= 0; j--) {
			mx2[i][j] = mn2[i][j] = a[i][j];
			if(i < n - 1) mn2[i][j] = min(mn2[i][j], mn2[i + 1][j]),
			              mx2[i][j] = max(mx2[i][j], mx2[i + 1][j]);
			if(j < m - 1) mn2[i][j] = min(mn2[i][j], mn2[i][j + 1]),
			              mx2[i][j] = max(mx2[i][j], mx2[i][j + 1]);
			all.pb(pii(i, j));
		}
	sort(all.begin(), all.end(), [](pii a, pii b) { return mn1[a.fst][a.snd] > mn1[b.fst][b.snd]; });
	for(i = all.size() - 1; i >= 0; i--) {
		mn3[i] = mn2[all[i].fst][all[i].snd];
		if(i < all.size() - 1) mn3[i] = min(mn3[i], mn3[i + 1]);
		mx3[i] = mx2[all[i].fst][all[i].snd];
		if(i < all.size() - 1) mx3[i] = max(mx3[i], mx3[i + 1]);
	}
	ll l = 0, r = 2.1e9;
	while(l < r) {
		ll x = (l + r) / 2;
		multiset<int> mn2, mx2;
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				mn2.insert(::mn2[i][j]),
				mx2.insert(::mx2[i][j]);
		bool ok = false;
		en = 1;
		int smn = 0, smx = 0;
		i = 0;
		for(pii p : all) {
			i++;
			sset(smn, 1, 1000000000, ::mx1[p.fst][p.snd], ::mn2[p.fst][p.snd], mn, INT_MAX);
			sset(smx, 1, 1000000000, ::mx1[p.fst][p.snd], ::mx2[p.fst][p.snd], mx, INT_MIN);
			int MN = get(smn, 1, 1000000000, ::mn1[p.fst][p.snd] + x + 1, mn, INT_MAX);
			if(i < all.size()) MN = min(MN, mn3[i]);
			int MX = get(smx, 1, 1000000000, ::mn1[p.fst][p.snd] + x + 1, mx, INT_MIN);
			if(i < all.size()) MX = max(MX, mx3[i]);
			if(MN == INT_MAX || MX - MN <= x) { ok = true; break; }
		}
		if(ok) r = x;
		else l = x + 1;
	}
	return l;
}
