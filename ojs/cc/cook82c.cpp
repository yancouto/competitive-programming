#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int q[1123456];

int j, m;

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

const int N = 1000009 * 64;
ll v[N]; int vn;
int acc[N];

int rnd(int l, int r) { return l + (double(rand()) / (ll(RAND_MAX) + 1ll)) * (r - l + 1); }

void quick(int l, int r) {
	int m = rnd(l, r);
	ll x = v[m];
	int cntl = 0;
	for(int i = l; i <= r; i++)
		if(v[i] > x)
			swap(v[i], v[l + cntl++]);
	int cnte = 0;
	for(int i = l + cntl; i <= r; i++)
		if(v[i] == x)
			swap(v[i], v[l + cntl + cnte++]);
	int ml = l + cntl - 1;
	int mr = l + cntl + cnte;
	if(l <= ml && acc[ml] - (l? acc[l - 1] : 0ll)) quick(l, ml);
	if(mr <= r && acc[r] - (mr? acc[mr - 1] : 0ll)) quick(mr, r);
}

int ct[1 << 22];

int main() {
	int i, n; ll x;
	rd(n); rd(m);
	for(i = 0; i < n; i++) {
		rd(x);
		while(x >= (1 << 22)) {
			v[vn++] = x;
			x >>= 1;
		}
		if(x > 0) ct[x]++;
	}
	for(i = 0; i < m; i++) {
		rd(q[i]); q[i]--;
		if(q[i] < vn) acc[q[i]]++;
	}
	for(i = 1; i < vn; i++)
		acc[i] += acc[i - 1];
	quick(0, vn - 1);
	for(i = (1 << 22) - 1; i > 1; i--)
		ct[i >> 1] += ct[i];
	for(i = 0; i < m; i++)
		if(q[i] < vn)
			printf("%lld\n", v[q[i]]);
		else break;
	int j = i;
	int op = vn;
	for(i = (1 << 22) - 1; i >= 1; i--) {
		while(j < m && op + ct[i] >= q[j] + 1)
			printf("%d\n", i), j++;
		op += ct[i];
	}
}
