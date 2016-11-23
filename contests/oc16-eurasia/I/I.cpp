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

unsigned fexp(unsigned x, unsigned p) {
	unsigned r = 1;
	for(; p; p >>= 1, x *= x)
		if(p & 1)
			r *= x;
	return r;
}

unsigned fixsum(unsigned x, unsigned val) {
	return x * fexp((1u << val) + 1u, (1u << 31u) - 1u);
}

unsigned fixxor(unsigned x, unsigned val) {
	for(int i = 31-val; i >= 0; i--)
		x ^= ((x & (1u << (i + val))) >> val);
	return x;
}

int main() {
	unsigned x;
	for_tests(t, tt) {
		scanf("%u", &x);
		x = fixsum(x, 16);
		x = fixxor(x, 11);
		x = fixsum(x, 3);
		x = fixxor(x, 6);
		x = fixsum(x, 10);
		printf("%u\n", x);
	}
}
