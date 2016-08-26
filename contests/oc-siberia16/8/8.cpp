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

const int N = 1000109;
int hei[N], heo[N], en;
const int NO = 20000010;
int nx[NO], v[NO];
const int M = 11234;

int a[M], l[M], r[M], ct[M];

inline void pb(int &h, int i) {
	v[en] = i;
	nx[en] = h;
	h = en++;
}

int n, m;
pii solve() {
	int i, j;
	for(i = 0; i < N; i++) hei[i] = heo[i] = -1;
	en = 0;
	int cur = 0;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			if(a[i] <  l[j]) pb(hei[l[j] - a[i]], i);
			if(a[i] <= r[j]) pb(heo[r[j] - a[i]], i);
			if(a[i] >= l[j] && a[i] <= r[j]) ct[i]++;
			if(ct[i] == 1 && a[i] >= l[j] && a[i] <= r[j]) cur++;
		}
	pii ans(cur, 0);
	for(i = 0; i < N; i++) {
		for(int j = hei[i]; j != -1; j = nx[j]) if(++ct[v[j]] == 1) cur++;
		ans = max(ans, pii(cur, -i));
		for(int j = heo[i]; j != -1; j = nx[j]) if(--ct[v[j]] == 0) cur--;
	}
	return ans;
}

int l2[M], r2[M], a2[M], p[M];

inline int get() {
	char c;
	while(isspace(c = getchar_unlocked()));
	int x = c - '0';
	while(isdigit(c = getchar_unlocked()))
		x = (x << 3) + (x << 1) + (c - '0');
	return x;
}

int main() {
	int i;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	n = get(); m = get();
	for(i = 0; i < n; i++) a[i] = get();
	for(i = 0; i < m; i++) l[i] = get(), r[i] = get();
	//for(i = 0; i < n; i++) a[i] = rand() % 1000000;
	//for(i = 0; i < m; i++) {
	//	l[i] = rand() % 1000000; r[i] = rand() % 1000000;
	//	if(r[i] < l[i]) swap(l[i], r[i]);
	//}
	sort(a, a + n);
	for(i = 0; i < m; i++) l2[i] = l[i], r2[i] = r[i], p[i] = i;
	sort(p, p + m, [](int i, int j) { return l[i] < l[j]; });
	for(i = 0; i < m; i++) l[i] = l2[p[i]], r[i] = r2[p[i]];
	int j = 0, sn = 0;
	for(i = 0; i < m; ) {
		for(j = i; j < m && l[j] <= r[i]; j++)
			r[i] = max(r[i], r[j]);
		l[sn] = l[i]; r[sn++] = r[i];
		i = j;
	}
	m = sn;
	pii ans = solve();
	for(i = 0; i < n; i++) a[i] = 1000000 - a[i];
	for(i = 0; i < m; i++) {
		l[i] = 1000000 - l[i];
		r[i] = 1000000 - r[i];
		swap(l[i], r[i]);
	}
	reverse(l, l + m);
	reverse(r, r + m);
	reverse(a, a + n);
	ans = max(ans, solve());
	printf("%d %d\n", -ans.snd, ans.fst);
}
