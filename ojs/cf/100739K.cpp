#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
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

ll a[N], x[N]; int p[N];
ll acc[N], ans[N];

inline ll eval(ll x, ll i) {
	if(x < i) return -1e16;
	return acc[i] + ((x - i) / 2) * a[i] + ((x - i + 1) / 2) * a[i - 1];
}

void solve(int l, int r, int ql, int qr) {
	if(r < l) return;
	int m = (l + r) / 2;
	assert(ql <= x[p[m]]);
	int bi = ql;
	for(int i = ql + 2; i <= qr && i <= x[p[m]]; i += 2)
		if(eval(x[p[m]], i) > eval(x[p[m]], bi))
			bi = i;
	ans[p[m]] = max(ans[p[m]], eval(x[p[m]], bi));
	solve(l, m - 1, ql, bi);
	solve(m + 1, r, bi, qr);
	//printf("[%d, %d, %d] [%d]%lld = %lld\n", l, m, r, p[m], x[p[m]], ans[p[m]]);
}

int main() {
	int i, q;
	rd(n); rd(q);
	for(i = 0; i < n; i++) rd(a[i]);
	acc[0] = a[0];
	for(i = 1; i < n; i++) acc[i] = a[i] + acc[i - 1];
	for(i = 0; i < q; i++) rd(x[i]), p[i] = i;
	sort(p, p + q, [](int i, int j) { return x[i] < x[j]; });
	solve(0, q - 1, 1, n - 1);
	for(i = 0; i < q && x[p[i]] == 1; i++);
	solve(i, q - 1, 2, n - 1);
	for(i = 0; i < q; i++) printf("%lld\n", ans[i]);
}
