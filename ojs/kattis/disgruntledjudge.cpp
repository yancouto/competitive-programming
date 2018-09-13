#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const int modn = 10001;
inline int mod(int x) { return x % modn; }

ll fexp(ll x, ll p) {
	ll r = 1;
	for(; p; p >>= 1, x = mod(x * x))
		if(p & 1)
			r = mod(r * x);
	return r;
}

int inv[modn];
int x[modn];

int main() {
	int i, n;
	for(i = 1; i < modn; i++)
		inv[i] = fexp(i, 9792 - 1);
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%d", &x[i]);
	if(n == 0) { return 0; }
	if(n == 1) { puts("12"); return 0; }
	for(int a = 0; a <= 10000; a++) {
		vector<int> bs;
		if(true || mod((a + 1) * inv[a + 1]) != 1) {
			for(int b = 0; b <= 10000; b++)
				if(x[1] == mod(a * mod(a * x[0] + b) + b))
					bs.pb(b);
		} else {
			int b = mod(x[1] - mod(a * mod(a * x[0])) + modn);
			b = mod(b * inv[a + 1]);
			bs.pb(b);
		}
		for(int b : bs) {
			for(i = 1; i < n; i++)
				if(x[i] != mod(a * mod(a * x[i - 1] + b) + b))
					break;
			if(i == n) {
				for(i = 0; i < n; i++)
					printf("%d\n", mod(x[i] * a + b));
				return 0;
			}
		}
	}
}
