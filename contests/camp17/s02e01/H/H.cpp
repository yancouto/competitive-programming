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

int n, m; ll k;
const int N = 212345;
int w[N], c[N];
ll accc[N], accw[N];

ll sumc(int l, int r) {
	if(l > r) return 0;
	return accc[r] - (l? accc[l - 1] : 0);
}
ll sumw(int l, int r) {
	if(l > r) return 0;
	return accw[r] - (l? accw[l - 1] : 0);
}

int main() {
	int i, j;
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	rd(n); rd(m); rd(k);
	for(i = 0; i < n; i++) {
		rd(w[i]); rd(c[i]);
	}
	accw[0] = w[0]; accc[0] = c[0];
	for(i = 1; i < n; i++)
		accw[i] = w[i] + accw[i - 1], accc[i] = c[i] + accc[i - 1];
	ll best = -1; int best_i, best_l;
	for(i = n - 1; i >= m; i--) {
		if(sumw(0, i - m) * k < sumw(i - m + 1, i)) break;
		int l = 0, r = i - m;
		while(l < r) {
			int mid = (l + r + 1) / 2;
			if(sumw(mid, i - m) * k < sumw(i - m + 1, i)) r = mid - 1;
			else l = mid;
		}
		if(sumc(0, l - 1) + sumc(i + 1, n - 1) > best)
			best = sumc(0, l - 1) + sumc(i + 1, n - 1),
			best_i = i,
			best_l = l;
	}
	printf("%d %lld\n", best_l + (n - 1 - best_i), best);
	for(i = 0; i < (n - 1 - best_i); i++) putchar('H');
	for(i = 0; i < best_l; i++) putchar('T');
	putchar('\n');
}
