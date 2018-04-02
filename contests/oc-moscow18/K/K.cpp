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

const int N = 1e5+7;

int n; ll x;
ll a[N];
int p[N];

ll get (ll a, ll x) {
	ll pot = 1;
	ll r = 0, c = 0;
	while (a || x || c) {
		ll s = ((a%10 - x%10 + c + 10)%10);
		r += s*pot;
		pot *= 10;
		ll t = a%10 - s + c;
		if (t >= 10) c = -1;
		else if (t < 0) c = 1;
		else c = 0;
		a /= 10; x /= 10;
	}
	return r;
}

int main () {
	scanf("%d %lld", &n, &x);
	
	for (int i = 0; i < n; i++) {
		scanf(" %lld", &a[i]);
		p[i] = i;
	}
	sort(p, p+n, [] (int i, int j) { return a[i] < a[j]; });
	
	for (int i = 0; i < n; i++) {
		ll r = get(a[i],x);
		//cout << "for " << a[i] << " = " << r << endl;
		int s = lower_bound(p,p+n,r, [] (int i, ll r) { return a[i] < r; }) - p;
		if (s < n && a[p[s]] == r) {
			printf("%d %d\n", i+1, p[s]+1);
			return 0;
		}
	}
	printf("-1 -1\n");
}
