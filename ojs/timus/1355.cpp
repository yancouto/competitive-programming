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

int main() {
	for_tests(t, tt) {
		int a, b, i;
		scanf("%d %d", &b, &a);
		if(a % b) { puts("0"); continue; }
		a /= b;
		int ct = 1;
		for(int i = 2; i * i <= a; i++)
			while(!(a % i))
				a /= i, ct++;
		if(a > 1) ct++;
		printf("%d\n", ct);
	}
}
