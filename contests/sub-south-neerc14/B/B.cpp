#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<int, int> pii;

typedef double ld;

ld sq(ld x) { return x * x; }
ll sq(ll x) { return x * x; }

ld eps = 1e-9;

const int N = 312345;
ll c[N], x[N];
int p[N], mn[N], mx[N];

inline bool in(int i, int j, ll r) {
	return sq(x[i] - c[j]) + 100ll <= r * r;
}

template<class T>
inline void rd(T &x) {
	char c;
	while(isspace(c = getchar()));
	x = c - '0';
	while(!isspace(c = getchar())) {
		if(c != '.') x = (x << 3) + (x << 1) + (c - '0');
	}
}

int main() {
	int i, n, m; ll R;
	rd(m); rd(n); rd(R);
	R *= 10;
	ld db;
	for(i = 0; i < m; i++) {
		rd(c[i]);
	}
	for(i = 0; i < n; i++) {
		rd(x[i]);
		p[i] = i;
	}
	sort(p, p + n, [](int i, int j) { return x[i] < x[j]; });
	int l = 0, r = 0;
	for(int i_ = 0; i_ < n; i_++) {
		i = p[i_];
		while(!in(i, l, R)) assert(++l < m);
		r = max(r, l);
		while(r + 1 < m && in(i, r + 1, R)) r++;
		mn[i] = l;
		mx[i] = r;
	}
	int cur = 0;
	ll tot = 0;
	for(i = 0; i < n; i++) {
		if(mn[i] <= cur && cur <= mx[i]) continue;
		if(cur < mn[i]) {
			tot += c[mn[i]] - c[cur];
			cur = mn[i];
		} else {
			tot += c[cur] - c[mx[i]];
			cur = mx[i];
		}
	}
	printf("%lld.%lld\n", tot / 10ll, tot % 10);
}
