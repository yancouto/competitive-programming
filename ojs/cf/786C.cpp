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

const int N = 112345;

const int M = 3123456;

int L[M], R[M], tr[M], t2[M];
int seg[N];
int en = 1;

int copy(int x) {
	L[en] = L[x]; R[en] = R[x]; tr[en] = tr[x]; t2[en] = t2[x];
	return en++;
}

int add(int i, int l, int r, int p) {
	int j = copy(i);
	tr[j]++;
	if(l == r) {
		t2[j] = 1;
		return j;
	}
	int m = (l + r) / 2;
	if(p <= m) L[j] = add(L[j], l, m, p);
	else R[j] = add(R[j], m + 1, r, p);
	tr[j] = tr[L[j]] + tr[R[j]];
	t2[j] = t2[L[j]] + t2[R[j]];
	return j;
}

int nx(int u, int d, int l, int r, int k) {
	if(l == r) return !!(tr[u] - tr[d]);
	int m = (l + r) / 2;
	int ans = 0;
	if(tr[L[u]] - tr[L[d]]) ans += nx(L[u], L[d], l, m, k);
	if(tr[R[u]] - tr[R[d]]) ans += nx(R[u], R[d], l, m, k);
	return ans;
}


int a[N];
int main() {
	int i, j, k;
	rd(n);
	for(i = 1; i <= n; i++) {
		rd(a[i]);
		seg[i] = add(seg[i - 1], 1, n, a[i]);
	}

	for(k = 1; k <= n; k++) {
		i = 1;
		int ct = 0;
		while(i <= n) {
			int l = i, r = n;
			while(l < r) {
				int m = (l + r + 1) / 2;
				if(nx(seg[i], seg[m], 1, n, 100) <= k) l = m;
				else r = m - 1;
			}
			ct++;
			i = l + 1;
		}
		printf("%d%c", ct, " \n"[k == n]);
	}
}
