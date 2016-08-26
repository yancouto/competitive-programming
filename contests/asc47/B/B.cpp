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

ull shiftm1(int p) {
	if(p == 64) return ULLONG_MAX;
	return (1ull << p) - 1ull;
}

int n;

ull a[100], p[100];
ull sub(ull bm, int I, int J) {
	int i = n - 1 - J;
	int j = n - 1 - I;
	bm >>= i;
	i = j - i + 1;
	return bm & shiftm1(i);
}

void prefs(ull bm) {
	int i, j;
	p[0] = 1;
	for(i = 1; i < n; i++) {
		p[i] = 1;
		for(j = 0; j < i; j++)
			if(sub(bm, 0, j) == sub(bm, i - j, i))
				p[i] = 0;
	}
}

ull rev(ull bm) {
	ull b2 = 0;
	for(int i = 0; i < n; i++)
		if((bm >> i) & 1)
			b2 |= (1ull << (n - 1 - i));
	return b2;
}

ull ans(ull bm) {
	int i, j;
	prefs(bm);
	a[0] = (bm >> (n - 1));
	for(i = 1; i < n; i++) {
		a[i] = sub(bm, 0, i);
		for(j = 0; 2*(j+1) <= i+1; j++) {
			a[i] -= a[j] * (1ull << (i+1 - 2*(j+1)));
			if(p[j] && sub(bm, 0, j) < sub(bm, i - j, i)) a[i]--;
			if(p[j]) a[i] -= sub(bm, j + 1, i - j - 1);
		}
	}
	return a[n-1] + p[n-1];
}

int main() {
	freopen("borderless.in", "r", stdin);
	freopen("borderless.out", "w", stdout);
	int i; ull k;
	while(scanf("%d %I64u", &n, &k) != EOF && n) {
		if(k == 1 && ans(0) == 1) {
			for(i = 0; i < n; i++) putchar('a');
			putchar('\n');
			continue;
		}
		ull l = 0, r = shiftm1(n);
		while(l < r) {
			ull m = l + ((r - l) >> 1);
			if((r - l) & 1) m++;
			if(ans(m) < k) l = m;
			else r = m - 1;
		}
		l++;
		for(i = 0; i < n; i++)
			putchar('a' + ((l >> (n-i-1)) & 1));
		putchar('\n');
	}
}
