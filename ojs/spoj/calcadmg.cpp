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

int gcd(int a, int b) {
	if(!b) return a;
	return gcd(b, a % b);
}

int main() {
	int a, b, c, d;
	for_tests(t, tt) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		printf("%d\n", 1+gcd(abs(a - c), abs(b - d)));
	}
}
