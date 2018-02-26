#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

typedef long double ld;
int main() {
	ll k,d , t;
	cin >> k >> d >> t;
	if(d < k)
		d = ll((k + d - 1) / d) * d;
	cout << "k " << k << " d " << d << endl;
	ll a = k;
	ll b = d - k;
	cout << "a " << a << " b " << b << endl;
	ll full = (2ll * t) / (2ll * a + b);
	ll g = (2ll * t) % (2ll * a + b);
	ld tm = ld(full) * (a + b);
	printf("base %.5f\n", double(tm));
	if(g) {
		cout << "g " << g << "/" << 2 * a + b<< endl;
		if(ld(a) / ld(t) >= ld(g) / ld(2 * a + b)) {
			printf("Case A\n");
			tm += ld(ld(g) / ld(2 * a + b)) * ld(t);
		} else {
			printf("Case B\n");
			cout << tm << endl;
			tm += a;
			cout << tm << endl;
			tm += ((ld(g) / ld(2 * a + b)) - ld(a) / ld(t)) * 2.0l * ld(t);
			cout << tm << endl;
		}
	}
	cout << tm << endl;
}
