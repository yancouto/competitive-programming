// incomplete
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
ll size;
char s[103];
ll ct[256]; int k[102];
ll get(ll x) {
	if(x <= size) return s[x];
	ll z = (x + size - 1) / size;
	int q = 63 - __builtin_clzll(z);
	if(z & (z - 1)) q++;
	return get(x - (size << (q - 1)) - k[q - 1]);
}
ll get(ll x, char c) {
	if(x == 0) return 0;
	ll z = (x + size - 1) / size;
	int q = 63 - __builtin_clzll(z);
	if(z & (z - 1)) q++;
	if(q == 0) {
		ll val = 0;
		for(int i = 0; i < size; i++)
			val += s[i] == c;
		return val;
	}
	printf("x %lld q %d\n", x, q);
	ll val = (ct[c] << (q - 1)) + get(x - (size << (q - 1)) + k[q - 1], c);

	for(int i = 0; i < k[q - 1]; i++)
		val += get((ct[c] << (q - 1)) - i) == c;
	return val;
}

int main() {
	int i, n, m; ll l, r; char c;
	scanf("%s", s);
	size = strlen(s);
	for(i = 0; s[i]; i++)
		ct[s[i]]++;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		scanf("%d", &k[i]);
	for(i = 0; i < m; i++) {
		scanf("%lld %lld %c", &l, &r, &c);
		printf("%lld\n", get(r, c) - get(l - 1, c));
	}
}
