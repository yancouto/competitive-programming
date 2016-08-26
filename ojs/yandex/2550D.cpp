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
#define left asljdalisdjli

ll cur = 1e17;
void ans() {
	printf("! %lld\n", cur); fflush(stdout);
	exit(0);
}

int left = 2000;
int query(ll x) {
	left--;
	if(left < 0) ans();
	printf("? %lld\n", x); fflush(stdout);
	char c; scanf(" %c", &c);
	return c == 'W';
}

std::random_device rd;
std::mt19937 g(rd());

ll gen(ll x) {
	std::uniform_int_distribution<ll> dis(0ll, x - 1ll);
	return dis(g);
}

ll gen(ll l, ll r) {
	ll g = gen(r - l + 1ll);
	return l + g;
}

int main() {
	srand(time(NULL));
	ll a[2] = {0, 0}, b[2];
	while(!a[0] || !a[1]) {
		ll x = gen(1, 5e17);
		a[query(x)] = x;
	}
	while(abs(a[0] - a[1]) > 1) {
		ll m = (a[0] + a[1]) / 2ll;
		a[query(m)] = m;
	}
	bool r = a[1] > a[0], fst = true;
	while(cur > 1) {
		ll x = gen(max(a[0], a[1]) + 1, min(a[0], a[1]) + cur);
		if(fst) x = max(a[0], a[1]) + cur;
		fst = false;
		if(query(x) != r) {
			b[r] = max(a[0], a[1]);
			b[!r] = x;
			while(abs(b[0] - b[1]) > 1) {
				ll m = (b[0] + b[1]) / 2ll;
				b[query(m)] = m;
			}
			cur = b[!r] - max(a[0], a[1]);
		}
	}
	ans();
}
