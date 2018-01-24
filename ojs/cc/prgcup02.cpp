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

int main() {
	for_tests(tn, tt) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		if(a < b) swap(a, b);
		if(a < c) swap(a, c);
		if(a * a == b * b + c * c && __gcd(a, __gcd(b, c)) == 1)
			puts("YES");
		else
			puts("NO");
	}
}
