#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef unsigned long long ll;
typedef pair<ll,ll> pii;
int sz_num(ll x) {
	return 64 - __builtin_clzll(x);
}

ll where_begins(ll x) {
	ll b = sz_num(x) - 1;
	//printf("b %lld\n", b);
	ll ans = 0;
	for(ll i = 1; i <= b; i++) {
		assert(ans <= ULLONG_MAX - (1ull << (i - 1ull)) * i);
		ans += (1ull << (i - 1ull)) * i;
		//printf(">> %lld\n", (1ull << (i - 1ull)));
		//printf("<%lld\n", ans);
	}
	assert(ans <= ULLONG_MAX - (b + 1ull) * (x - (1ull << b)));
	ans += (b + 1ull) * (x - (1ull << b));
	return ans;
}

int n;
char As[100];
ll A[100];

ll parse(int l, int r) {
	ll x = 0;
	for(; l <= r; l++)
		x = 2 * x + A[l];
	return x;
}

ll ans;

void try_(ll x, int d) {
	if(!x || where_begins(x) - d >= ans) return;
	ll ox = x;
	//printf("try(%lld, %d)\n", x, d);
	int od = d;
	int off = 0;
	while(d--) {
		if(--off == -1) {
			x--;
			if(x <= 0) return;
			off = sz_num(x) - 1;
		}
	}
	for(int i = 0; i < n; i++) {
		//printf("match[%d](%d) with %lld off %d\n", i, A[i], x, off);
		if(A[i] != ((x >> (sz_num(x) - 1 - off)) & 1ull))
			return;
		//printf("OK\n\n");
		off++;
		if(sz_num(x) == off)
			x++, off = 0;
	}
	//printf("ok %lld offset %d ==> %lld - %d\n", ox, od, where_begins(ox), od);
	ans = min(ans, where_begins(ox) - od);
}

int main () {
	//printf("%llu\n", (1ull << 56));
	//printf("%llu\n", where_begins(1ull << 57));
	int i, j;
	scanf("%s", As);
	n = strlen(As);
	for(i = 0; i < n; i++)
		A[i] = As[i] - '0';
	if(A[0])
		ans = where_begins(parse(0, n - 1));
	else
		ans = where_begins(parse(0, n - 1) + (1ull << n)) + 1;
	for(i = 0; i < n; i++)
		if(A[i])
			for(j = i + i; j < n; j++)
				try_(parse(i, j), i);
	bool all1 = true;
	for(i = 0; i < n - 1; i++) {
		if(!A[i + 1]) continue;
		all1 = all1 && A[i];
		for(int sz = max(i + 1, n - i - 1) + 1; sz <= n + 1; sz++) {
			ll x = (((parse(i + 1, n - 1) - 1ull) << (sz - (n - i - 1)))) | parse(0, i);
			x++;
			try_(x, i + 1);
			x = ((parse(i + 1, n - 1) << (sz - (n - i - 1)))) | parse(0, i);
			x++;
			try_(x, i + 1);
		}
	}
	printf("%llu\n", ans + n);
}
