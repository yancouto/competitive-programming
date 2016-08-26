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
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

ll mdc(ll a, ll b) {
	if(b == 0) return a;
	return mdc(b, a % b);
}

char str[30];
int main() {
	scanf("%s", str);
	int n = strlen(str);
	char *p = strchr(str, '.');
	ull a = 100;
	if(p) {
		char *o = p++;
		while(*o) {
			a *= 10;
			*o = *p;
			p++; o++;
		}
		a /= 10;
		n--;
	}
	ull x = atoll(str);
	printf("%I64d\n", a / mdc(a, x));
	return 0;
}
