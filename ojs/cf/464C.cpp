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
const ll m = 1000000006;
inline ll md(ll x) { return x % m; }

ll d[10], sz[10];
int main() {
	scanf("%s %d", s1, &n);
	for(i = 0; i < n; i++) {
		scanf(" %c->%s", &c[i], &s2);
		s[i] = s2;
	}
	for(i = 0; i < 10; i++) d[i] = i, sz[i] = 1;
	for(i = n - 1; i >= 0; i--) {
		reverse(s[i].begin(), s[i].end());
		ll p = 1; ll v = 0, s = 0;
		for(char c : s[i]) {
			v = mod(v + p * d[c - '0']);
			p = mod(p * 10ll);
		}
		d[c[i] - '0'] = v;
	}
}
