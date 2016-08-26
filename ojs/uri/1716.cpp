#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
ull modn;
inline ull mod(ull x) { return x % modn; }

ull fexp(ull x, ull p) {
	ull resp = 1;
	for(ull i = 1; i <= p; i <<= 1) {
		if(i & p) resp = mod(resp * x);
		x = mod(x * x);
	}
	return resp;
}
int mdc(int a, int b) {
	if(b == 0) return a;
	return mdc(b, a % b);
}

int main() {
	int i, j, p, q;
	int n, e, c;
	scanf("%d %d %d", &n, &e, &c);
	for(p = 3; ; p++)
		if(!(n % p))
			break;
	q = n / p;
	int phin = (--p) * (--q);
	set<int> div;
	for(i = 2; i * i <= q; i++)
		while((q % i) == 0) {
			div.insert(i);
			q /= i;
		}
	if(q != 1) div.insert(q);
	for(i = 2; i * i <= p; i++)
		while((p % i) == 0) {
			div.insert(i);
			p /= i;
		}
	if(p != 1) div.insert(p);
	int tot = phin;
	for(int pp : div)
		tot = tot - tot / pp;
	modn = phin;
	int d = (int) fexp(e, tot - 1);
	assert(mod(ull(d) * e) == 1);
	modn = n;
	printf("%d\n", (int) fexp(c, d));
	return 0;
}
