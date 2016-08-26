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
ll n, best; int bd = -1;
int ps[100], pn;
void go(int i, int mx, ll nu, int dvn) {
	if(mx == 0) {
		if(dvn > bd || (dvn == bd && nu < best))
			best = nu, bd = dvn;
		return;
	}
	go(i + 1, 0, nu, dvn);
	for(int g = 1; g <= mx && nu * ps[i] <= n; g++)
		go(i + 1, g, nu *= ps[i], dvn * (g + 1));
}

int main() {
	freopen("divisors.in", "r", stdin);
	freopen("divisors.out", "w", stdout);
	int i, j;
	for(i = 2; pn < 31; i++) {
		for(j = 2; j * j <= i && i % j; j++);
		if(j * j > i) ps[pn++] = i;
	}
	scanf("%I64d", &n);
	go(0, 100, 1, 1);
	printf("%I64d\n", best);
}
