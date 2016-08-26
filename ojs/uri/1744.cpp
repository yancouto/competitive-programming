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

char s[5009];
int main() {
	int a, b, i;
	scanf("%d %d", &a, &b); b = a - b;
	scanf("%s", s);
	int nb = 0;
	for(i = 0; s[i]; i++)
		nb += s[i] == 'B';
	int l = nb - 1, r = nb;
	ll tot = 0;
	while(s[l]) {
		while(l >= 0 && s[l] == 'B') l--;
		while(s[r] && s[r] == 'W') r++;
		if(!s[r] || l < 0) break;
		tot += min<ll>(a, ll(b) * (r - l));
		swap(s[l], s[r]);
	}
	printf("%lld\n", tot);
}
