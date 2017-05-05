#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, int> pli;
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
const int N = 312345;

ll rans[N], ans[N], a[N], acc[N]; pli x[N];
inline ll eval(ll x, ll i) {
	if(x < i) return LLONG_MIN;
	return acc[i] + ((x - i) / 2) * (a[i] + a[i - 1]) + ((x - i) % 2) * a[i - 1];
}


void solve(int l, int r, int il, int ir) {
	if(r < l) return;
	int m = (l + r) / 2;
	int bi = il;
	for(int i = il + 2; i <= ir; i += 2)
		if(eval(x[m].fst, i) >= eval(x[m].fst, bi))
			bi = i;
	ans[m] = max(ans[m], eval(x[m].fst, bi));
	solve(l, m - 1, il, bi);
	solve(m + 1, r, bi, ir);
}

int main() {
	int i, q;
	rd(n); rd(q);
	for(i = 0; i < n; i++) rd(a[i]), acc[i] = (i? acc[i - 1] : 0) + a[i];
	for(i = 0; i < q; i++) rd(x[i].fst), x[i].snd = i;
	sort(x, x + q);
	solve(0, q - 1, 1, n - 1);
	solve(0, q - 1, 2, n - 1);
	for(i = 0; i < q; i++) rans[x[i].snd] = ans[i];
	for(i = 0; i < q; i++) printf("%lld\n", rans[i]);
}
