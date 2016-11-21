#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair< int , int > pii;
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 70;
ll a[N];

struct st {
	ll mn, mx, sum;
};
#define pc __builtin_popcount

ll fat[112];
int f[256];
char s[100];
int n;
ll calc(int b) {
	if(b == 0) return 0;
	ll x = 0;
	for(int i = 0; i < n; i++) {
		sprintf(s, "%llx", a[i]);
		ll y = 0;
		for(int j = 0; s[j]; j++) {
			if((b >> f[s[j]]) & 1) continue;
			y = 16 * y + f[s[j]];
		}
		//if(b <= 4) printf("%llx - %d = %llx\n", a[i], b, y);
		x += y;
	}
	return x;
}

st memo[1 << 16];
st solve(int b) {
	if(b == ((1 << 16) - 1)) return {0, 0, 0};
	st &r = memo[b];
	if(r.mn != -1) return r;
	ll c = calc(b);
	r = {LLONG_MAX, 0, mod(mod(c) * fat[16 - pc(b)])};
	for(int i = 0; i < 16; i++) {
		if((b >> i) & 1) continue;
		st q = solve(b | (1 << i));
		r.mn = min(r.mn, c + q.mn);
		r.mx = max(r.mx, c + q.mx);
		r.sum = r.sum + q.sum;
		if(r.sum >= modn) r.sum -= modn;
	}
	return r;
}


int main() {
	int i = 0;
	for(char c : "0123456789abcdef")
		f[c] = i++;
	fat[0] = 1;
	for(i = 1; i < 100; i++)
		fat[i] = mod(ll(i) * fat[i - 1]);
	scanf("%x", &n);
	for(i = 0; i < n; i++) scanf("%llx", &a[i]);
	memset(memo, -1, sizeof memo);
	st a = solve(0);
	printf("%llx %llx %llx\n", a.mn, a.mx, a.sum);
}
